#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include "Food.h"
#include <cstdlib>
#include <time.h>



using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

objPos playerPos; // I added this

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    srand((unsigned)time(NULL));

    myGM = new GameMechs(30,15); // make the board size 30x15
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    
    objPos tempPos{-1, -1, 'o'};
    myFood->generateFood(tempPos,myPlayer->getPlayerPos()); // parameter is blockOff position so I put playerPos so that a food can't spawn on the player
     
    // Think about when to generate the new Food...

    // Think about whether you want to set up a debug key to call
    // the food generation routine for verification

    // remember, generateFood() requires player reference.
    // You will need to provide it AFTER player object is instantiated
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    
    myPlayer->updatePlayerDir();
    myPlayer->checkFoodConsumption();
    myPlayer->movePlayer();
   
    // Check for self collision
    if(myPlayer->checkSelfCollision())
    {
        // Handle the case when the player collides with itself
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }
    
    // Clear input for next loop/iteration/frame
    myGM->clearInput();
}

void DrawScreen(void) // drawscreen is allowed to be procedural programming for drawing border stuff as mentioned in week 12 tutorial
{
    MacUILib_clearScreen();

    bool bodyDrawn;
    bool foodDrawn;
    
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos drawPos;
    objPos tempFoodPos;

    for(int y = 0;y < myGM->getBoardSizeY(); y++)
    {
        for(int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            bodyDrawn = false;
            foodDrawn = false;

            // iterate through every element in the list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody,k);
                if(tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    bodyDrawn = true;
                    break;
                }
            }

            if(bodyDrawn) continue;
            // if player body was drawn, don't draw anything below.

            if(y==0 || y == myGM->getBoardSizeY() - 1 || x==0 || x== myGM->getBoardSizeX() -1)
            {
                // Draw border with #
                drawPos.setObjPos(x,y,'#');
                MacUILib_printf("%c",drawPos.getSymbol());
            }
            else
            {
                
                // Food Printing
                for(int i=0 ; i<5 ; i++) {
                    objPosArrayList* foodBucket = myFood->getFoodBucket();
                    foodBucket->getElement(tempFoodPos, i);
                    if(tempFoodPos.x == x && tempFoodPos.y == y) {
                        MacUILib_printf("%c", tempFoodPos.getSymbol());
                        foodDrawn = true;
                        break;
                    }
                }
                // If food is here, don't print space
                if (foodDrawn) continue;
                
                // Whitespace Printing
                drawPos.setObjPos(x,y,' ');
                MacUILib_printf("%c", drawPos.getSymbol());
            }
        }
        MacUILib_printf("\n"); // Move to the next line after each row
    }

    // Score Print Out
    MacUILib_printf("Score: %d\n", myGM->getScore());   
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 

    // Seperate end messages
    bool endType = myGM->getLoseFlagStatus();
    if(endType) {
        MacUILib_printf("Game Ended. You Scored: %d Points!\n",myGM->getScore());
    }
    else {
        MacUILib_printf("Game Quit. You Scored: %d Points!\n",myGM->getScore());
    }
    

    MacUILib_uninit();

    delete myFood;
    delete myPlayer;
    delete myGM;
}
