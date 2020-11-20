#include "../Headers/Client.hpp"
#include <iostream> /*DELETE*/
/*MULTITHREADING*/
Client::Client(unsigned id, std::string name, uint32_t address, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), location_(location), pool_(pool) {}

bool Client::ReceivePacket(std::shared_ptr<Packet> packet) {
        received_packets_.push_back(packet);
        packet->Handshake(address_); //what if timed out?
        return true;
}

bool Client::GetStatus() {
        //mtx_.lock();
        return update_;
        //mtx_.unlock();
}

bool Client::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false; /*LATER*/
}
bool Client::RequestConnection(uint32_t target_address, channels_ channel, unsigned bandwidth, double vf, double length) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        std::cout << "RequestConnectionCalled" << std::endl; /*DELETE*/
        if (target_address == address_ || interface_.first) {return false;} /*checking for connection to itself and already connected*/
        Channel *tmpChannel;
        switch (channel) {
        case twisted_pair:
                tmpChannel = new TwistedPair(bandwidth, vf, length);
                break;
        default:
                return false;
        }
        std::shared_ptr<Channel> ch(tmpChannel); /*putting pointer to shared ptr instance*/
        std::shared_ptr<Node> target = pool_->GetNodeByAddress(target_address);
        /*initiator will always set it's transmission queue as first*/
        std::cout << "Requestng ApproveConnection" << std::endl; /*DELETE*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                interface_ = std::make_pair(ch, second);
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}

bool Client::RequestConnection(std::shared_ptr<Node> target, channels_ channel, unsigned bandwidth, double vf, double length) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (target.get() == this) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr; /*will become shared, no need to delete*/
        /*creating channel*/
        switch (channel) {
        case twisted_pair:
                tmpChannelPtr = new TwistedPair(bandwidth, vf, length); /*was make_shared*/
                break;
        default:
                return false;
        }
        std::shared_ptr<Channel> ch(tmpChannelPtr); /*was make_shared*/
        /*initiator will always set it's transmission queue as first*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                interface_ = std::make_pair(ch, second);
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}
bool Client::ApproveConnection(std::shared_ptr<Channel> ch, queue q) {
        /*check if connected later?*/
        std::pair<std::shared_ptr<Channel>, queue> interface_ = std::make_pair(ch,q);
        ch->SetDevice(std::shared_ptr<Node>(this), second); /*was make_shared*/
        return true;
}
bool Client::GeneratePacket() {
        return false; /*LATER*/
}
bool Client::RequestAddressesFromDhcp() {
        std::shared_ptr<Node> dhcp_ = pool_->GetNodeByAddress(gateway_);
        uint32_t tmp = dhcp_->CastAddress();
        /*Inform the pool about new address*/
        return tmp ? pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), tmp)), address_ = tmp : false; /*check algorithm in pool*/
}                                                       /*was make_shared*/
uint32_t Client::CastAddress() {
        return 0;
}
bool Client::SetAddress(uint32_t address) {
        address_ = address;
        pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), address_));
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

unsigned Client::GetId() {
        return id_;
}

/*Propagation delay + bandwidthdelay(for mtu 1500bytes packet)*/
double Client::GetChannelWeight() {
        return interface_.first->GetPropagationDelay() + interface_.first->GetBandwidthDelay();

}