#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <queue>
#include "Packet.hpp"
#include "Node.hpp"
class Channel {
public:
        virtual ~Channel() {}
        virtual bool PushPacket_q1(std::shared_ptr<Packet>) = 0;
        virtual bool PushPacket_q2(std::shared_ptr<Packet>) = 0;
        virtual bool Status_q1() = 0;
        virtual bool Status_q2() = 0;
        virtual std::shared_ptr<Packet> PopPacket_q1(void) = 0;
        virtual std::shared_ptr<Packet> PopPacket_q2(void) = 0;
private:
        long load_;
        long bandwidth_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
};
#endif //CHANNEL_HPP