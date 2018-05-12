#include "pair.hpp"

int Pair::getID() const {
	return playerID;
}

int Pair::getNumOfCoins() const {
	return coins;
}

void Pair::setNumOfCoins(int C) {
	coins = C;
}

bool  Pair::operator> (const Pair& p) const	{
	if (this->coins > p.getNumOfCoins() ||
		(this->coins == p.getNumOfCoins() && this->playerID < p.getID()) ) {
		return true;
	}
	return false;
}

bool Pair::operator== (const Pair& p) const	{
	if(this->playerID == p.getID() && this->coins == p.getNumOfCoins())
		return true;
	else
		return false;
}

bool  Pair::operator< (const Pair& p) const	{
	return !(*this >= p);
}

bool Pair::operator>= (const Pair& p) const	{
	if(*this > p || *this == p)
		return true;
	else
		return false;
}
bool Pair::operator<= (const Pair& p) const	{
	return !(*this > p);
}

std::ostream& operator<<(std::ostream& output, const Pair& pair)	{
	output << pair.coins << "," << pair.playerID << std::endl;
	return output;
}
