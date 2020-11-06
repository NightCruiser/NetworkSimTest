#include "../Headers/SimulationController.hpp"
#include <iostream>
/*MULTITHREADING!!!*/
SimulationController::SimulationController() : uploaded_(false), ready_(false), active_(false) {}
void SimulationController::StartSimulation() {
        if (!ready_) {return;}
        active_ = true;
        for (auto i : sim_nodes_) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Creating thread for Node" << std::endl;
                std::shared_ptr<std::thread> th = std::make_shared<std::thread>([&]()
                {       /*Lambda*/
                        i.first->Start();
                });
                i.first->Start();
        }
}
                                /*Enum nodes and name*/ /*without connections for testing*/
bool SimulationController::LoadCheckConfiguration(std::list<std::pair<nodes_, std::string>> map_nodes) { /*will receive file later with locations and so on, now simple for multithreadinfg tests*/
        return false; /*disable using*/
}

bool SimulationController::BuildNetwork() {
        return false; /*disable using*/
}

bool SimulationController::LoadCheckConfiguration(std::string test) {
        uploaded_ = true;
}

bool SimulationController::BuildNetwork(std::string test) { /*Just FOR TEST 15 clients connected to 1 router*/
        if (!uploaded_) {return false;}
        std::shared_ptr<AddressPool> tmpPool = std::make_shared<AddressPool>(pool_);
        std::shared_ptr<Node> tempNode = Creator::CreateNode(router, "firstRouter", 455, std::make_pair(15,52), tmpPool);
        tempNode->SetAddress((uint32_t)321);
        pool_.AddNode(std::make_pair(tempNode, (uint32_t)321));
        /*CreateNode(nodes_ node, std::string name, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool)*/
        
        for (int i = 0; i < 15; i++) {
                std::shared_ptr<Node> tmp = Creator::CreateNode(client, "Client" + i, i, std::make_pair(15,52), tmpPool);
                tmp->RequestConnection((uint32_t)321, twisted_pair, (unsigned)2000);
                pool_.AddNode(std::make_pair(tmp, i));
                sim_nodes_.push_back(std::make_pair(tmp, client));
        }

        sim_nodes_.push_back(std::make_pair(tempNode, router));
        ready_ = true;
}

void SimulationController::StopRouters() {
        for (auto i : sim_nodes_) {
                i.first->Stop();
        }
}

bool SimulationController::GetStatus() {
        return active_;
}