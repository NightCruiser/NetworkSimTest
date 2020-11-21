#ifndef SIMULATIONCONTROLLER_HPP
#define SIMULATIONCONTROLLER_HPP
#include <fstream>
#include <map>
#include <set>
#include "Creator.hpp"
/*Structure to store nodes for building network*/
struct NodeConfig {
        std::string name_;
        uint32_t address_;
        std::pair<double, double> location_;
        nodes_ type_;
        unsigned id_;
        uint32_t mac_;
};
/*Structure to store connections for building network*/
struct Connections {
        uint32_t initiator_mac_;
        uint32_t target_mac_;
        channels_ channel_;
        unsigned bandwidth_;
        unsigned length_;
};

/*Structure to store events, used in map of events*/
struct Event {
        uint32_t sender_address_;
        uint32_t target_address_;
        unsigned size_;
};

class SimulationController {
public:
        SimulationController();
        ~SimulationController() {}
        void StartSimulation();
                /*Check will be implemented*/     /*Enum nodes and name*/ /*without connections for testing*/
        bool LoadCheckConfiguration(std::fstream&);
        /*this will connect */
        bool LoadCheckConfiguration(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork();
        bool GetStatus();


private:
        bool uploaded_;
        bool ready_;
        bool active_;
        std::list<std::shared_ptr<NodeConfig>> parsed_nodes_;
        std::list<std::shared_ptr<Connections>> parsed_connections_;
        std::map<unsigned, std::set<std::pair<unsigned, double>>> network_graph_; /*weighted*/
        std::map<unsigned, std::set<std::shared_ptr<Event>>> events_map_; /*event timings as a key*/
        std::shared_ptr<AddressPool> pool_;
        std::list<std::pair<std::shared_ptr<Node>, nodes_>> sim_nodes_;
        std::list<std::shared_ptr<Node>> created_nodes_;
        std::list<std::shared_ptr<std::thread>> threads_;
};
#endif //SIMULATIONCONTROLLER_HPP