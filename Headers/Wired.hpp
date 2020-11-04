#ifndef WIRED_HPP
#define WIRED_HPP
#include "Channel.hpp"
class Wired : public Channel {
private:
        Node& device_one_;
        Node& device_two_;
};
#endif //WIRED_HPP