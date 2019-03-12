#include <vector>

template <class T>
class Game {
public:
	/*
		The score for 'state'. Should return a positive integer
		for an advantage to the maximizer and a negative integer for an 
		advantage to the minimizer
	*/
	virtual int evaluate (T state) = 0;

	/*
		Vector of all legal moves from 'state'.
	*/
	virtual std::vector<T> legal_moves (T state, bool maximize) = 0;
};

template <class T>
class Minimax {
private:
	struct StateScore {
		T state;
		int score;
	};

	Game<T> *game;
	int strength; // Max depth of search tree
	
	// Actual minimax
	StateScore minimax (T state, bool maximize, int depth) {
		StateScore node;
		std::vector<T> children = game->legal_moves(state, maximize);
		if (depth == strength || children.empty()) {
			node.state = state;
			node.score = game->evaluate(state);
			return node;
		}
		// Default to a random node if no best move is found
		if (maximize) {
			node.score = INT_MIN;
		} else {
			node.score = INT_MAX;
		}
		for (T child : children) {
			int score = minimax(child, !maximize, depth + 1).score;
			if ((maximize && score > node.score) ||
				(!maximize && score < node.score)) {
				node.score = score;
				node.state = child;
			}
		}
		return node;
	}

public:
	Minimax (Game<T> *game, int strength)
		: game(game), strength(strength) {}

	// Minimax interface
	T best_move (T state, bool maximize) {
		return minimax(state, maximize, 0).state;
	}
};

