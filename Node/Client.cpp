#include "../Headers/Client.hpp"
Client::Client() {}
void Client::Stop() {

}
bool Client::RecievePacket() {

}
bool Client::ReceivePacket(std::shared_ptr<Packet>) {

}
bool Client::Start() {

}
bool Client::SendPacket(uint32_t, std::shared_ptr<Packet>) {

}
bool Client::RequestConnection(uint32_t, channels_,long){ /*Here the connection initiator should specify recieve/transmit queues of channel*/

}
bool Client::ApproveConnection(std::shared_ptr<Channel>, queue) {

}
bool Client::GeneratePacket() {

}
bool Client::RequestAddressesFromDhcp() {

}
uint32_t Client::CastAddress() {

}
bool Client::SetAddress(uint32_t) {

}
bool Client::SetGateway(uint32_t) {

}
uint32_t Client::GetAddress() {

}
std::string Client::GetName() {

}
uint32_t Client::GetGateweay() {

}
uint32_t Client::GetMac() {
        
}   