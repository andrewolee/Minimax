#include <vector>

template <class T>
class Game {
public:
	// score of state
	virtual int evaluate (T state) = 0;

	// vector of all legal moves from state
	virtual std::vector<T> legal_moves (T state) = 0;
};

template <class T>
class Minimax {
private:
	Game<T> *game;
	int strength; // max depth of search tree

	typedef struct {
		T state;
		int score;
	} StateScore;

	// actual minimax
	StateScore minimax (T state, int depth, bool maximize) {
		StateScore ss;
		std::vector<T> states = game->legal_moves(state);
		if (depth == strength || states.empty()) {
			ss.state = state;
			ss.score = game->evaluate(state);
			return ss;
		}
		ss.score = 0;
		ss.state = states[rand() * (states.size()) / RAND_MAX];
		for (T s : states) {
			int score = minimax(s, depth + 1, maximize).score;
			if (maximize) {
				if (score >= ss.score) {
					ss.score = score;
					ss.state = s;
				}
			} else {
				if (score <= ss.score) {
					ss.score = score;
					ss.state = s;
				}
			}
		}
		return ss;
	}

public:
	Minimax (Game<T> *game, int strength)
		: game(game), strength(strength) {}

	// interface for minimax
	T best_move (T state, bool maximize) {
		return minimax(state, 0, maximize).state;
	}
};