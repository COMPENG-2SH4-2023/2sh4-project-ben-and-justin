#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                      mainGameMechsRef->getBoardSizeY()/2,
                      '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    // for debugging purpose - insert another 4 segments
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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
    

    objPos currentHead; // holding the pos information of the current head
    playerPosList->getHeadElement(currentHead);

    switch(myDir)
    {
        case UP:
            currentHead.y--;
            if(currentHead.y <= 0) // Wraparound from top to bottom
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            break;
        case DOWN:
            currentHead.y++;
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY()) // Wraparound from bottom to top
                currentHead.y = 1;
            break;
        case LEFT:
            currentHead.x--;  
            if(currentHead.x <= 0) // Wraparound from left to right
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case RIGHT:
            currentHead.x++;
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX()) // Wraparound from right to left
                currentHead.x = 1;
            break;

        case STOP:
        default:
            break;
    }

    // new current head should be inserted to the head of the list
    playerPosList->insertHead(currentHead);

    // then, remove tail
    playerPosList->removeTail();
}

