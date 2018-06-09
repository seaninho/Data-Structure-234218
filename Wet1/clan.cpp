#include "clan.hpp"

int Clan::getClanID() {
	return clanID;
}

void Clan::addPlayerToClan(Player* player) {
	Pair* key = new Pair(player->getPlayerID(), player->getNumOfCoins());
	playerTree->insertKey(key, player);
	int num_of_challenges = player->getCompletedChallenges();
	int playerID = player->getPlayerID();
	if(numOfPlayers == 0) {
		bestPlayer = *player;
	} else if (num_of_challenges > bestPlayer.getCompletedChallenges()
			|| (num_of_challenges == bestPlayer.getCompletedChallenges()
					&& playerID < bestPlayer.getPlayerID())) {
		bestPlayer = *player;
	}
	numOfPlayers++;
}

void Clan::removeStudentFromClan(Player player) {
	Pair key = Pair(player.getPlayerID(), player.getNumOfCoins());
	playerTree->removeKey(key, false);
//	if (bestPlayer.getPlayerID() == player.getPlayerID())	{
//		if (playerTree->root != NULL)	{
//			bestPlayer = *playerTree->findMaxKey()->data;
//		} else	{
//			bestPlayer = Player();
//		}
//	}
	numOfPlayers--;
}

int Clan::getNumOfPlayers() {
	return numOfPlayers;
}

void Clan::setNumOfPlayers(int num) {
	numOfPlayers = num;
}

Player Clan::getBestPlayer() {
	if (numOfPlayers == 0) {
		bestPlayer = Player();
	}
	return bestPlayer;
}

void Clan::setBestPlayer(Player* player) {
	if (bestPlayer.getPlayerID() == -1) {
		bestPlayer = *player;
	} else if (player->getCompletedChallenges()
			> bestPlayer.getCompletedChallenges()) {
		bestPlayer = *player;
	} else if (player->getCompletedChallenges()
			== bestPlayer.getCompletedChallenges()
			&& player->getPlayerID() < bestPlayer.getPlayerID()) {
		bestPlayer = *player;
	}
}

AVLtree<Pair, Player>* Clan::getClanTree() {
	return playerTree;
}

void Clan::clanTreeRevPrint(AVLnode<Pair, Player>** nodes) {
	int i = 0;
	playerTree->revinorderPrint(playerTree->root, nodes, &i);
}
