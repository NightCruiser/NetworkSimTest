#ifndef SIMULATIONCONTROLLER_HPP
#define SIMULATIONCONTROLLER_HPP
#include <fstream>
#include "Creator.hpp"
class SimulationController {
public:
        SimulationController();
        ~SimulationController();
        void StartSimulation();
                /*Check will be implemented*/     /*Enum nodes and name*/ /*without connections for testing*/
        bool LoadCheckConfiguration(std::list<std::pair<nodes_, std::string>>); /*will receive file later, now simple for multithreadinfg tests*/
        /*this will connect */
        bool LoadCheckConfiguration(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork(std::string); /*JUST FOR TESTING DELETE*/
        bool BuildNetwork();
        void StopRouters();
        bool GetStatus();


private:
        AddressPool pool_;
        std::list<std::pair<std::shared_ptr<Node>, nodes_>> sim_nodes_;
        std::list<std::pair<nodes_, std::string>> map_nodes_;/*TEST*/
        bool uploaded_;
        bool ready_;
        std::list<std::shared_ptr<std::thread>> threads_;
        bool active_;
};
#endif //SIMULATIONCONTROLLER_HPP