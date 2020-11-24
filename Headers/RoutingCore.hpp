#ifndef ROUTINGCORE_HPP
#define ROUTINGCORE_HPP
#include <memory>
#include <mutex>
#include <thread>
#include <map>
#include <set>
#include "Functionalities.hpp"

/**
 * RoutingCore class represents a simple switch, can hold a lot of connections,
 * stored in interfaces2_ map
 * Contains routing tables 
 * */

class AddressPool; //forward declaration new
class RoutingCore : public Functionalities {
public:
        RoutingCore(const RoutingCore&) = delete;
        RoutingCore();
        ~RoutingCore();
        RoutingCore(unsigned, std::string, uint32_t, uint32_t, std::pair<double, double>, std::shared_ptr<AddressPool>);
        bool ReceivePacket(std::shared_ptr<Packet>);
        bool SendPacket(uint32_t, std::shared_ptr<Packet>);
        bool RequestConnection(std::shared_ptr<Node>&, std::shared_ptr<Connections>&); /*Here the connection initiator should specify recieve/transmit queues of channel*/
        bool ApproveConnection(std::shared_ptr<Channel>&, queue);
        bool GeneratePacket();
        bool SetAddress(uint32_t);
        uint32_t GetAddress();
        std::string GetName();
        uint32_t GetMac();
        unsigned GetId();
        double GetChannelWeight(unsigned); /*unsigned - ID of node, that requests*/
        void Disconnect();
private:
        unsigned id_;
        std::string name_;
        uint32_t address_;
        uint32_t mac_;
        std::pair<double, double> location_;
        std::shared_ptr<AddressPool> pool_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::map<unsigned, std::pair<std::shared_ptr<Channel>, queue>> interfaces2_;
        std::list<std::pair<std::shared_ptr<Channel>, queue>> interfaces_; /*OLD DELETE*/
        std::map<unsigned, std::set<uint32_t>> routing_table_;
};

#endif //ROUTINGCORE_HPP