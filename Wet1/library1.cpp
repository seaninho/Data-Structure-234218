
#include "library1.h"
#include "oasis.hpp"

void* Init() {
	Oasis* DS = new Oasis();
	return (void*)DS;
}

StatusType addPlayer(void *DS, int PlayerID, int initialCoins){
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->addPlayer(PlayerID, initialCoins);
}

StatusType addClan(void *DS, int clanID){
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->addClan(clanID);

}

StatusType joinClan(void *DS, int playerID, int clanID)	{
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->joinClan(playerID, clanID);
}

StatusType completeChallange(void *DS, int playerID, int coins)	{
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->completeChallange(playerID, coins);
}

StatusType getBestPlayer(void *DS, int clanID, int *playerID) {
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->getBestPlayer(clanID, playerID);
}

StatusType getScoreboard(void *DS, int clanID, int **players, int *numOfPlayers) {
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->getScoreboard(clanID, players, numOfPlayers);
}

StatusType uniteClans(void *DS, int clanID1, int clanID2) {
	if (DS == NULL) return INVALID_INPUT;
	return ((Oasis*)DS)->uniteClans(clanID1, clanID2);
}
void Quit(void** DS)	{
	if (DS == NULL) return;
	delete ((Oasis*)*DS);
	*DS=NULL;
}

