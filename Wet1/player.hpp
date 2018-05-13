#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "pair.hpp"
#include "avltree.hpp"

#define INVALID -1
#define EMPTY 0

//class Clan;
class Player {

	int playerID;
	int num_of_coins;
	bool completedChallenge;
	AVLnode<int, Clan>* clanTree;

public:
    /* Description:   Constructs the player.
     * Input:         ID - a unique integer.
     * Output:        None.
     * Return Values: Player object.
    */
	Player(int ID, int initialCoins) : playerID(ID), num_of_coins(initialCoins), completedChallenge(false), clanTree(NULL) {}

    /* Description:   Constructs the player - default constructor.
     * Input:         None.
     * Output:        None.
     * Return Values: Player object.
    */
	Player() : playerID(INVALID), num_of_coins(EMPTY), completedChallenge(false), clanTree(NULL) {}

    /* Description:   Destruction of the player.
     * Input:         None.
     * Output:        None.
     * Return Values: None.
    */
	~Player() {
		clanTree = NULL;
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

    /* Description:  Indicates whether the player has successfully completed a challenge.
    * Input:         None.
    * Output:        None.
    * Return Values: true - the completed a challenge successfully. false - otherwise.
    */
	bool getCompletedChallenge();

    /* Description:  Marks the player has completed a challenge successfully.
    * Input:         None.
    * Output:        None.
    * Return Values: None.
    */
	void setCompletedChallenge();

    /* Description:  Adds the player to a specific clan.
    * Input:         node - the clan's players tree root.
    * Output:        None.
    * Return Values: None.
    */
	void setClan(AVLnode<int, Clan>* node);

    /* Description:  Gets the player's clan tree.
    * Input:         None.
    * Output:        None.
    * Return Values: The  player's clan tree.
    */
	AVLnode<int, Clan>* getClanTree();

};

#endif /* PLAYER_HPP_ */
