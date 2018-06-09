#include "oasis.hpp"

StatusType Oasis::addPlayer(int playerID, int initialCoins) {
	if (playerTree->findKey(playerID)) {
		return FAILURE;
	}
	Player* new_player;
	try {
		new_player = new Player(playerID, initialCoins);
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
	Pair* new_pair;
	try {
		new_pair = new Pair(playerID, initialCoins);
	} catch (std::bad_alloc&) {
		delete new_player;
		return ALLOCATION_ERROR;
	}

	int* new_id = new int(playerID);

	playerTree->insertKey(new_id, new_player);

	playerCoinTree->insertKey(new_pair, new_player);

	numOfPlayers++;

	if (numOfPlayers == 1
			|| (bestPlayer.getCompletedChallenges() == 0
					&& new_player->getPlayerID() < bestPlayer.getPlayerID())) {
		bestPlayer = *new_player;
	}

	return SUCCESS;
}

StatusType Oasis::addClan(int clanID) {
	if (clanTree->findKey(clanID)) {
		return FAILURE;
	}
	Clan* new_clan;
	try {
		new_clan = new Clan(clanID);
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
	int* new_id = new int(clanID);
	clanTree->insertKey(new_id, new_clan);
	return SUCCESS;
}

StatusType Oasis::joinClan(int playerID, int clanID) {
	if (!playerTree->findKey(playerID) || !clanTree->findKey(clanID)) {
		return FAILURE;
	}
	Player* player = playerTree->getData(playerID);
	Clan* clan = clanTree->getData(clanID);
	if (player->getClan()) {
		return FAILURE;
	}
	try {
		clan->addPlayerToClan(player);
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
	player->setClan(clan);

	return SUCCESS;
}

StatusType Oasis::completeChallenge(int playerID, int coins) {
	if (!playerTree->findKey(playerID)) {
		return FAILURE;
	}

	Player* player = playerTree->getData(playerID);

	Pair* pair = new Pair(player->getPlayerID(), player->getNumOfCoins());

	Clan* clan = NULL;

	if (player->getClan()) {
		clan = player->getClan();
	}

	playerCoinTree->removeKey(*pair, false);

	if (clan) {
		clan->removeStudentFromClan(*player);
	}

	player->completeChallenge();

	player->addCoins(coins);

	if (player->getCompletedChallenges() > bestPlayer.getCompletedChallenges()
			|| (player->getCompletedChallenges()
					== bestPlayer.getCompletedChallenges()
					&& player->getPlayerID() < bestPlayer.getPlayerID())) {
		bestPlayer = *player;
	}

	if (clan) {
		clan->addPlayerToClan(player);
	}
	pair->setNumOfCoins(player->getNumOfCoins());

	playerCoinTree->insertKey(pair, player);

	return SUCCESS;
}

StatusType Oasis::getBestPlayer(int clanID, int *playerID) {
	if (clanID < 0) {
		if (numOfPlayers == 0) {
			*playerID = -1;
			return SUCCESS;
		}
		*playerID = bestPlayer.getPlayerID();
		return SUCCESS;
	}
	if (!clanTree->findKey(clanID)) {
		return FAILURE;
	}
	*playerID = clanTree->getData(clanID)->getBestPlayer().getPlayerID();
	return SUCCESS;
}

StatusType Oasis::getScoreboard(int clanID, int **players, int *numOfPlayers) {
	if (clanID < 0) {
		if (this->numOfPlayers == 0) {
			*numOfPlayers = 0;
			*players = NULL;
			return SUCCESS;
		}
		int index = 0;
		AVLnode<Pair, Player>* root = playerCoinTree->root;
		AVLnode<Pair, Player>** nodes;
		try {
			nodes = new AVLnode<Pair, Player>*[this->numOfPlayers];
		} catch (std::bad_alloc&) {
			return ALLOCATION_ERROR;
		}

		playerCoinTree->revinorderPrint(root, nodes, &index);
		*players = (int*) malloc(this->numOfPlayers * sizeof(int));
		if (*players == NULL) {
			delete[] nodes;
			return ALLOCATION_ERROR;
		}
		for (int i = 0; i < this->numOfPlayers; i++) {
			(*players)[i] = nodes[i]->data->getPlayerID();
		}
		*numOfPlayers = this->numOfPlayers;
		delete[] nodes;
		return SUCCESS;
	}
	if (!clanTree->findKey(clanID)) {
		return FAILURE;
	}
	Clan* clan = clanTree->getData(clanID);
	if (clan->getNumOfPlayers() == 0) {
		*players = NULL;
		*numOfPlayers = 0;
		return SUCCESS;
	}
	AVLnode<Pair, Player>** nodes;
	int clanNumOfPlayers = clan->getNumOfPlayers();
	try {
		nodes = new AVLnode<Pair, Player>*[clanNumOfPlayers];
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
	clan->clanTreeRevPrint(nodes);
	*players = (int*) malloc(sizeof(int) * clanNumOfPlayers);
	if (*players == NULL) {
		delete[] nodes;
		return ALLOCATION_ERROR;
	}
	for (int i = 0; i < clanNumOfPlayers; i++) {
		(*players)[i] = nodes[i]->data->getPlayerID();
	}
	*numOfPlayers = clanNumOfPlayers;

	delete[] nodes;
	return SUCCESS;
}

StatusType Oasis::uniteClans(int clanID1, int clanID2) {
	if (!clanTree->findKey(clanID1) || !clanTree->findKey(clanID2)) {
		return FAILURE;
	}
	Clan* clan1 = clanTree->getData(clanID1);
	Clan* clan2 = clanTree->getData(clanID2);

	if (clan1->getNumOfPlayers() == 0 && clan2->getNumOfPlayers() == 0) {
		if (clan1->getClanID() < clan2->getClanID()) {
			clanTree->removeKey(clan2->getClanID(), true);

			return SUCCESS;
		} else {
			clanTree->removeKey(clan1->getClanID(), true);

			return SUCCESS;
		}
	}

	if (clan1->getNumOfPlayers() < clan2->getNumOfPlayers()
			|| (clan1->getNumOfPlayers() == clan2->getNumOfPlayers()
					&& clan2->getClanID() < clan1->getClanID())) {
		Clan* temp = clan1;
		clan1 = clan2;
		clan2 = temp;
	}

	if (clan2->getNumOfPlayers() == 0) {
		AVLnode<Pair, Player>** nodes1;
		try {
			nodes1 = new AVLnode<Pair, Player>*[clan1->getNumOfPlayers()];
		} catch (std::bad_alloc&) {
			return ALLOCATION_ERROR;
		}
		int counter = 0, index = 0;
		clan1->getClanTree()->inorderPrint(clan1->getClanTree()->root, nodes1,
				&index);

		for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
			if (nodes1[i]->data->getCompletedChallenges() != 0) {
				counter++;
			}
		}

		AVLnode<Pair, Player>** array;
		if (counter == 0) {
			for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
				nodes1[i]->data->setClan(NULL);
				delete nodes1[i]->key;
				delete nodes1[i];
			}

			delete[] nodes1;

			clan1->getClanTree()->root = NULL;

			clanTree->removeKey(clan2->getClanID(), true);

			clan1->setNumOfPlayers(0);

			Player player = Player();

			clan1->setBestPlayer(&player);

			return SUCCESS;
		}

		try {
			array = new AVLnode<Pair, Player>*[counter];
		} catch (std::bad_alloc&) {
			delete[] nodes1;
			return ALLOCATION_ERROR;
		}
		index = 0;

		for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
			if (nodes1[i]->data->getCompletedChallenges() == 0) {
				nodes1[i]->data->setClan(NULL);
				delete nodes1[i]->key;
			} else {
				array[index++] = nodes1[i];
			}
		}

		clan1->getClanTree()->createAvlFromArray(counter, array);

		for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
			delete nodes1[i];
		}

		delete[] nodes1;

		clanTree->removeKey(clan2->getClanID(), true);

		clan1->setNumOfPlayers(counter);

		delete[] array;

		return SUCCESS;
	}

	AVLnode<Pair, Player>** nodes1;
	AVLnode<Pair, Player>** nodes2;
	try {
		nodes1 = new AVLnode<Pair, Player>*[clan1->getNumOfPlayers()];
	} catch (std::bad_alloc&) {
		return ALLOCATION_ERROR;
	}
	try {
		nodes2 = new AVLnode<Pair, Player>*[clan2->getNumOfPlayers()];
	} catch (std::bad_alloc&) {
		delete[] nodes1;
		return ALLOCATION_ERROR;
	}
	int counter = 0, index1 = 0, index2 = 0;
	clan1->getClanTree()->inorderPrint(clan1->getClanTree()->root, nodes1,
			&index1);
	clan2->getClanTree()->inorderPrint(clan2->getClanTree()->root, nodes2,
			&index2);

	for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
		if (nodes1[i]->data->getCompletedChallenges() != 0) {
			counter++;
		}
	}
	for (int i = 0; i < clan2->getNumOfPlayers(); i++) {
		if (nodes2[i]->data->getCompletedChallenges() != 0) {
			counter++;
		}
	}
	if (counter == 0) {
		for (int i = 0; i < clan1->getNumOfPlayers(); i++) {
			nodes1[i]->data->setClan(NULL);
			delete nodes1[i]->key;
			delete nodes1[i];
		}
		for (int i = 0; i < clan2->getNumOfPlayers(); i++) {
			nodes2[i]->data->setClan(NULL);
			nodes2[i]->data = NULL;
			delete nodes2[i]->key;
			nodes2[i]->key = NULL;
		}
		delete[] nodes1;
		delete[] nodes2;
		Player player = Player();
		clan1->setBestPlayer(&player);
		clan1->setNumOfPlayers(0);
		clan1->getClanTree()->root = NULL;

		clanTree->removeKey(clan2->getClanID(), true);

		return SUCCESS;
	}
	AVLnode<Pair, Player>** mergedArray;
	try {
		mergedArray = new AVLnode<Pair, Player>*[counter];
	} catch (std::bad_alloc&) {
		delete[] nodes1;
		delete[] nodes2;
		return ALLOCATION_ERROR;
	}
	index1 = 0;
	index2 = 0;
	for (int i = 0; i < counter; i++) {

		while (index1 < clan1->getNumOfPlayers()
				&& nodes1[index1]->data->getCompletedChallenges() == 0) {
			nodes1[index1]->data->setClan(NULL);
			delete nodes1[index1]->key;
			nodes1[index1]->key = NULL;
			nodes1[index1]->data = NULL;
			index1++;
		}
		while (index2 < clan2->getNumOfPlayers()
				&& nodes2[index2]->data->getCompletedChallenges() == 0) {
			nodes2[index2]->data->setClan(NULL);
			delete nodes2[index2]->key;
			nodes2[index2]->key = NULL;
			nodes2[index2]->data = NULL;
			index2++;
		}
		if (index1 < clan1->getNumOfPlayers()
				&& index2 < clan2->getNumOfPlayers()) {
			if (nodes1[index1] < nodes2[index2]) {
				mergedArray[i] = nodes1[index1++];
			} else {
				mergedArray[i] = nodes2[index2++];
				mergedArray[i]->data->setClan(clan1);
			}
		} else if (index1 < clan1->getNumOfPlayers()) {
			mergedArray[i] = nodes1[index1++];
		} else if (index2 < clan2->getNumOfPlayers()) {
			mergedArray[i] = nodes2[index2++];
			mergedArray[i]->data->setClan(clan1);
		}
	}

	while(index1 < clan1->getNumOfPlayers()
				&& nodes1[index1]->data->getCompletedChallenges() == 0) {
		nodes1[index1]->data->setClan(NULL);
		delete nodes1[index1]->key;
		nodes1[index1]->key = NULL;
		nodes1[index1]->data = NULL;
		index1++;
	}
	while (index2 < clan2->getNumOfPlayers()
			&& nodes2[index2]->data->getCompletedChallenges() == 0) {
		nodes2[index2]->data->setClan(NULL);
		delete nodes2[index2]->key;
		nodes2[index2]->key = NULL;
		nodes2[index2]->data = NULL;
		index2++;
	}

	clan1->getClanTree()->createAvlFromArray(counter, mergedArray);
	clan2->getClanTree()->root = NULL;

	for(int i = 0; i < clan1->getNumOfPlayers(); i++) {
		delete nodes1[i];
	}
	for(int i = 0; i < clan2->getNumOfPlayers(); i++) {
		delete nodes2[i];
	}
	delete[] nodes1;
	delete[] nodes2;

	Player temp_player = clan2->getBestPlayer();

	clan1->setBestPlayer(&temp_player);
	clan1->setNumOfPlayers(counter);

	clanTree->removeKey(clan2->getClanID(), true);

	delete[] mergedArray;

	return SUCCESS;
}
