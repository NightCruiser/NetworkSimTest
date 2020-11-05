#include "../Headers/NodeController.hpp"
NodeController::NodeController() {}
NodeController::~NodeController() {}
bool NodeController::RecievePacket() {}
bool NodeController::RecievePacket(std::shared_ptr<Packet>) {}
bool NodeController::Start() {}
bool NodeController::SendPacket(uint32_t, std::shared_ptr<Packet>) {}
bool NodeController::RequestConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) {} /*Here the connection initiator should specify recieve/transmit queues of channel*/
bool NodeController::ApproveConnection(std::shared_ptr<Node>, std::shared_ptr<Channel>) {}
bool NodeController::GeneratePacket() {}
uint32_t NodeController::RequestAddressesFromDhcp() {}
uint32_t NodeController::CastAddresses() {}
bool NodeController::SetAddress(uint32_t) {}
bool NodeController::SetGateway(uint32_t) {}
uint32_t NodeController::GetAddress() {}
std::string NodeController::GetName() {}
uint32_t NodeController::GetGateweay() {}
uint32_t NodeController::GetMac() {}