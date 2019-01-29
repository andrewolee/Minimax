#include "minimax.h"

typedef struct {
	char board[3][3];
} board;

class TicTacToe : public Game<board> {
public:
	void initial () {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				state.board[i][j] = 0;
			}
		}
	}
};

int main (int argc, char* argv[]) {

}