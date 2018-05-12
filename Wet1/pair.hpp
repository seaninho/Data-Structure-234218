#ifndef PAIR_HPP_
#define PAIR_HPP_

#include <iostream>

class Pair {

	int playerID, coins;

public:

	Pair(int x, int y) : playerID(x), coins(y) {}
	~Pair() {}

	int getID() const;
	int getNumOfCoins() const;
	void setNumOfCoins(int C);

	bool operator> (const Pair& p) const;
	bool operator< (const Pair& p) const;
	bool operator== (const Pair& p) const;
	bool operator>= (const Pair& p) const;
	bool operator<= (const Pair& p) const;

	friend std::ostream& operator<<(std::ostream& output, const Pair& pair);
};

#endif /* PAIR_HPP_ */
