#ifndef SIMULATIONCONTROLLER_HPP
#define SIMULATIONCONTROLLER_HPP
#include <fstream>
#include <map>
#include <set>
#include "Creator.hpp"
#include "NetworkGraph.hpp"

/**
 * The Controller class, that handles configuration files reading and checking,
 * network building and the simulation
 * */

class SimulationController {
public:
        SimulationController();
        ~SimulationController() {}
        void StartSimulation();
                /*Check will be implemented*/     /*Enum nodes and name*/ /*without connections for testing*/
        bool LoadCheckConfiguration(std::fstream&);
        /*this will connect */
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
        std::list<std::shared_ptr<Node>> created_nodes_;
        NetworkGraph graph_;
};
#endif //SIMULATIONCONTROLLER_HPP