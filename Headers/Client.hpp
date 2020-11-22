#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <memory>
#include "Node.hpp"
class Client : public Node {
public:
        Client(unsigned, std::string, uint32_t, uint32_t, std::pair<double, double>, std::shared_ptr<AddressPool>);
        bool ReceivePacket(std::shared_ptr<Packet>);
        bool SendPacket(uint32_t, std::shared_ptr<Packet>);
        bool RequestConnection(std::shared_ptr<Node>, std::shared_ptr<Connections>); /*Here the connection initiator should specify recieve/transmit queues of channel*/
        bool ApproveConnection(std::shared_ptr<Channel>, queue);
        bool GeneratePacket();
        bool SetAddress(uint32_t);
        uint32_t GetAddress();
        std::string GetName();
        uint32_t GetMac();
        unsigned GetId();   
        double GetChannelWeight();
private:
        unsigned id_;
        std::string name_;
        uint32_t address_;
        uint32_t mac_;
        std::pair<double, double> location_;
        std::shared_ptr<AddressPool> pool_;
        bool update_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::shared_ptr<Packet>> packets_;
        std::pair<std::shared_ptr<Channel>, queue> interface_;
};
#endif //CLIENT_HPP