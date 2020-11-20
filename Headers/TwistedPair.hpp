#ifndef TWISTEDPAIR_HPP
#define TWISTEDPAIR_HPP
#include <thread>
#include <mutex>
#include <list>
#include "Wired.hpp"

 /*MULTITHREADING!!!*/
class TwistedPair : public Wired {
public:
        TwistedPair(unsigned, double, double);
        bool PushPacketToQueue(std::shared_ptr<Packet>, queue);
        bool Status_queue(queue);
        std::shared_ptr<Packet> GetPacketFromQueue(queue);
        void SetDevice(std::shared_ptr<Node>, queue);
        void DecreaseLoad(queue, unsigned);
        double GetPropagationDelay();
        double GetBandwidthDelay();
private:
        unsigned bandwidth_;
        unsigned bandwidth_q1_;
        unsigned bandwidth_q2_;
        double velocity_factor_;
        double length_;
        double mtu_;
        std::mutex ch_mtx_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
        std::shared_ptr<Node> device_one_;
        std::shared_ptr<Node> device_two_;
        std::list<std::shared_ptr<std::thread>> threads_;
        
};
#endif //TWISTEDPAIR_HPP