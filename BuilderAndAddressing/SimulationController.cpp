#include "../Headers/SimulationController.hpp"
#include <iostream>
/*MULTITHREADING!!!*/
SimulationController::SimulationController() : uploaded_(false), ready_(false), active_(false), 
        pool_(new AddressPool()) { /*allocating new pool*/ /*make_shared uses a copy constructor so "new"*/
}
void SimulationController::StartSimulation() {
        if (!ready_) {return;}
        active_ = true;
        for (auto i : sim_nodes_) {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Creating thread for Node: " << i.first->GetName() << std::endl;
                std::shared_ptr<std::thread> th(new std::thread([&, i]() /*was make_shared*/
                {       /*Lambda*/
                        i.first->Start();
                        std::cout << "Started" << std::endl;
                }));
                th->detach();
                threads_.push_back(th);
                //i.first->Start();
                
        }
        std::cout << "FOR loop ends SimController" << std::endl; //TEST
       /* while (active_) {  //new 3 //NO NEED
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                std::cout << "SimulationStart running" << std::endl;
        }*/
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
        return true;
}

bool SimulationController::BuildNetwork(std::string test) { /*Just FOR TEST 15 clients connected to 1 router*/
        if (!uploaded_) {return false;}
        std::shared_ptr<Node> tempNode = Creator::CreateNode(router, "firstRouter", 455, std::make_pair(15,52), pool_);
        tempNode->SetAddress((uint32_t)321);
        pool_->AddNode(std::make_pair(tempNode, (uint32_t)321)); /*adding to pool*/
        /*CreateNode(nodes_ node, std::string name, uint32_t mac, std::pair<double,double> location, std::shared_ptr<AddressPool> pool)*/
        
        for (int i = 0; i < 20; i++) {
                std::cout << "Creating Node " << (i + 1) << std::endl; /*DELETE*/
                std::string name = "Client " + std::to_string(i); /*DELETE*/
                std::shared_ptr<Node> tmp = Creator::CreateNode(client, name, i, std::make_pair(15,52), pool_);
                if (tmp->RequestConnection((uint32_t)321, twisted_pair, (unsigned)2000)) {
                        std::cout << tmp->GetName() << " connected to " << tempNode->GetName() << std::endl; /*DELETE*/
                };
                pool_->AddNode(std::make_pair(tmp, i));
                sim_nodes_.push_back(std::make_pair(tmp, client));
        }

        sim_nodes_.push_back(std::make_pair(tempNode, router));
        ready_ = true;
        return true;
}

void SimulationController::StopRouters() {
        for (auto i : sim_nodes_) {
                i.first->Stop();
        }
        active_ = false; //new3
}

bool SimulationController::GetStatus() {
        return active_;
}