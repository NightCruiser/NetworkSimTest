#include "../Headers/TwistedPair.hpp"
#include <iostream>
TwistedPair::TwistedPair(long bandwidth) : bandwidth_(bandwidth), load_(0) {}

bool PushPacketToQueue(std::shared_ptr<Packet>, int) {

}
bool Status_queue(int) {

}
bool PopPacketFromQueue(int) {

}
std::shared_ptr<Packet> GetPacketFromQueue(int) {
        
}

void TwistedPair::SetDevice(std::shared_ptr<Node> device, queue dev_number) {

        dev_number == first ? device_one_ = device : device_two_ = device;
        
}