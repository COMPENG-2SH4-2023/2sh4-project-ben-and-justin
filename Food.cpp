#include "Food.h"


// Think about where to seed the RNG

Food::Food(GameMechs* thisGMRef) : mainGameMechsRef(thisGMRef)
{
    
    foodPos.setObjPos(-1,-1,'o'); // initialize foodPos outside of the game board (so to not be displayed)

}

Food::~Food()
{
    
}

void Food::generateFood(objPos blockOff, const objPosArrayList* playerBody)
{
    
    // generate random x and y coord, and make sure they are NOT boarder or blockOff pos.
    
    // check x and y against 0 and boardSizeX / Y.

    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element-by-element
    // for your convenience

    bool blocked;
    do
    {
        
        // Generated random x and y coordinates
        int randomX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 2);
        int randomY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 2);

        // Set food position
        foodPos.setObjPos(randomX, randomY, 'o');

        // Check if the generated position is blocked by the player's body
        blocked = false;
        for(int i = 0; i < playerBody->getSize();i++)
        {
            objPos tempBody;
            playerBody->getElement(tempBody, i);
            if (foodPos.isPosEqual(&tempBody))
            {
                blocked = true;
                break;
            }
        }


    } while (blocked || foodPos.isPosEqual(&blockOff));

}



void Food::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}