#include "../Headers/RoutingCore.hpp"
#include <chrono>
#include <iostream> /*delete after tests*/
RoutingCore::RoutingCore() {}
/*ADD Additional constructor for other functionalities*/
RoutingCore::RoutingCore(unsigned id, std::string name, uint32_t address, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), location_(location), pool_(pool)  {}

RoutingCore::~RoutingCore() {
}

bool RoutingCore::ReceivePacket(std::shared_ptr<Packet> packet) { /*Should we inform the log?*/ /*Method for tests without controller*/

        mtx_.lock();

        received_packets_.push_back(packet);

        mtx_.unlock();
        return true;
}


bool RoutingCore::GetStatus() {
        mtx_.lock();
        return update_;
        mtx_.unlock();
}


bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false;
} /*LATER*/

/*Need REFACTOR*/
bool RoutingCore::RequestConnection(uint32_t target_address, channels_ channel, unsigned bandwidth, double vf, double length) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (target_address == address_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr;
        switch (channel) {
        case twisted_pair:
                tmpChannelPtr = new TwistedPair(bandwidth, vf, length); /*was make_shared*/
                break;
        default:
                return false;
        }
        std::shared_ptr<Node> target = pool_->GetNodeByAddress(target_address);
        std::shared_ptr<Channel> ch(tmpChannelPtr); /*was make_shared*/
        /*initiator will always set it's transmission queue as first*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                std::pair<std::shared_ptr<Channel>, queue> interface = std::make_pair(ch, second);
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
                interfaces_.push_back(interface);
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}
bool RoutingCore::RequestConnection(std::shared_ptr<Node> target, channels_ channel, unsigned bandwidth, double vf, double length) { 
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
                std::pair<std::shared_ptr<Channel>, queue> interface = std::make_pair(ch, second);
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
                interfaces_.push_back(interface);
                gateway_ = target->GetAddress();
                return true;
        }
       return false;
}

bool RoutingCore::ApproveConnection(std::shared_ptr<Channel> ch, queue q) {
        std::pair<std::shared_ptr<Channel>, queue> interface = std::make_pair(ch,q);
        ch->SetDevice(std::shared_ptr<Node>(this), second); /*was make_shared*/
        interfaces_.push_back(interface);
        return true;
}
bool RoutingCore::GeneratePacket() {
        /*Routing device will not generate packets*/
        return false;
}
bool RoutingCore::RequestAddressesFromDhcp() {
        std::shared_ptr<Node> dhcp_ = pool_->GetNodeByAddress(gateway_);
        uint32_t tmp = dhcp_->CastAddress();
        /*Inform the pool about new address*/           /*was make_shared*/
        return tmp ? pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), tmp)), address_ = tmp : false; /*check algorithm in pool*/
}
uint32_t RoutingCore::CastAddress() {
        if (node_) {
                return node_->CastAddress();
        }
        return 0;
}
bool RoutingCore::SetAddress(uint32_t address) {
        address_ = address;
        /*Inform the pool about new address*/
        pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), address_));
        return true;
}
bool RoutingCore::SetGateway(uint32_t gateway) {
        gateway_ = gateway;
        return true;
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
unsigned RoutingCore::GetId() {
        return id_;
}

double RoutingCore::GetChannelWeight() {
        return 0.;
}
