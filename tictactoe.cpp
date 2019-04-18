#include "minimax.h"
#include <stdio.h>

struct Board {
	char state[3][3];
};

class TicTacToe : public Game<Board> {
private:
	Board board;

public:
	TicTacToe () {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state[i][j] = '';
			}
		}
	}

	void print_board () {
		for (int i = 0; i < 3; i++) {
			printf("%c\n", 'a' + i);
		}
		printf("\n")
		for (int i = 0; i < 3; i++) {
			printf("%i", i);
			for (int j = 0; j < 3; j++) {
				printf(" %c", state[i][j]);
			}
			printf("\n");
		}
	}

	std::vector<Board> legal_moves(Board board, bool maximize) {
		std::vector 
	}
};