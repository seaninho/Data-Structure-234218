#include "player.hpp"

void Player::addCoins (int C) {
	this->num_of_coins += C;
}

int Player::getPlayerID() {
	return this->playerID;
}

int Player::getNumOfCoins() {
	return this->num_of_coins;
}

bool Player::getCompletedChallenge() {
	return completedChallenge;
}

void Player::setCompletedChallenge() {
	completedChallenge = true;
}

void Player::setClan(AVLnode<int, Clan>* node) {
	clanTree = node;
}

AVLnode<int, Clan>* Player::getClanTree() {
	return clanTree;
}
