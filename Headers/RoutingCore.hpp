#ifndef ROUTINGCORE_HPP
#define ROUTINGCORE_HPP
#include <memory>
#include <mutex>
#include <thread>
#include "Functionalities.hpp"

class AddressPool; //forward declaration new
class RoutingCore : public Functionalities {
public:
        RoutingCore(const RoutingCore&) = delete;
        RoutingCore();
        ~RoutingCore();
        RoutingCore(std::string, uint32_t, std::pair<double, double>, std::shared_ptr<AddressPool>);
        bool ReceivePacket(std::shared_ptr<Packet>);
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
        bool GetStatus();
private:
        std::mutex mtx_;
        std::string name_;
        uint32_t mac_;
        std::pair<double, double> location_;
        std::shared_ptr<AddressPool> pool_;
        bool update_;
        uint32_t gateway_;
        uint32_t address_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::pair<std::shared_ptr<Channel>, queue>> interfaces_; /*First - pointer to a channel Second - Input queue*/
        std::list<std::shared_ptr<std::thread>> threads_;
        std::shared_ptr<Node> node_;
};

#endif //ROUTINGCORE_HPP