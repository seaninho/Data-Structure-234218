#ifndef CLAN_HPP_
#define CLAN_HPP_

#include "avltree.hpp"
#include "pair.hpp"
#include "player.hpp"

class Clan{

	int clanID;
	Player bestPlayer;
	int numOfPlayers;
	AVLtree<Pair,Player>* clanTree;

public:

	Clan(int ID) : clanID(ID), bestPlayer(Player()), numOfPlayers(EMPTY) {
		clanTree = new AVLtree<Pair,Player>();
	}

//	Clan() : clanID(-1), bestPlayer(Player()), numOfPlayers(-1) {
//		clanTree = NULL;
//	}

	~Clan()	{
		clanTree->cleanTreeData(clanTree->root);
		delete clanTree;
	}

	int getClanID() {
		return clanID;
	}

	void addPlayerToClan(Player* player) {
		Pair* key = new Pair(player->getPlayerID(), player->getNumOfCoins());
		clanTree->insertKey(key, player);
		int num_of_coins = player->getNumOfCoins();
		int playerID = player->getPlayerID();
		if (num_of_coins > bestPlayer.getNumOfCoins() ||
				(num_of_coins == bestPlayer.getNumOfCoins() && playerID < bestPlayer.getPlayerID())) {
			bestPlayer = *player;
		}
		numOfPlayers++;
	}

	void removeStudentFromClan(Player player) {
		Pair key = Pair(player.getPlayerID(), player.getNumOfCoins());
		clanTree->removeKey(key,false);
		if (bestPlayer.getPlayerID() == player.getPlayerID())	{
			if (clanTree->root != NULL)	{
				bestPlayer = *clanTree->findMaxKey()->data;
			} else	{
				bestPlayer = Player();
			}
		}
		numOfPlayers--;
	}


	int getNumOfPlayers()	{
		return numOfPlayers;
	}

	Player getBestPlayer ()	{
		if (numOfPlayers == 0) {
			bestPlayer = Player();
		}
		return bestPlayer;
	}

	void setBestPlayer ()	{
		bestPlayer = *clanTree->findMaxKey()->data;
	}

	AVLnode<Pair,Player>* getClanTreeRoot ()	{
		return clanTree->root;
	}

	AVLtree<Pair,Player>* getClanTree()	{
		return clanTree;
	}


	void clanTreeRevPrint(AVLnode<Pair,Player>** nodes)	{
		int i = 0;
		clanTree->revinorderPrint(clanTree->root, nodes, &i);
	}


};


#endif /* CLAN_HPP_ */
