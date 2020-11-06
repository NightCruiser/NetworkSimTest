#include "../Headers/TwistedPair.hpp"
#include <iostream>
TwistedPair::TwistedPair(long bandwidth) : bandwidth_(bandwidth * 2), load_(0) {} /*x2 for full duplex*/

bool TwistedPair::PushPacketToQueue(std::shared_ptr<Packet> packet, queue q) {
        q == first ? packets_q1_.push(packet) : packets_q2_.push(packet);
}
bool TwistedPair::Status_queue(queue) {

}
bool TwistedPair::PopPacketFromQueue(queue) {

}
std::shared_ptr<Packet> TwistedPair::GetPacketFromQueue(queue) {
        
}

void TwistedPair::SetDevice(std::shared_ptr<Node> device, queue dev_number) {

        dev_number == first ? device_one_ = device : device_two_ = device;
        
}