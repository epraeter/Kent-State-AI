#include "hmm.hpp"

int main() {
	int states;
	int emissions;

	std::cout << "Enter # of states: ";
	std::cin >> states;
	std::cout << '\n';

	std::cout << "Enter # of emissions: ";
	std::cin >> emissions;
	std::cout << '\n';

	HMM hmm(states, emissions);

	hmm.TransitionMatrix();		//set transition matrix
	hmm.EmissionsMatrix();		//set emissions matrix
	hmm.SetObservations(); // set obser
	hmm.InitialValues();	//set inital values for states. equals to 0
	std::cout << hmm << std::endl;	// print fancy stuff
	hmm.GetPaths();

	return 0;
}