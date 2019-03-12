#include "minimax.h"

/*
	clang++ tictactoe.cpp -o tictactoe -std=c++11
*/

class Sum21 : public Game<int> {
public:
	int evaluate(int state) {
		if (state == 21) {
			return 10;
		} else {
			return -10;
		}
	}

	std::vector<int> legal_moves (int state, bool maximize) {
		std::vector<int> states;
		for (int i = 0; i < 5; i++) {
			states.push_back(state + i);
		}
		return states;
	}
};

int main (int argc, char* argv[]) {
	Sum21* sum21 = new Sum21();
	Minimax<int> minimax = Minimax<int>(sum21, 2);

	int sum = 0;

	for (int i = 0; i < 21; i++) {
		printf("sum: %i\n", sum);
		sum = minimax.best_move(sum, true);
	}
}