#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <memory>
#include "Node.hpp"
class Client : public Node {
private:
        std::list<std::shared_ptr<Packet>> received_packets_;
        std::shared_ptr<Channel> interface_;
        std::pair<double, double> location_;
        std::string name_;
        uint32_t mac_;
        uint32_t gateway_;
        uint32_t address_;
};
#endif //CLIENT_HPP