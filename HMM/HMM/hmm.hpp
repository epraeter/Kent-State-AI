#ifndef AI_HMM
#define AI_HMM

#include <list>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <vector>
#include <string>


class HMM {
private:
	int num_states;
	int num_emissions;
	int num_observations;
	std::map<int, double> init_value_map;		// Initial values
	std::map<std::string, double> path_prob;	// probabilities of paths for set of observations
	double** transitions;						// state matrix
	double** emissions;							// emissions and state matrix
	int* observations;

public:
	HMM();
	HMM(int, int); // int = number of states and emissions the user enters at runtime
	~HMM();

	void EmissionsMatrix();
	void TransitionMatrix();
	void SetObservations();
	void InitialValues();

	void GetProb(std::string, double, int, int);
	void GetPaths();


	friend std::ostream& operator<<(std::ostream&, const HMM&); // for clean output

};

#endif