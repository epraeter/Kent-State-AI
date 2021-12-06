#include "hmm.hpp"

HMM::HMM() {
	num_states = 0;
	num_emissions = 0;
	transitions = NULL;
	emissions = NULL;
	observations = NULL;
}

HMM::HMM(int st, int em) {
	num_states = st;
	num_emissions = em;

	transitions = new double* [num_states];
	for (int i = 0; i < num_states; i++) {
		transitions[i] = new double[num_states];
	}

	emissions = new double* [num_states];
	for (int i = 0; i < num_states; i++) {
		emissions[i] = new double[num_emissions];
	}

	observations = NULL;
}

HMM::~HMM() {
	if (transitions != NULL) {
		for (int i = 0; i < num_states; i++) {
			if (transitions[i] != NULL) {
				delete[] transitions[i];
			}
		}
		delete[] transitions;
	}

	if (emissions != NULL) {
		for (int i = 0; i < num_states; i++) {
			if (emissions[i] != NULL) {
				delete[] emissions[i];
			}
		}
		delete[] emissions;
	}

	if (observations != NULL) {
		delete[] observations;
	}
}

void HMM::TransitionMatrix() {
	srand(time(NULL));

	// gets values for transition matrix less than 1 that add up to 1
	for (int i = 0; i < num_states; i++) {
		double hundred = 100.0;
		std::vector<double> weights;
		for (int j = 0; j < num_states; j++) {
			double random = rand() % 101;
			if (j == num_states - 1) {
				weights.push_back(hundred / 100.0);
			}
			else {
				if (hundred == 0) {
					weights.push_back(0.0);
				}
				else {
					if (hundred - random < 0) {
						weights.push_back(hundred / 100.0);
						hundred = 0;
					}
					else {
						weights.push_back(random / 100.0);
						hundred -= random;
					}
				}
			}
		}
		std::random_shuffle(weights.begin(), weights.end());
		for (int j = 0; j < num_states; j++) {		// sets them in the matrix
			transitions[i][j] = weights[j];
		}
	}

}

void HMM::EmissionsMatrix() {
	srand(time(NULL) * 2);
	// gets values for emissions matrix less than 1 that add up to 1
	for (int i = 0; i < num_states; i++) {
		double hundred = 100.0;
		std::vector<double> weights;
		for (int j = 0; j < num_emissions; j++) {
			double random = rand() % 101;
			if (j == num_states - 1) {
				weights.push_back(hundred / 100.0);
			}
			else {
				if (hundred == 0) {
					weights.push_back(0.0);
				}
				else {
					if (hundred - random < 0) {
						weights.push_back(hundred / 100.0);
						hundred = 0;
					}
					else {
						weights.push_back(random / 100.0);
						hundred -= random;
					}
				}
			}
		}
		std::random_shuffle(weights.begin(), weights.end());
		for (int j = 0; j < num_emissions; j++) {	// sets them in the matrix
			emissions[i][j] = weights[j];
		}
	}

}



void HMM::SetObservations() {
	std::cout << "Enter the # of observations: ";
	std::cin >> num_observations;
	std::cout << '\n';
	observations = new int[num_observations];
	for (int i = 0; i < num_observations; i++) {
		std::cout << "Enter an observation. {...}: ";
		std::cin >> observations[i];
		std::cout << '\n';
	}
}

void HMM::InitialValues() {

	double hundred = 100.0;
	std::vector<double> weights;
	for (int j = 0; j < num_states; j++) {
		double random = rand() % 101;
		if (j == num_states - 1) {
			weights.push_back(hundred / 100.0);
		}
		else {
			if (hundred == 0) {
				weights.push_back(0.0);
			}
			else {
				if (hundred - random < 0) {
					weights.push_back(hundred / 100.0);
					hundred = 0;
				}
				else {
					weights.push_back(random / 100.0);
					hundred -= random;
				}
			}
		}
	}

	std::random_shuffle(weights.begin(), weights.end());
	for (int j = 0; j < num_states; j++) {
		init_value_map.insert(std::pair<int, double>(j + 1, weights[j]));
	}

}

void HMM::GetProb(std::string seq, double odds, int cur_state, int depth) {
	if (depth == num_observations) {
		std::pair<std::string, double> temp(seq, odds);
		path_prob.insert(temp);
		return;
	}
	else {
		for (int i = 0; i < num_states; i++) {//possible next_state
			if (transitions[cur_state][i] != 0 && emissions[i][observations[depth]] != 0) {

				int seq_num = i + 1;
				std::string next_seq = seq + std::to_string(seq_num);

				odds = odds * transitions[cur_state][i] * emissions[i][observations[depth]];
				GetProb(next_seq, odds, i, depth + 1);
			}
		}
	}
}

void HMM::GetPaths() { // finds best path and displays other possible paths
	int count = 0;
	for (std::pair<int, double> init : init_value_map) {	// finds path and probability
		if (std::get<1>(init) != 0) {

			int         depth = 1;
			std::string seq = std::to_string(std::get<0>(init));
			double      odds = std::get<1>(init) * emissions[std::get<0>(init) - 1][observations[0]];
			int         cs = std::get<0>(init) - 1;


			GetProb(seq, odds, cs, depth);

			count++;
		}
	}

	//
	// outputs paths
	//

	std::cout << "\n\nPossible Paths:\n";

	std::string best_path = "";
	double probability = 0;

	for (std::pair<std::string, double> path : path_prob) {
		if (path.second > probability) {
			probability = path.second;
			best_path = path.first;
		}
		std::cout << "Path: " << path.first << " = " << path.second << '\n';
	}

	if (probability != 0) {
		std::cout << "\nMost Probable Path:\n";
		std::cout << "Path: \t\t\t" << best_path << '\n';
		std::cout << "Probability: \t" << probability << '\n';
	}
	else {
		std::cout << "Observation sequence not possible.\n";
	}

}

std::ostream& operator<<(std::ostream& out, const HMM& hmm) { // prints matrices and values
	out << "Init Values: \n";
	for (std::pair<int, double> init : hmm.init_value_map) {
		out << "{" << std::get<0>(init) << " , " << std::get<1>(init);
		out << "}\n";
	}

	out << '\n';

	out << "Observations: \n";
	for (int i = 0; i < hmm.num_observations; i++) {
		out << "{" << i << " , " << hmm.observations[i] << "}\n";
	}

	out << '\n';

	out << "Transitions Matrix: \n";
	for (int i = 0; i < hmm.num_states; i++) {
		out << '|';
		for (int j = 0; j < hmm.num_states; j++) {
			out << hmm.transitions[j][i] << '\t' << '|';
		}
		out << '\n';
	}

	out << '\n';

	out << "Emissions Matrix: \n";
	for (int i = 0; i < hmm.num_emissions; i++) {
		//out << hmm.observations[i];
		out << '|';
		for (int j = 0; j < hmm.num_states; j++) {
			out << hmm.emissions[j][i] << '\t' << '|';
		}
		out << '\n';
	}

	return out;
}

