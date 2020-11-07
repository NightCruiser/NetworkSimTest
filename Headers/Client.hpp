#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <memory>
#include "Node.hpp"
class Client : public Node {
public:
        Client(std::string, uint32_t, std::pair<double, double>, std::shared_ptr<AddressPool>);
        void Stop();
        bool RecievePacket();
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
        bool GetStatus();        
private:
        std::mutex mtx_;
        std::string name_;
        uint32_t mac_;
        std::pair<double, double> location_;
        std::shared_ptr<AddressPool> pool_;
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::list<std::shared_ptr<Packet>> packets_;
        std::pair<std::shared_ptr<Channel>, queue> interface_;
        uint32_t gateway_;
        uint32_t address_;
        bool update_;
        std::list<std::shared_ptr<std::thread>> threads_;
};
#endif //CLIENT_HPP