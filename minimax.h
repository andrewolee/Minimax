#include <stdio.h>
#include <vector>

template <class T>
class Game {
protected:
	T state;
	bool player_turn;

public:
	Game (T state) {
		this->state = state;
		this->player_turn = true;
	}

	Game (T state, bool player_turn) {
		this->state = state;
		this->player_turn = player_turn;
	}

	T current_state () {
		return state;
	}

	// restore to starting position
	virtual void initial () = 0;
	
	// 1 on success, -1 on failure
	virtual int try_move (T state) = 0;

	// static score of the current position
	virtual int evaluate (T state) = 0;

	// vector of all legal moves from the current position
	virtual std::vector<T> legal_moves (T state) = 0;
};

template <class T>
class Minimax {
private:
	Game<T> game;
	int strength; // max depth of search tree

public:
	Minimax (Game<T> &game, int strength) {
		this->game = game;
		this->strength = strength;
	}

	T best_move (T state) {
		for (T p : game.legal_moves(state)) {
			game.evaluate(p);
		}
	}
};