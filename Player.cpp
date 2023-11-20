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
    switch(myDir)
    {
        case UP:
            playerPos.y = (playerPos.y - 1 + mainGameMechsRef->getBoardSizeY()) % mainGameMechsRef->getBoardSizeY();
            if(playerPos.y == 0) // Wraparound from top to bottom
                playerPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;
        case DOWN:
            playerPos.y = (playerPos.y + 1) % mainGameMechsRef->getBoardSizeY();
            if(playerPos.y == mainGameMechsRef->getBoardSizeY() - 1) // Wraparound from bottom to top
                playerPos.y = 1;
            break;
        case LEFT:
            playerPos.x = (playerPos.x - 1 + mainGameMechsRef->getBoardSizeX()) % mainGameMechsRef->getBoardSizeX();  
            if(playerPos.x == 0) // Wraparound from left to right
                playerPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case RIGHT:
            playerPos.x = (playerPos.x + 1) % mainGameMechsRef->getBoardSizeX();
            if (playerPos.x == mainGameMechsRef->getBoardSizeX() - 1) // Wraparound from right to left
                playerPos.x = 1;
            break;
        default:
            break;
    }
}

