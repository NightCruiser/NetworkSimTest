#ifndef SIMULATIONCONTROLLER_HPP
#define SIMULATIONCONTROLLER_HPP
#include <fstream>
#include <map>
#include <set>
#include "Creator.hpp"


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
        bool LoadCheckConfiguration(std::list<std::pair<nodes_, std::string>>); /*will receive file later, now simple for multithreadinfg tests*/
        /*this will connect */
        bool LoadCheckConfiguration(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork();
        bool GetStatus();


private:
        bool uploaded_;
        bool ready_;
        bool active_;
        std::map<unsigned, std::set<double>> network_graph_; /*weighted*/
        std::map<unsigned, std::set<Event>> events_map_; /*event timings as a key*/
        std::shared_ptr<AddressPool> pool_;
        std::list<std::pair<std::shared_ptr<Node>, nodes_>> sim_nodes_;
        std::list<std::pair<nodes_, std::string>> map_nodes_;/*TEST*/
        std::list<std::shared_ptr<std::thread>> threads_;
};
#endif //SIMULATIONCONTROLLER_HPP