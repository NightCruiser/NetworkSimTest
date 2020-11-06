#include "../Headers/TwistedPair.hpp"
#include <iostream>
/*MULTITHREADING!!!*/
TwistedPair::TwistedPair(unsigned bandwidth) : bandwidth_(bandwidth * 2), load_q1_(0), load_q2_(0) { /*x2 for full duplex*/
        threads_.clear();
}

void TwistedPair::DecreaseLoad(queue q, unsigned size) { /*not sure about mutex*/
        ch_mtx_.lock();
        q == first ? load_q1_ -= size : load_q2_ -= size;
        ch_mtx_.unlock();
}
bool TwistedPair::PushPacketToQueue(std::shared_ptr<Packet> packet, queue q) {
        if (packet->GetSize() <= (bandwidth_ * 2) - (q == first ? load_q1_ : load_q2_)) { /*need optimization*/
                q == first ? load_q1_ += packet->GetSize() : load_q2_ += packet->GetSize();
                /*Hopefully it will work and enables dynamic load*/
                std::shared_ptr<std::thread> th = std::make_shared<std::thread>(std::thread([&, packet,q]() 
                {       /*Lambda Expression*/
                        while (!packet->GetDeliveryStatus()) {
                                /*checks delivery status every 0.5 seconds*/
                                std::this_thread::sleep_for(std::chrono::milliseconds(500))
                                ;
                        }
                        DecreaseLoad(q, packet->GetSize());
                }));
                th->detach();
                /*What about remaining pointers to threads?*/
                threads_.push_back(th);
                q == first ? packets_q1_.push(packet) : packets_q2_.push(packet);
                return true;
                }
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