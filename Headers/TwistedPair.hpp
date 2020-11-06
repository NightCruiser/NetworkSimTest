#ifndef TWISTEDPAIR_HPP
#define TWISTEDPAIR_HPP
#include <thread>
#include <mutex>
#include <list>
#include "Wired.hpp"

 /*MULTITHREADING!!!*/
class TwistedPair : public Wired {
public:
        TwistedPair(unsigned);
        bool PushPacketToQueue(std::shared_ptr<Packet>, queue);
        bool Status_queue(queue);
        std::shared_ptr<Packet> GetPacketFromQueue(queue);
        void SetDevice(std::shared_ptr<Node>, queue);
        void DecreaseLoad(queue, unsigned);
private:
        std::mutex ch_mtx_;
        unsigned load_q1_;
        unsigned load_q2_;
        unsigned bandwidth_;
        std::queue<std::shared_ptr<Packet>> packets_q1_;
        std::queue<std::shared_ptr<Packet>> packets_q2_;
        std::shared_ptr<Node> device_one_;
        std::shared_ptr<Node> device_two_;
        std::list<std::shared_ptr<std::thread>> threads_;
        
};
#endif //TWISTEDPAIR_HPP