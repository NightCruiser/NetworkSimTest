#ifndef SIMULATIONCONTROLLER_HPP
#define SIMULATIONCONTROLLER_HPP
#include <fstream>
#include <map>
#include <set>
#include "Creator.hpp"


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
        std::list<std::pair<std::shared_ptr<Node>, nodes_>> sim_nodes_;
        std::list<std::shared_ptr<Node>> created_nodes_;
        std::list<std::shared_ptr<std::thread>> threads_;
};
#endif //SIMULATIONCONTROLLER_HPP