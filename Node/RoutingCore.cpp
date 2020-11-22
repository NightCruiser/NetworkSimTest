#include "../Headers/RoutingCore.hpp"
#include <chrono>
#include <iostream> /*delete after tests*/
RoutingCore::RoutingCore() {}
/*ADD Additional constructor for other functionalities*/
RoutingCore::RoutingCore(unsigned id, std::string name, uint32_t address, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), mac_(mac), location_(location), pool_(pool)  {}

RoutingCore::~RoutingCore() {
}

bool RoutingCore::ReceivePacket(std::shared_ptr<Packet> packet) { /*Should we inform the log?*/ /*Method for tests without controller*/

        received_packets_.push_back(packet);

        return true;
}

bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false;
} /*LATER*/

bool RoutingCore::RequestConnection(std::shared_ptr<Node> target, std::shared_ptr<Connections> connection) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (connection->target_mac_ == mac_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr; /*will become shared, no need to delete*/
        /*creating channel*/
        tmpChannelPtr = new Wired(connection->bandwidth_, connection->velocity_, connection->length_); /*was make_shared*/
        std::shared_ptr<Channel> ch(tmpChannelPtr); /*making shared ptr*/

        /*initiator will always set it's transmission queue as first*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                unsigned i = interfaces2_.size();
                std::pair<unsigned, std::pair<std::shared_ptr<Channel>, queue>> interface = std::make_pair(i, std::make_pair(ch, second));
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
                interfaces2_.insert(interface);
                return true;
        }
       return false;
}



bool RoutingCore::ApproveConnection(std::shared_ptr<Channel> ch, queue q) {
        unsigned i = interfaces2_.size();
        std::pair<unsigned, std::pair<std::shared_ptr<Channel>, queue>> interface = std::make_pair(i, std::make_pair(ch, q));
        ch->SetDevice(std::shared_ptr<Node>(this), second); /*was make_shared*/
        interfaces2_.insert(interface);
        return true;
}
bool RoutingCore::GeneratePacket() {
        /*Routing device will not generate packets*/
        return false;
}

bool RoutingCore::SetAddress(uint32_t address) {
        address_ = address;
        /*Inform the pool about new address*/
        pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), address_));
        return true;
}

uint32_t RoutingCore::GetAddress() {
        return address_;
}
std::string RoutingCore::GetName() {
        return name_;
}

uint32_t RoutingCore::GetMac() {
        return mac_;
}
unsigned RoutingCore::GetId() {
        return id_;
}

double RoutingCore::GetChannelWeight() {
        
        return 0.35; /*FAKE*/
}
