#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <memory>
#include "Node.hpp"
class Client : public Node {
public:
        void Stop();
        bool RecievePacket();
        bool ReceivePacket(std::shared_ptr<Packet>);
        bool Start();
        bool SendPacket(uint32_t, std::shared_ptr<Packet>);
        bool RequestConnection(uint32_t, channels_,long); /*Here the connection initiator should specify recieve/transmit queues of channel*/
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
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::shared_ptr<Packet>> packets_;
        std::shared_ptr<Channel> interface_;
        std::pair<double, double> location_;
        std::string name_;
        uint32_t mac_;
        uint32_t gateway_;
        uint32_t address_;
};
#endif //CLIENT_HPP