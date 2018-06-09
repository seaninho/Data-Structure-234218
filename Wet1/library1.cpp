#include "library1.h"

#include "oasis.hpp"

void* init() {
	Oasis* DS = new Oasis();
	return (void*)DS;
}

StatusType addPlayer(void *DS, int PlayerID, int initialCoins){
	if (DS == NULL || PlayerID <= 0 || initialCoins < 0) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->addPlayer(PlayerID, initialCoins);
}

StatusType addClan(void *DS, int clanID){
	if (DS == NULL || clanID <= 0) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->addClan(clanID);

}

StatusType joinClan(void *DS, int playerID, int clanID)	{
	if (DS == NULL || playerID <= 0 || clanID <= 0) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->joinClan(playerID, clanID);
}

StatusType completeChallange(void *DS, int playerID, int coins)	{
	if (DS == NULL || playerID <= 0 || coins <= 0) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->completeChallenge(playerID, coins);
}

StatusType getBestPlayer(void *DS, int clanID, int *playerID) {
	if (DS == NULL || playerID == NULL || clanID == 0) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->getBestPlayer(clanID, playerID);
}

StatusType getScoreboard(void *DS, int clanID, int **players, int *numOfPlayers) {
	if (DS == NULL || clanID == 0 || players == NULL || numOfPlayers == NULL) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->getScoreboard(clanID, players, numOfPlayers);
}

StatusType uniteClans(void *DS, int clanID1, int clanID2) {
	if (DS == NULL || clanID1 <= 0 || clanID2 <= 0 || clanID1 == clanID2) {
		return INVALID_INPUT;
	}
	return ((Oasis*)DS)->uniteClans(clanID1, clanID2);
}
void quit(void** DS)	{
	if (DS == NULL) return;
	delete ((Oasis*)*DS);
	*DS = NULL;
	return;
}

