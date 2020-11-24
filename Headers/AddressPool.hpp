#ifndef ADDRESSPOOL_HPP
#define ADDRESSPOOL_HPP
#include "Node.hpp" //new
/**
 * AddressPool class will contain a nodes list containing of pairs 
 * shared_ptr Node - Mac address
 * While building the network new nodes will register here
 * Used to handle the connections
*/

class Node; //forward declaration
class AddressPool {
public:
        AddressPool(); //new
        ~AddressPool() {} //new
        std::shared_ptr<Node> GetNodeByMac(const uint32_t);
        void AddNode(std::pair<std::shared_ptr<Node>, uint32_t>);
        void ClearPool();
        void PrintPool(); /*Temporary*/
private:
        std::list<std::pair<std::shared_ptr<Node>, uint32_t>> nodes_;
};
#endif //ADDRESSPOOL_HPP