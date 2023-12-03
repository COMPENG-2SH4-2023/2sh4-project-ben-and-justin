#ifndef FOOD_H
#define FOOD_H
#include <cstdlib>
#include <time.h>
#include "GameMechs.h"

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class Food
{
    private:
        objPos foodPos;
        objPosArrayList* foodBucket;
        GameMechs* mainGameMechsRef;

    public:
        Food(GameMechs* thisGMRef);
        ~Food();
        void generateFood(objPos blockOff, const objPosArrayList* playerBody); // You need to upgrade this somehow
        // Need to accept the player body array list
        // go through each array list element to make sure they are all
        // blocked off from random food generation

        void getFoodPos(objPos &returnPos);
        objPosArrayList* getFoodBucket();
        

};




#endif