#include "../Headers/Client.hpp"
#include <iostream> /*DELETE*/
/*MULTITHREADING*/
Client::Client(std::string name, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : name_(name), mac_(mac), location_(location), pool_(pool) {}
void Client::Stop() {
        update_ = true;
}

bool Client::ReceivePacket(std::shared_ptr<Packet> packet) {
        received_packets_.push_back(packet);
        return true;
}
bool Client::Start() {
        update_ = false;
        if (!interface_.first) {
                return false;
        }
        /*Creating thread for interface port, using lambda expression specifying the behavior*/
        queue q = interface_.second;
        std::shared_ptr<Channel> ch = interface_.first;
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); /*delay on creating threads*/
        std::cout << name_ << "Creating thread" << std::endl; /*DELETE*/
        std::shared_ptr<std::thread> th = std::make_shared<std::thread> (std::thread([&, q, ch]()                
        {        /*Lambda Expression*/
                while (true) {
                        /*refresh rate*/
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        std::cout << name_ << std::this_thread::get_id() << "listening on queue " << q << std::endl; /*DELETE*/
                        if (ch->Status_queue(q)) {
                                std::cout << name_ << std::this_thread::get_id() << "newPacket" << q << std::endl; /*DELETE*/
                                this->ReceivePacket(ch->GetPacketFromQueue(q));
                        }
                }
        }        /*End of Lambda*/
        ));
        th->detach();
        threads_.push_back(th);

        while (true) {
                if (!update_) {
                        break;
                }
                /*For Tests will print out status, later will reroute packets*/
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                std::cout << name_ << std::this_thread::get_id() << "Running" << std::endl; /*DELETE*/
        }
        return true;
}
bool Client::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false; /*LATER*/
}
bool Client::RequestConnection(uint32_t target_address, channels_ channel, unsigned bandwidth) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (target_address == address_ || !interface_.first) {return false;} /*checking for connection to itself and already connected*/
        std::shared_ptr<Channel> ch;
        switch (channel) {
        case twisted_pair:
                ch = std::make_shared<Channel>(TwistedPair(bandwidth));
                break;
        default:
                return false;
        }
        std::shared_ptr<Node> target = pool_->GetNodeByAddress(target_address);
        /*initiator will always set it's transmission queue as first*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                std::pair<std::shared_ptr<Channel>, queue> interface_ = std::make_pair(ch, second);
                ch->SetDevice(std::make_shared<Node>(*this), first);
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}
bool Client::ApproveConnection(std::shared_ptr<Channel> ch, queue q) {
        /*check if connected later?*/
        std::pair<std::shared_ptr<Channel>, queue> interface_ = std::make_pair(ch,q);
        ch->SetDevice(std::make_shared<Node>(*this), second);
        return true;
}
bool Client::GeneratePacket() {
        return false; /*LATER*/
}
bool Client::RequestAddressesFromDhcp() {
        std::shared_ptr<Node> dhcp_ = pool_->GetNodeByAddress(gateway_);
        uint32_t tmp = dhcp_->CastAddress();
        /*Inform the pool about new address*/
        return tmp ? pool_->AddNode(std::make_pair(std::make_shared<Node>(*this), tmp)), address_ = tmp : false; /*check algorithm in pool*/
}
uint32_t Client::CastAddress() {
        return 0;
}
bool Client::SetAddress(uint32_t address) {
        address_ = address;
        return true;
}
bool Client::SetGateway(uint32_t gateway) {
        gateway_ = gateway;
        return true;
}
uint32_t Client::GetAddress() {
        return address_;
}
std::string Client::GetName() {
        return name_;
}
uint32_t Client::GetGateweay() {
        return gateway_;
}
uint32_t Client::GetMac() {
        return mac_;
}   