#include "../Headers/TwistedPair.hpp"
#include <iostream>
/*MULTITHREADING!!!*/
TwistedPair::TwistedPair(unsigned bandwidth) : bandwidth_(bandwidth * 2), load_q1_(0), load_q2_(0) { /*x2 for full duplex*/
        threads_.clear();
}

void TwistedPair::DecreaseLoad(queue q, unsigned size) { 
        
}
bool TwistedPair::PushPacketToQueue(std::shared_ptr<Packet> packet, queue q) {
        
        return false;
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