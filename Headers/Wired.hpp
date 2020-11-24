#ifndef WIRED_HPP
#define WIRED_HPP
#include <list>
#include <memory>
#include <map>
#include "Channel.hpp"

/**
 * Wired class inherited from Channel, represents any wired link
 * In our case only velocity factor matters, so we can use only 1 class
 * velocity factor specifies in a constructor
 * */

class Wired : public Channel {
public:
        Wired(unsigned, double, double);
        ~Wired();
        bool PushPacketToQueue(std::shared_ptr<Packet>, queue);
        bool Status_queue(queue);
        std::shared_ptr<Packet> GetPacketFromQueue(queue);
        void SetDevice(Node*, queue);
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
        Node* device_one_;
        Node* device_two_;
};
#endif //WIRED_HPP