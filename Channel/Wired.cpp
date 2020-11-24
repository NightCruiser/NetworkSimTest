#include "../Headers/Wired.hpp"
#include <iostream>
#include "../Headers/Node.hpp"

Wired::Wired(unsigned bandwidth, double vf, double length) 
        : bandwidth_(bandwidth), velocity_factor_(vf), length_(length), mtu_(0.012) {

        }

Wired::~Wired() {
        std::cout << "Deleting Channel\n";
}

bool Wired::PushPacketToQueue(std::shared_ptr<Packet> packet, queue q) {
        
        return false;
}

double Wired::GetPropagationDelay() {
        return length_ / (SOL * velocity_factor_);
}

double Wired::GetBandwidthDelay() {
        /*mtu in megabits | bandwidth in megabits*/
        return mtu_ / (bandwidth_ * 0.001) /*converting to milliseconds*/;
}
bool Wired::Status_queue(queue q) {
        /*hard to read sequence, ternary operators check if there any packet in given queue*/
        return q == first ? packets_q1_.front() ? true : false : packets_q2_.front() ? true : false; 
}

std::shared_ptr<Packet> Wired::GetPacketFromQueue(queue q) {
        std::shared_ptr<Packet> packet = q == first ? packets_q1_.front() : packets_q2_.front();
        q == first ? packets_q1_.pop() : packets_q2_.pop();
        return packet;
}

void Wired::SetDevice(Node* device, queue dev_number) {
        dev_number == first ? device_one_ = device : device_two_ = device;
        
}

std::pair<unsigned, unsigned> Wired::GetDevicesId() {
        
        return std::make_pair(device_one_->GetId(), device_two_->GetId()); /*FAKE*/
}