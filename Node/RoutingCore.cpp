#include "../Headers/RoutingCore.hpp"
#include <chrono>
#include <iostream> /*delete after tests*/
RoutingCore::RoutingCore() {}
/*ADD Additional constructor for other functionalities LATER*/
RoutingCore::RoutingCore(unsigned id, std::string name, uint32_t address, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), mac_(mac), location_(location), pool_(pool)  {}

RoutingCore::~RoutingCore() {
        std::cout << "Deleting RoutingCore " << id_ << std::endl;
}

bool RoutingCore::ReceivePacket(std::shared_ptr<Packet> packet) { /*Should we inform the log?*/ /*Method for tests without controller*/

        received_packets_.push_back(packet);

        return true;
}

bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false;
} /*LATER*/

bool RoutingCore::RequestConnection(std::shared_ptr<Node>& target, std::shared_ptr<Connections>& connection) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (connection->target_mac_ == mac_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr; /*will become shared, no need to delete*/
        /*creating channel*/
        tmpChannelPtr = new Wired(connection->bandwidth_, connection->velocity_, connection->length_); /*was make_shared*/
        std::shared_ptr<Channel> ch(tmpChannelPtr); /*making shared ptr*/

        /*initiator will always set it's transmission queue as first*/
        /*If the target rejects the connection for some reason, no interface will be created*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                 /*queue specified in interfaces is always input queue*/
                 /*we send data using first queue and receive using second, as initiator*/
                unsigned i = interfaces2_.size();
                /*using enum here just to determine first or second device it will be, we don't send a queue to channel*/
                ch->SetDevice(this, first); /*was make_shared*/
                /*Adding new connection to interface map, need some refactor because 
                 It is necessary to know WHO is connected, or maybe it's channel's task?*/
                std::pair<unsigned, std::pair<std::shared_ptr<Channel>, queue>> interface = std::make_pair(i, std::make_pair(ch, second));
                interfaces2_.insert(interface);
                return true;
        }
       return false;
}



bool RoutingCore::ApproveConnection(std::shared_ptr<Channel>& ch, queue q) {
         /*check here if connected later?(not implemented yet)*/

        /*creating an interface*/
        unsigned i = interfaces2_.size(); /*needed to set a map's key (port number) existing will always be size -1*/
        std::pair<unsigned, std::pair<std::shared_ptr<Channel>, queue>> interface = std::make_pair(i, std::make_pair(ch, q));
        /*setting the device to a channel, second because first is initiator*/
        ch->SetDevice(this, second);
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

double RoutingCore::GetChannelWeight(unsigned id) {
        std::pair<double, double> ids;
        /*Find if there a connection with a node with the given id*/
        for (auto i : interfaces2_) {
                ids = i.second.first->GetDevicesId();
                /*we don't know first or second, it depends on who was an initiator of connection*/
                if (ids.first == id || ids.second == id) {
                        return i.second.first->GetPropagationDelay() + i.second.first->GetBandwidthDelay(); 
                }       
        }
        
        return 9999.9999; /*NO CONNECTION*/
}

void RoutingCore::Disconnect() {
        interfaces2_.clear(); /*??? TEST*/
}