#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <queue>
#include "Packet.hpp"

static const int SOL = 299792458; /*Speed of light in vacuum meters/second*/

typedef enum queues_ {first = 1, second = 2} queue; //new
class Node; //forward new
class Channel {
public:
        virtual ~Channel() {}
        virtual bool PushPacketToQueue(std::shared_ptr<Packet>, queue) = 0;
        virtual bool Status_queue(queue) = 0;
        virtual std::shared_ptr<Packet> GetPacketFromQueue(queue) = 0;
        virtual void SetDevice(std::shared_ptr<Node>, queue) = 0;
        virtual double GetPropagationDelay() = 0;
};
#endif //CHANNEL_HPP