#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <queue>
#include "Packet.hpp"
typedef enum queues_ {first = 1, second = 2} queue;
class Channel {
public:
        virtual ~Channel() {}
        virtual bool PushPacketToQueue(std::shared_ptr<Packet>, queue) = 0;
        virtual bool Status_queue(queue) = 0;
        virtual std::shared_ptr<Packet> GetPacketFromQueue(queue) = 0;
        virtual void SetDevice(std::shared_ptr<Node>, queue) = 0;
};
#endif //CHANNEL_HPP