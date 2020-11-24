#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <queue>
#include "Packet.hpp"

/**
 * Channel class is an interface for channel (link) classes
 * such as Wired and maybe Wireless in the future
 * */
static const double SOL = 299792.458; /*Speed of light in vacuum meters/millisecond*/

typedef enum queues_ {first = 1, second = 2} queue; //new
class Node; //forward new
class Channel {
public:
        virtual ~Channel() {}
        virtual bool PushPacketToQueue(std::shared_ptr<Packet>, queue) = 0;
        virtual bool Status_queue(queue) = 0;
        virtual std::shared_ptr<Packet> GetPacketFromQueue(queue) = 0;
        virtual void SetDevice(Node*, queue) = 0;
        virtual double GetPropagationDelay() = 0;
        virtual double GetBandwidthDelay() = 0;
        virtual std::pair<unsigned, unsigned> GetDevicesId() = 0;
};
#endif //CHANNEL_HPP