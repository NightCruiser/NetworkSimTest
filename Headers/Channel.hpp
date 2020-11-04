#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <queue>
#include "Packet.hpp"
#include "Node.hpp"
class Channel {
public:
        virtual ~Channel() {}
        virtual bool PushPacket(Packet&) = 0;
        virtual bool PopPacket(void) = 0;
private:
        long load_;
        long bandwidth_;
        std::queue<Packet> packets_;
};
#endif //CHANNEL_HPP