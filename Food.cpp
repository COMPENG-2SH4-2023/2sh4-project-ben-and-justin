#include "Food.h"


// Think about where to seed the RNG

Food::Food(GameMechs* thisGMRef) : mainGameMechsRef(thisGMRef)
{
    foodPos.setObjPos(-1,-1,'o'); // initialize foodPos outside of the game board (so to not be displayed)

    // FoodBucket initialization with invalid objects
    foodBucket = new objPosArrayList();
    for(int i=0 ; i<5 ; i++) {
        foodBucket->insertHead(foodPos);
    }
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPos blockOff, const objPosArrayList* playerBody)
{
    
    // generate random x and y coord, and make sure they are NOT boarder or blockOff pos.
    
    // check x and y against 0 and boardSizeX / Y.

    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element-by-element
    // for your convenience

    // Bonus Rambling
    // Generate 5 food, with 1 or 2 specials
        // Score 10 w length += 0
        // Score 5 w length += 10
    // Solution
        // Initialize foodBucket in constructor, add deconstructor for memory leaks - Done
        // Repeat coordinate generation for 5 objects here (PPA3 GenerateFood) - Done
        // RNG after valid coordinates to assign specials, only two specials assigned - Done
    
        // In Player>movePlayer>checkConsumption, check foodBucket->getElement->getSymbol, act accordingly - Done
        // Update DrawScreen to accomodate foodBucket - Done

    // Generate 5 food objects
    int i,j,k;
    for(i=0 ; i<5 ; i++) {
        bool blocked;
        int randomX, randomY;
        objPos tempFoodPos;
        foodBucket->getElement(tempFoodPos, i);

        // Loop for validity
        do {
            // Assign random coordinates
            randomX = 1 + rand() % (mainGameMechsRef->getBoardSizeX() - 2);
            randomY = 1 + rand() % (mainGameMechsRef->getBoardSizeY() - 2);
            tempFoodPos.setObjPos(randomX, randomY, 'X');

            blocked = false;
            // Check against existing food objects
            for(j=0 ; j<i ; j++) {
                objPos existingFoodPos;
                foodBucket->getElement(existingFoodPos, j);
                if(tempFoodPos.isPosEqual(&existingFoodPos)) {
                    blocked = true;
                    break;
                }
            }

            // Check against Player
            for(j=0 ; j<playerBody->getSize() ; j++) {
                objPos tempBody;
                playerBody->getElement(tempBody, j);
                if (foodPos.isPosEqual(&tempBody)) {
                    blocked = true;
                    break;
                }
            }

        } while(blocked || tempFoodPos.isPosEqual(&blockOff));

        // Clear bad data placeholders
        foodBucket->removeTail();
        // Insert valid food into foodBucket
        if(i < 3) {
            // Insert regular foods for first three entries
            tempFoodPos.setObjPos(randomX, randomY, 'o');
            foodBucket->insertHead(tempFoodPos);
        }
        else {
            // Insert special foods for rest (50/50 chance of @ or +)
            int rng = rand() % 2;
            if(rng) {
                // Length Food
                tempFoodPos.setObjPos(randomX, randomY, '@');
            }
            else {
                // Score Food
                tempFoodPos.setObjPos(randomX, randomY, '+');
            }
            foodBucket->insertHead(tempFoodPos);
        }
    }
}

void Food::getFoodPos(objPos &returnPos) {
    returnPos = foodPos;
}

objPosArrayList* Food::getFoodBucket() {
    return foodBucket;
}