#ifndef ROUTINGCORE_HPP
#define ROUTINGCORE_HPP
#include <memory>
#include "Node.hpp"
class RoutingCore : public Node {
public:
        RoutingCore(const RoutingCore&) = delete;
        RoutingCore();
        RoutingCore(std::string, uint32_t);
        bool RecievePacket();
        bool RecievePacket(std::shared_ptr<Packet>);
        bool Start();
        bool SendPacket(uint32_t, std::shared_ptr<Packet>);
        bool RequestConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>); /*Here the connection initiator should specify recieve/transmit queues of channel*/
        bool ApproveConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>);
        bool GeneratePacket();
        uint32_t RequestAddressesFromDhcp();
        uint32_t CastAddresses();
        bool SetAddress(uint32_t);
        bool SetGateway(uint32_t);
        uint32_t GetAddress();
        std::string GetName();
        uint32_t GetGateweay();
        uint32_t GetMac();
private:
        bool update_;
        uint32_t mac_;
        uint32_t gateway_;
        uint32_t address_;
        std::pair<double, double> location_;
        std::string name_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::pair<std::shared_ptr<Channel>, int>> interfaces_; /*First - pointer to a channel Second - Input queue*/
};

#endif //ROUTINGCORE_HPP