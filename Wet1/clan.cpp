#include "clan.hpp"

int Clan::getClanID() {
	return clanID;
}

void Clan::addPlayerToClan(Player* player) {
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

void Clan::removeStudentFromClan(Player player) {
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


int Clan::getNumOfPlayers()	{
	return numOfPlayers;
}

Player Clan::getBestPlayer ()	{
	if (numOfPlayers == 0) {
		bestPlayer = Player();
	}
	return bestPlayer;
}

void Clan::setBestPlayer ()	{
	bestPlayer = *clanTree->findMaxKey()->data;
}

AVLtree<Pair,Player>* Clan::getClanTree()	{
	return clanTree;
}


void Clan::clanTreeRevPrint(AVLnode<Pair,Player>** nodes)	{
	int i = 0;
	clanTree->revinorderPrint(clanTree->root, nodes, &i);
}
