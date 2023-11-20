#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2,'@');

}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x,playerPos.y,playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic 

    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w': //UP
            if(myDir != UP && myDir != DOWN)
                myDir = UP;
            break;
        case 'a': //LEFT
            if(myDir != LEFT && myDir != RIGHT)
                myDir = LEFT;
            break;
        case 's': //DOWN
            if(myDir != UP && myDir != DOWN)
                myDir = DOWN;
            break;
        case 'd': //RIGHT
            if(myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT;
            break;
    }       
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

