#include "Player.h"
#include <iostream>


Player::Player(GameMechs* thisGMRef, Food *foodRef) : mainGameMechsRef(thisGMRef), myFood(foodRef)
{
    
    myDir = STOP;

    // more actions to be included

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                      mainGameMechsRef->getBoardSizeY()/2,
                      '*');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    

    // Initialize playerPos with the new head position
    playerPos = tempPos;
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
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY() -1) // Wraparound from bottom to top
                currentHead.y = 1;
            break;
        case LEFT:
            currentHead.x--;  
            if(currentHead.x <= 0) // Wraparound from left to right
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            break;
        case RIGHT:
            currentHead.x++;
            if (currentHead.x >= mainGameMechsRef->getBoardSizeX() -1) // Wraparound from right to left
                currentHead.x = 1;
            
            break;

        case STOP:
        default:
            break;
    }
    // Update playerPos to reflect the new head position
    playerPos = currentHead;

    // Insert the new head position to the playerPosList
    // playerPosList->insertHead(playerPos);

    // playerPosList->removeTail();
    

    if(!checkFoodConsumption()) 
    {
        // Normal movement when there's no food consumption
        playerPosList->insertHead(currentHead);
        playerPosList->removeTail();
    }
}

bool Player::checkFoodConsumption()
{

    // Check if the head overlaps with the food
    objPos foodPos;
    myFood->getFoodPos(foodPos);

    if(playerPos.isPosEqual(&foodPos))
    {
        

        // Generate new food
        myFood->generateFood(playerPos, playerPosList);

        // Increase the score in GM
        mainGameMechsRef->incrementScore();
        
        increasePlayerLength();

        return true; // Food consumed successfully
    }

    
    return false; // No food consumption
}

void Player::increasePlayerLength()
{
    
    // Get the current head position
    objPos currentHead;
    playerPosList->getHeadElement(currentHead);

    // Insert the new head position to the playerPosList
    playerPosList->insertHead(currentHead);
}

bool Player::checkSelfCollision()
{
    // Check if the new head position collides with any element in the playerPosList
    objPos tempPos;

    for(int i = 1; i < playerPosList->getSize();i++)
    {
        playerPosList->getElement(tempPos,i);
        if(tempPos.isPosEqual(&playerPos))
        {
            return true; // Collision detected
        }
    }

    return false; // No collision
}