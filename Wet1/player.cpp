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

int Player::getCompletedChallenges() {
	return this->completedChallenges;
}

void Player::completeChallenge() {
	completedChallenges++;
}

void Player::setClan(Clan* clan) {
	this->clan = clan;
}

Clan* Player::getClan() {
	return this->clan;
}
