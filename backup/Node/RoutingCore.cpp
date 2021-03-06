#include "../Headers/RoutingCore.hpp"
#include <chrono>
#include <iostream> /*delete after tests*/
RoutingCore::RoutingCore() {}
/*ADD Additional constructor for other functionalities*/
RoutingCore::RoutingCore(std::string name, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) : name_(name), mac_(mac), location_(location), pool_(pool)  {}

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
        return true;
}

void RoutingCore::Stop() {
        update_ = true;
}

bool RoutingCore::GetStatus() {
        mtx_.lock();
        return update_;
        mtx_.unlock();
}

bool RoutingCore::Start() {
        update_ = false;
       if (interfaces_.size() == 0) {
               return false;
       }
       int x = 1; //TEST
       /*Creating threads for each interface port, using lambda expression specifying the behavior*/
       for (auto i : interfaces_) {
               std::this_thread::sleep_for(std::chrono::milliseconds(300)); /*delay on creating threads*/
                std::cout << name_ << "Creating thread" << x << std::endl; /*DELETE*/
                ++x; //TEST
               std::shared_ptr<std::thread> th(new std::thread([&]()                
               {        /*Lambda Expression*/
                       queue queue_ = i.second;
                       std::shared_ptr<Channel> ch = i.first;
                       while (true) {
                               if (this->GetStatus()) {break;}
                               /*refresh rate*/
                                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                                std::cout << name_ << std::this_thread::get_id() << " listening on queue " << queue_ << std::endl; /*DELETE*/
                                if (ch->Status_queue(queue_)) {
                                        std::cout << name_ << std::this_thread::get_id() << "newPacket" << queue_ << std::endl; /*DELETE*/
                                        this->ReceivePacket(ch->GetPacketFromQueue(queue_));
                                }
                       }
               }        /*End of Lambda*/
               ));
               std::this_thread::sleep_for(std::chrono::milliseconds(10)); //TEST //don't know why but without it SegFault
                                                                           //Need to figure this out     
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

bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false;
} /*LATER*/

/*Need REFACTOR*/
bool RoutingCore::RequestConnection(uint32_t target_address, channels_ channel, unsigned bandwidth) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (target_address == address_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr;
        switch (channel) {
        case twisted_pair:
                tmpChannelPtr = new TwistedPair(bandwidth); /*was make_shared*/
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
