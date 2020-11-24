#include "../Headers/Client.hpp"
#include <iostream> /*DELETE*/

/*Client's constructor*/
Client::Client(unsigned id, std::string name, uint32_t address, uint32_t mac, std::pair<double, double> location, std::shared_ptr<AddressPool> pool) 
        : id_(id), name_(name), address_(address), mac_(mac), location_(location), pool_(pool) {
                std::cout << "creatingClient" << std::endl;
        }

Client::~Client() {
        std::cout << "Deleting Client " << id_ << std::endl;
}
bool Client::ReceivePacket(std::shared_ptr<Packet> packet) {
        /*NOT IMPLEMENTED*/
        return true;
}


bool Client::SendPacket(uint32_t, std::shared_ptr<Packet>) {
        /*NOT IMPLEMENTED*/
        /*WILL SEND USING OPPOSITE QUEUE, interface queue is for receiving*/
        return false; /*LATER*/
}

bool Client::RequestConnection(std::shared_ptr<Node>& target, std::shared_ptr<Connections>& connection) { 
        /*Here the connection initiator should specify recieve/transmit queues of channel*/
        if (connection->target_mac_ == mac_) {return false;} /*checking for connection to itself*/
        Channel *tmpChannelPtr; /*will become shared, no need to delete*/
        /*creating channel*/
        tmpChannelPtr = new Wired(connection->bandwidth_, connection->velocity_, connection->length_); 
        /*making shared pointer from normal*/
        std::shared_ptr<Channel> ch(tmpChannelPtr);

        /*initiator will always set it's transmission queue as first*/
        /*If the target rejects the connection for some reason, no interface will be created*/
        if (target->ApproveConnection(ch, first)) {
                 /*initiator will listen the second queue*/
                 /*queue specified in interfaces is always input queue*/
                 /*we send data using first queue and receive using second, as initiator*/
                interface_ = std::make_pair(ch, second);
                /*using enum here just to determine first or second device it will be, we don't send a queue to channel*/
                ch->SetDevice(this, first); /*was make_shared*/
                return true;
        }
       return false;
}

bool Client::ApproveConnection(std::shared_ptr<Channel>& ch, queue q) {
        /*check here if connected later?(not implemented yet)*/

        /*creating an interface*/
        std::pair<std::shared_ptr<Channel>, queue> interface_ = std::make_pair(ch,q);

        /*setting the device to a channel, second because first is initiator*/
        ch->SetDevice(this, second); 
        return true;
}
bool Client::GeneratePacket() {
        return false; /*LATER*/
}

bool Client::SetAddress(uint32_t address) {
        address_ = address;
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
double Client::GetChannelWeight(unsigned id) {
        std::pair<double, double> ids = interface_.first->GetDevicesId();
        /*Check if nodes connected*/
        /*we don't know first or second, it depends on who was an initiator of connection*/
        if (ids.first != id && ids.second != id) {
                return 9999.9999; /*NO connection Impossible route*/
        }
        return interface_.first->GetPropagationDelay() + interface_.first->GetBandwidthDelay();

}

void Client::Disconnect() {
        interface_.first = nullptr; /*??? TEST*/
}