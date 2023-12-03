#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    // Construct the remaining declaration from the project manual.
    // Only some sample members are included here
    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef, Food *foodRef);
        ~Player();
                // UPGRADED it
        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();

        char checkFoodConsumption();
        void increasePlayerLength();
        bool checkSelfCollision();
        // Need more actions in here:
        // after inserting the head but before removing the tail
        // - check if new head position collides with food
        // - if yes, increment the score in GM, generate new food, and
        // do not remove tail

        // otherwise, remove tail and move on.


        // Lastly, add self collision check.
        // - if self-collided
        // set loseFlag and exitFlag both to true (through GM)
        // this will break the program loop and end the game
        //
        // - if ending, you need to differentiate the end game state
        // LOST - display LOST message
        // otherwise, display ENDGAME message only.

    private:                // UPGRADED it
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;
        objPos playerPos;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food *myFood;
};

#endif