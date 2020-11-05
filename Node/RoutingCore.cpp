#include "../Headers/RoutingCore.hpp"
RoutingCore::RoutingCore() {}
RoutingCore::RoutingCore(std::string name, uint32_t mac) : name_(name), mac_(mac)  {}

RoutingCore::~RoutingCore() {}

bool RoutingCore::RecievePacket() { /*Should we inform the log?*/ /*Method for tests without controller*/
        for (auto i : interfaces_) {
                if (i.second == 1 || i.first->Status_q1()) {
                        received_packets_.push_back(i.first->PopPacket_q1()); /*Check that Channel deletes pointer*/
                }
                if (i.first->Status_q2()) {
                        received_packets_.push_back(i.first->PopPacket_q2());
                }
        }
        
}
bool RoutingCore::RecievePacket(std::shared_ptr<Packet>) {}
bool RoutingCore::Start() {}
bool RoutingCore::SendPacket(uint32_t, std::shared_ptr<Packet>) {}
bool RoutingCore::RequestConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) {} /*Here the connection initiator should specify recieve/transmit queues of channel*/
bool RoutingCore::ApproveConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) {}
bool RoutingCore::GeneratePacket() {}
uint32_t RoutingCore::RequestAddressesFromDhcp() {}
uint32_t RoutingCore::CastAddresses() {}
bool RoutingCore::SetAddress(uint32_t) {}
bool RoutingCore::SetGateway(uint32_t) {}
uint32_t RoutingCore::GetAddress() {}
std::string RoutingCore::GetName() {}
uint32_t RoutingCore::GetGateweay() {}
uint32_t RoutingCore::GetMac() {}
