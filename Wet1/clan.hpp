#ifndef CLAN_HPP_
#define CLAN_HPP_

#include "avltree.hpp"
#include "pair.hpp"
#include "player.hpp"

class Clan{

	int clanID;
	Player bestPlayer;
	int numOfPlayers;
	AVLtree<Pair,Player>* clanTree;

public:
    /* Description:   Constructs the clan.
     * Input:         ID - a unique integer.
     * Output:        None.
     * Return Values: Clan object.
    */
	Clan(int ID) : clanID(ID), bestPlayer(Player()), numOfPlayers(EMPTY) {
		clanTree = new AVLtree<Pair,Player>();
	}

//	Clan() : clanID(-1), bestPlayer(Player()), numOfPlayers(-1) {
//		clanTree = NULL;
//	}

    /* Description:   Destructs the clan.
     * Input:         None.
     * Output:        None.
     * Return Values: None.
    */
	~Clan()	{
		clanTree->cleanTreeData(clanTree->root);
		delete clanTree;
	}
    /* Description:  Gets the clan's ID.
    * Input:         None.
    * Output:        None.
    * Return Values: The clan's ID.
    */
	int getClanID();

	/* Description:  Adds a player to the clan.
    * Input:         player - the player's data.
    * Output:        None.
    * Return Values: None.
    */
	void addPlayerToClan(Player* player);

    /* Description:  Removes a player from the clan.
    * Input:         player - the player's data.
    * Output:        None.
    * Return Values: None.
    */
	void removeStudentFromClan(Player player);

    /* Description:  Gets the number of players in the clan.
    * Input:         None.
    * Output:        None.
    * Return Values: The number of players in the clan.
    */
	int getNumOfPlayers();

    /* Description:  Gets the best player in the clan, the player who has the most coins.
    * Input:         None.
    * Output:        None.
    * Return Values: The player's data.
    */
	Player getBestPlayer ();

    /* Description:  Sets the best player in the clan, the player who has the most coins.
    * Input:         None.
    * Output:        None.
    * Return Values: None.
    */
	void setBestPlayer ();

    /* Description:  Gets the clan's players tree.
    * Input:         None.
    * Output:        None.
    * Return Values: The clan's players tree root node.
    */
	AVLtree<Pair,Player>* getClanTree();

    /* Description:  Prints the clan's players tree.
    * Input:         None.
    * Output:        None.
    * Return Values: None.
    */
	void clanTreeRevPrint(AVLnode<Pair,Player>** nodes);

};


#endif /* CLAN_HPP_ */
