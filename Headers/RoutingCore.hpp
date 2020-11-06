#ifndef ROUTINGCORE_HPP
#define ROUTINGCORE_HPP
#include <memory>
#include <mutex>
#include <thread>
#include "Node.hpp"
class RoutingCore : public Node {
public:
        RoutingCore(const RoutingCore&) = delete;
        RoutingCore();
        RoutingCore(std::string, uint32_t, std::pair<double, double>, std::shared_ptr<AddressPool>);
        void Stop();
        bool ReceivePacket(std::shared_ptr<Packet>);
        bool Start();
        bool SendPacket(uint32_t, std::shared_ptr<Packet>);
        bool RequestConnection(uint32_t, channels_, unsigned); /*Here the connection initiator should specify recieve/transmit queues of channel*/
        bool ApproveConnection(std::shared_ptr<Channel>, queue);
        bool GeneratePacket();
        bool RequestAddressesFromDhcp();
        uint32_t CastAddress();
        bool SetAddress(uint32_t);
        bool SetGateway(uint32_t);
        uint32_t GetAddress();
        std::string GetName();
        uint32_t GetGateweay();
        uint32_t GetMac();
private:
        std::shared_ptr<AddressPool> pool_;
        std::mutex mtx_;
        bool update_;
        uint32_t mac_;
        uint32_t gateway_;
        uint32_t address_;
        std::pair<double, double> location_;
        std::string name_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::pair<std::shared_ptr<Channel>, queue>> interfaces_; /*First - pointer to a channel Second - Input queue*/
        std::list<std::shared_ptr<std::thread>> threads_;
        std::shared_ptr<Node> node_;
};

#endif //ROUTINGCORE_HPP