#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "pair.hpp"
#include "avltree.hpp"

#define INVALID -1
#define EMPTY 0

class Clan;
class Player {

	int playerID;
	int num_of_coins;
	int completedChallenges;
	Clan* clan;

public:
    /* Description:   Constructs the player.
     * Input:         ID - a unique integer.
     * Output:        None.
     * Return Values: Player object.
    */
	Player(int ID, int initialCoins) : playerID(ID), num_of_coins(initialCoins), completedChallenges(0), clan(NULL) {}

    /* Description:   Constructs the player - default constructor.
     * Input:         None.
     * Output:        None.
     * Return Values: Player object.
    */
	Player() : playerID(INVALID), num_of_coins(EMPTY), completedChallenges(0), clan(NULL) {}

    /* Description:   Destruction of the player.
     * Input:         None.
     * Output:        None.
     * Return Values: None.
    */
	~Player() {
		clan = NULL;
	}

    /* Description:   Adds coins to the player's tally.
     * Input:         C - the number of coins the player has earned.
     * Output:        None.
     * Return Values: None.
    */
	void addCoins (int C);

    /* Description:  Gets the player's ID.
    * Input:         None.
    * Output:        None.
    * Return Values: The player's ID.
    */
	int getPlayerID();

    /* Description:  Gets the number of coins the player has.
    * Input:         None.
    * Output:        None.
    * Return Values: The number coins.
    */
	int getNumOfCoins();

    /* Description:  Gets the number of challenges the player has.
    * Input:         None.
    * Output:        None.
    * Return Values: The number of challenges.
    */
	int getCompletedChallenges();

    /* Description:  Increases the number of completed challenges by 1.
    * Input:         None.
    * Output:        None.
    * Return Values: None.
    */
	void completeChallenge();

    /* Description:  Adds the player to a specific clan.
    * Input:         clan - the clan itself.
    * Output:        None.
    * Return Values: None.
    */
	void setClan(Clan* clan);

    /* Description:  Gets the player's clan.
    * Input:         None.
    * Output:        None.
    * Return Values: A pointer to the player's clan tree.
    */
	Clan* getClan();

};

#endif /* PLAYER_HPP_ */
