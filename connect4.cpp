#include "minimax.h"
#include <stdio.h>

#define O_WIN INT_MIN
#define X_WIN INT_MAX

const int HEIGHT = 6;
const int  WIDTH = 7;

enum Chip {None, X, O};

struct Board {
    Chip state[WIDTH][HEIGHT];
    // The last move played, for easier win/loss checking
    Chip chip;
    int x, y;
};

class Connect4 : public Game<Board> {
private:
    Board board;

public:
    Connect4 () {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                board.state[x][y] = None;
            }
        }
    }

    void print_board() {
        for (int i = 0; i < 10; i++) {
            printf("\n");
        }
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                printf("|");
                switch (board.state[x][y]) {
                    case None:
                        printf("_");
                        break;
                    case X:
                        printf("X");
                        break;
                    case O:
                        printf("O");
                }
            }
            printf("|\n");
        } 
        for (int x = 1; x < WIDTH + 1; x++) {
            printf("|%i", x);
        }
        printf("|\n");
    }

    void player_move() {
        int x = 0;
        do {
            printf("\nEnter column number to place chip: \n");
            scanf("%u", &x);
        } while(x < 1 || WIDTH < x);
        x--;
        int y = 0;
        while (board.state[x][y] == None && y < HEIGHT){
            y++;
        }
        y--;
        board.state[x][y] = O;
        board.x = x;
        board.y = y;
        board.chip = O;
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
        for (int x = 0; x < WIDTH; x++) {
            if (board.state[x][0] == None) {
                int y = 0;
                while (board.state[x][y] == None && y < HEIGHT){
                    y++;
                }
                y--;
                Board cpy = board;
                Chip chip = maximize ? X : O;
                cpy.state[x][y] = chip;
                cpy.chip = chip;
                cpy.x = x;
                cpy.y = y;
                boards.push_back(cpy);
            }
        }
        return boards;
    }

    int evaluate (Board board) {
        // Vertical wins
        int count = 0;
        for (int y = std::max(0, board.y - 3); 
            y < std::min(HEIGHT, board.y + 4); y++) {
            if (board.state[board.x][y] == board.chip) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                return board.chip == O ? O_WIN : X_WIN;
            }
        }
        // Horizontal wins
        count = 0;
        for (int x = std::max(0, board.x - 3); 
            x < std::min(WIDTH, board.x + 4); x++) {
            if (board.state[x][board.y] == board.chip) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                return board.chip == O ? O_WIN : X_WIN;
            }
        }
        // Diagonal wins
        count = 0;
        for (int i = std::max(-3, std::max(-board.x, -board.y)); 
            i < std::min(4, std::min(WIDTH - board.x, HEIGHT - board.y)); i++) {
            if (board.state[board.x + i][board.y + i] == board.chip) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                return board.chip == O ? O_WIN : X_WIN;
            }
        }
        count = 0;
        for (int i = std::max(-3, std::max(board.x + 1 - WIDTH, -board.y)); 
            i < std::min(4, std::min(board.x, HEIGHT - board.y)); i++) {
            if (board.state[board.x - i][board.y + i] == board.chip) {
                count++;
            } else {
                count = 0;
            }
            if (count == 4) {
                return board.chip == O ? O_WIN : X_WIN;
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
        if (connect4->evaluate(connect4->get_board()) == O_WIN) {
            connect4->print_board();
            printf("\nYou win!\n\n:)\n\n");
            break;
        } 
        connect4->set_board(minimax.best_move(connect4->get_board(), true));
        if (connect4->evaluate(connect4->get_board()) == X_WIN) {
            connect4->print_board();
            printf("\nYou lose!\n\n:(\n\n");
            break;
        } 
    }
}

