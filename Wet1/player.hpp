#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "pair.hpp"
#include "avltree.hpp"

#define INVALID -1
#define EMPTY 0

//class Clan;
class Player {

	int playerID;
	int num_of_coins;
	bool completedChallange;
	AVLnode<int, Clan>* clanTree;

public:

	Player(int ID, int initialCoins) : playerID(ID), num_of_coins(initialCoins), completedChallange(false), clanTree(NULL) {}

	Player() : playerID(INVALID), num_of_coins(EMPTY), completedChallange(false), clanTree(NULL) {}

	~Player() {
		clanTree = NULL;
	}

	void addCoins (int C) {
		this->num_of_coins += C;
	}

	int getPlayerID() {
		return this->playerID;
	}

	int getNumOfCoins() {
		return this->num_of_coins;
	}

	bool getCompletedChallange() {
		return completedChallange;
	}

	void setCompletedChallange() {
		completedChallange = true;
	}

	void setClan(AVLnode<int, Clan>* node) {
		clanTree = node;
	}

	AVLnode<int, Clan>* getClanTree() {
		return clanTree;
	}

};

#endif /* PLAYER_HPP_ */
