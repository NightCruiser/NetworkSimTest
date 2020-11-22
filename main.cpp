#include <iostream>
#include "Headers/SimulationController.hpp"
#include <thread> //new3
int main(int argc, char* argv[]) {
	int choice = 0;
	SimulationController controller;
	std::shared_ptr<std::thread> sim_thread; //new3
	std::fstream config("testconf.txt");
	do {
	std::cout << "1 - Load Fake config\n"
		<< "2 - Build Fake Network\n"
		<< "3 - Start Simulation\n"
		<< "4 - Stop Routers\n"
		<< "0 - Exit\n" << "Choice >>";
	std::cin >> choice;
	switch (choice){
	case 1 :
		controller.LoadCheckConfiguration(config); 
		break;
	case 2 :
		controller.BuildNetwork();
		break;
	case 3 :
		controller.StartSimulation();
		break;
	case 4 : 
		break;
	case 0 :
		std::cout << "Thanks For Watching!" << std::endl;
		break;
	default:
		std::cerr << "Wrong Choice" << std::endl;
		break;
	}
	} while (choice != 0);
	return 0;
}