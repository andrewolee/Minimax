#include "minimax.h"
#include <stdio.h>

const int HEIGHT = 6;
const int  WIDTH = 7;

struct Board {
	char state[HEIGHT][WIDTH];
};

class Connect4 : public Game<Board> {
private:
	Board board;

public:
	Connect4 () {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				board.state[i][j] = '_';
			}
		}
	}

	void print_board() {
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				printf("|%c", board.state[i][j]);
			}
			printf("|\n");
		} 
		for (int i = 0; i < WIDTH; i++) {
			printf("|%i", i + 1);
		}
		printf("|\n");
	}

	void player_move() {
		int j = 0;
		do {
			printf("\nEnter column number to place chip: \n");
			scanf("%u", &j);
		} while(j < 1 || WIDTH < j);
		j--;
		int i = 0;
		while (board.state[i][j] == '_' && i < HEIGHT){
			i++;
		}
		board.state[i - 1][j] = 'o';
	}

	void set_board(Board board) {
		this->board = board;
	}

	Board get_board() {
		return board;
	}

	std::vector<Board> legal_moves (Board board, bool maximize) {
		std::vector<Board> boards;
		if (evaluate(board) != 0) {
			return boards;
		}
		for (int j = 0; j < WIDTH; j++) {
			if (board.state[0][j] == '_') {
				int i = 0;
				while (board.state[i][j] == '_' && i < HEIGHT){
					i++;
				}
				Board cpy = board;
				if (maximize) {
					cpy.state[i - 1][j] = 'x';
				} else {
					cpy.state[i - 1][j] = 'o';
				}
				boards.push_back(cpy);
			}
		}
		return boards;
	}

	int evaluate (Board board) {
		int count = 0;
		char player = '_';
		// Check for vertical wins
		for (int j = 0; j < WIDTH; j++) {
			for (int i = 0; i < HEIGHT; i++) {
				if (board.state[i][j] == player && player != '_') {
					count++;
					if (count == 4) {
						if (player == 'x') {
							return INT_MAX;
						} else {
							return INT_MIN;
						}
					}
				} else {
					player = board.state[i][j];
					count = 1;
				}
			}
		}

		count = 0;
		player = '_';
		// Check for horizontal wins
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board.state[i][j] == player && player != '_') {
					count++;
					if (count == 4) {
						if (player == 'x') {
							return INT_MAX;
						} else {
							return INT_MIN;
						}
					}
				} else {
					player = board.state[i][j];
					count = 1;
				}
			}
		}

		count = 0; 
		player = '_';
		// Check for diagonal wins
		for (int i = 0; i < HEIGHT; i++) {
			for (int k = 0; k < WIDTH && i + k < HEIGHT; k++) {
				if (board.state[i + k][k] == player && player != '_') {
					count++;
					if (count == 4) {
						if (player == 'x') {
							return INT_MAX;
						} else {
							return INT_MIN;
						}
					}
				} else {
					player = board.state[i + k][k];
					count = 1;
				}
			}
		}

		count = 0; 
		player = '_';
		// Check for diagonal wins
		for (int i = 0; i < HEIGHT; i++) {
			for (int k = 0; k < WIDTH && 0 <= i - k; k++) {
				if (board.state[i - k][k] == player && player != '_') {
					count++;
					if (count == 4) {
						if (player == 'x') {
							return INT_MAX;
						} else {
							return INT_MIN;
						}
					}
				} else {
					player = board.state[i - k][k];
					count = 1;
				}
			}
		}

		count = 0; 
		player = '_';
		// Check for diagonal wins
		for (int i = 0; i < HEIGHT; i++) {
			for (int k = 0; k < WIDTH && 0 <= i - k; k++) {
				if (board.state[i - k][k] == player && player != '_') {
					count++;
					if (count == 4) {
						if (player == 'x') {
							return INT_MAX;
						} else {
							return INT_MIN;
						}
					}
				} else {
					player = board.state[i - k][k];
					count = 1;
				}
			}
		}

		return 0;
	}
};

int main(void) {
	Connect4* connect4 = new Connect4();
	Minimax<Board> minimax = Minimax<Board>(connect4, 6);
	while (true) {
		connect4->print_board();
		connect4->player_move();
		if (connect4->evaluate(connect4->get_board()) == INT_MIN) {
			connect4->print_board();
			printf("\nYou win!\n\n:)\n\n");
			break;
		} 
		connect4->set_board(minimax.best_move(connect4->get_board(), true));
		if (connect4->evaluate(connect4->get_board()) == INT_MAX) {
			connect4->print_board();
			printf("\nYou lose!\n\n:(\n\n");
			break;
		} 
	}
}



