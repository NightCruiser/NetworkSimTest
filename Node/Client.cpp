#include "../Headers/Client.hpp"
#include <iostream> /*DELETE*/
/*MULTITHREADING*/
Client::Client(unsigned id, std::string name, uint32_t address, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), mac_(mac), location_(location), pool_(pool) {}

bool Client::ReceivePacket(std::shared_ptr<Packet> packet) {
        received_packets_.push_back(packet);
        packet->Handshake(address_); //what if timed out?
        return true;
}


bool Client::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        return false; /*LATER*/
}

bool Client::RequestConnection(std::shared_ptr<Node> target, std::shared_ptr<Connections> connection) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (connection->target_mac_ == mac_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr; /*will become shared, no need to delete*/
        /*creating channel*/
        tmpChannelPtr = new Wired(connection->bandwidth_, connection->velocity_, connection->length_); /*was make_shared*/
        std::shared_ptr<Channel> ch(tmpChannelPtr); /*was make_shared*/

        /*initiator will always set it's transmission queue as first*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                interface_ = std::make_pair(ch, second);
                ch->SetDevice(std::shared_ptr<Node>(this), first); /*was make_shared*/
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

bool Client::SetAddress(uint32_t address) {
        address_ = address;
        pool_->AddNode(std::make_pair(std::shared_ptr<Node>(this), address_));
        return true;
}

uint32_t Client::GetAddress() {
        return address_;
}
std::string Client::GetName() {
        return name_;
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