
#ifndef OASIS_HPP_
#define OASIS_HPP_

#include "avltree.hpp"
#include "player.hpp"
#include "clan.hpp"
#include "pair.hpp"
#include "library1.h"

class Oasis {
	int numOfPlayers;
	Player bestPlayer;
	AVLtree<int, Player>* playerTree;
	AVLtree<Pair, Player>* playerCoinTree;
	AVLtree<int, Clan>* clanTree;

public:
	Oasis(){
		numOfPlayers = 0;
		playerTree = new AVLtree<int, Player>;
		playerCoinTree = new AVLtree<Pair, Player>;
		clanTree = new AVLtree<int, Clan>;
	};

	StatusType addPlayer(int playerID, int initialCoins);
	StatusType addClan(int clanID);
	StatusType joinClan(int playerID, int clanID);
	StatusType completeChallenge(int playerID, int coins);
	StatusType getBestPlayer(int clanID, int *playerID);
	StatusType getScoreboard(int clanID, int **players, int *numOfPlayers);
	StatusType uniteClans(int clanID1, int clanID2);

	~Oasis(){
		delete clanTree;
		playerCoinTree->cleanTreeData(playerCoinTree->root);
		delete playerCoinTree;
		delete playerTree;
	};
};



#endif
