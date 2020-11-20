#include "../Headers/TwistedPair.hpp"
#include <iostream>
/*MULTITHREADING!!!*/
TwistedPair::TwistedPair(unsigned bandwidth, double vf, double length) 
        : bandwidth_(bandwidth), bandwidth_q1_(bandwidth), bandwidth_q2_(bandwidth), velocity_factor_(vf), length_(length), mtu_(0.0015) {
        threads_.clear();
}

void TwistedPair::DecreaseLoad(queue q, unsigned size) { 
        
}
bool TwistedPair::PushPacketToQueue(std::shared_ptr<Packet> packet, queue q) {
        
        return false;
}

double TwistedPair::GetPropagationDelay() {
        return length_ / (SOL * velocity_factor_);
}

double TwistedPair::GetBandwidthDelay() {
        return mtu_ / bandwidth_;
}
bool TwistedPair::Status_queue(queue q) {
        /*hard to read sequence, ternary operators check if there any packet in given queue*/
        return q == first ? packets_q1_.front() ? true : false : packets_q2_.front() ? true : false; 
}

std::shared_ptr<Packet> TwistedPair::GetPacketFromQueue(queue q) {
        std::shared_ptr<Packet> packet = q == first ? packets_q1_.front() : packets_q2_.front();
        q == first ? packets_q1_.pop() : packets_q2_.pop();
        return packet;
}

void TwistedPair::SetDevice(std::shared_ptr<Node> device, queue dev_number) {

        dev_number == first ? device_one_ = device : device_two_ = device;
        
}