#ifndef TWISTEDPAIR_HPP
#define TWISTEDPAIR_HPP
#include "Wired.hpp"
class TwistedPair : public Wired {
public:
        TwistedPair(long);
        bool PushPacketToQueue(std::shared_ptr<Packet>, queue);
        bool Status_queue(queue);
        bool PopPacketFromQueue(queue);
        std::shared_ptr<Packet> GetPacketFromQueue(queue);
        void SetDevice(std::shared_ptr<Node>, queue);
private:
        long load_;
        long bandwidth_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
        std::shared_ptr<Node> device_one_;
        std::shared_ptr<Node> device_two_;
        
};
#endif //TWISTEDPAIR_HPP