#include "../Headers/RoutingCore.hpp"
#include <chrono>
#include <iostream> /*delete after tests*/
RoutingCore::RoutingCore() {}
RoutingCore::RoutingCore(std::string name, uint32_t mac, std::pair<double, double> location) : name_(name), mac_(mac), location_(location)  {}

RoutingCore::~RoutingCore() {
}

bool RoutingCore::ReceivePacket(std::shared_ptr<Packet> packet) { /*Should we inform the log?*/ /*Method for tests without controller*/
/*
        for (auto i : interfaces_) {
                if (i.second == 1 || i.first->Status_q1()) {
                        received_packets_.push_back(i.first->PopPacket_q1());
                }
                if (i.first->Status_q2()) {
                        received_packets_.push_back(i.first->PopPacket_q2());
                }
        }
        return true;
        */
        mtx_.lock();

        received_packets_.push_back(packet);

        mtx_.unlock();
}

bool RoutingCore::Start() {
       if (interfaces_.size() == 0) {
               return false;
       }
       /*Creating threads for each interface port, using lambda expression specifying the behavior*/
       for (auto i : interfaces_) {
               std::this_thread::sleep_for(std::chrono::milliseconds(300)); /*delay on creating threads*/
                std::cout << name_ << "Creating thread" << std::endl; /*DELETE*/
               std::shared_ptr<std::thread> th = std::make_shared<std::thread> (std::thread([&]()                
               {        /*Lambda Expression*/
                       queue queue_ = i.second;
                       std::shared_ptr<Channel> ch = i.first;
                       while (true) {
                               /*refresh rate*/
                                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                                std::cout << std::this_thread::get_id() << "listening on queue " << queue_ << std::endl; /*DELETE*/
                                if (ch->Status_queue(queue_)) {
                                        this->ReceivePacket(ch->GetPacketFromQueue(queue_));
                                        ch->PopPacketFromQueue(queue_);
                                }
                       }
               }        /*End of Lambda*/
               ));
               th->detach();
               threads_.push_back(th);
       }
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
bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {}
bool RoutingCore::RequestConnection(uint32_t target_address, channels_ channel, long bandwidth) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (target_address == address_) {return false;} /*checking for connection to itself*/
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
                std::pair<std::shared_ptr<Channel>, queue> interface = std::make_pair(ch, second);
                ch->SetDevice(std::make_shared<Node>(*this), first);
                interfaces_.push_back(interface);
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}
bool RoutingCore::ApproveConnection(std::shared_ptr<Channel> ch, queue q) {
        std::pair<std::shared_ptr<Channel>, queue> interface = std::make_pair(ch,q);
        ch->SetDevice(std::make_shared<Node>(*this), second);
        interfaces_.push_back(interface);
        return true;
}
bool RoutingCore::GeneratePacket() {}
bool RoutingCore::RequestAddressesFromDhcp() {
        pool_->GetNodeByAddress(gateway_);
}
uint32_t RoutingCore::CastAddresses() {
        if (node_) {
                return node_->CastAddresses();
        }
        return 0;
}
bool RoutingCore::SetAddress(uint32_t address) {
        address_ = address_;
}
bool RoutingCore::SetGateway(uint32_t gateway) {
        gateway_ = gateway;
}
uint32_t RoutingCore::GetAddress() {
        return address_;
}
std::string RoutingCore::GetName() {
        return name_;
}
uint32_t RoutingCore::GetGateweay() {
        return gateway_;
}
uint32_t RoutingCore::GetMac() {
        return mac_;
}
