#ifndef WIRED_HPP
#define WIRED_HPP
#include <list>
#include <memory>
#include <map>
#include "Channel.hpp"
class Wired : public Channel {
public:
        Wired(unsigned, double, double);
        bool PushPacketToQueue(std::shared_ptr<Packet>, queue);
        bool Status_queue(queue);
        std::shared_ptr<Packet> GetPacketFromQueue(queue);
        void SetDevice(std::shared_ptr<Node>, queue);
        double GetPropagationDelay();
        double GetBandwidthDelay();
        std::pair<unsigned, unsigned> GetDevicesId();
private:
        unsigned bandwidth_;
        double velocity_factor_;
        double length_;
        double mtu_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
        std::shared_ptr<Node> device_one_;
        std::shared_ptr<Node> device_two_;
};
#endif //WIRED_HPP