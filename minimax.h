#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

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
		Vector of all legal moves from 'state'. In a win/lose state, 
		'legal_moves' should return an empty vector.
	*/
	virtual std::vector<T> legal_moves (T state, bool maximize) = 0;
};

template <class T>
class Minimax {
private:
	Game<T> *game;
	int strength; // Max depth of search tree
	std::default_random_engine rng; // For returning random best move when there are multiple best moves
	
	// Actual minimax. Returns the score of a state
	int minimax (T state, bool maximize, int depth) {
		std::vector<T> moves = game->legal_moves(state, maximize);
		if (depth == strength || moves.empty()) {
			return game->evaluate(state);
		}
		int score = maximize ? INT_MIN : INT_MAX;
		for (T move : moves) {
			int minimax_score = minimax(move, !maximize, depth + 1);
			if ((maximize && minimax_score > score) ||
				(!maximize && minimax_score < score)) {
				score = minimax_score;
			}
		}
		return score;
	}

public:
	// Time based seed
	Minimax (Game<T> *game, int strength) : game(game), strength(strength) {
		int seed = std::chrono::system_clock::now().time_since_epoch().count();
		rng = std::default_random_engine(seed);
	}

	// Minimax interface
	T best_move (T state, bool maximize) {
		std::vector<T> moves = game->legal_moves(state, maximize);
		std::shuffle(moves.begin(), moves.end(), rng);
		int score = maximize ? INT_MIN : INT_MAX;
		T candidate;
		for (T move : moves) {
			int minimax_score = minimax(move, !maximize, 0);
			if ((maximize && minimax_score > score) ||
				(!maximize && minimax_score < score)) {
				score = minimax_score;
				candidate = move;
			}
		}
		return candidate;
	}
};

