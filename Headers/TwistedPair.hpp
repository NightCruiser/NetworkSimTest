#ifndef TWISTEDPAIR_HPP
#define TWISTEDPAIR_HPP
#include "Wired.hpp"
class TwistedPair : public Wired {
public:
        bool PushPacket_q1(std::shared_ptr<Packet>);
        bool PushPacket_q2(std::shared_ptr<Packet>);
        bool Status_q1();
        bool Status_q2();
        std::shared_ptr<Packet> PopPacket_q1(void);
        std::shared_ptr<Packet> PopPacket_q2(void);
private:
        long load_;
        long bandwidth_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
};
#endif //TWISTEDPAIR_HPP