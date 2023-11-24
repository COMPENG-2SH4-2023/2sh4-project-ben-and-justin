#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
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

    myGM = new GameMechs(30,15); // make the board size 20x10
    myPlayer = new Player(myGM);
    myFood = new Food(myGM);

    myFood->generateFood(playerPos); // parameter is blockOff position so I put playerPos so that a food can't spawn on the player
     
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
    myPlayer->movePlayer();
    
    myGM->clearInput();
   
    
}

void DrawScreen(void) // drawscreen is allowed to be procedural programming for drawing border stuff as mentioned in week 12 tutorial
{
    MacUILib_clearScreen();

    bool drawn;
    
    objPosArrayList* playerBody = getPlayerPos();
    objPos tempBody;

    objPos drawPos;
    objPos tempFoodPos;
    
   
    myFood->getFoodPos(tempFoodPos); // get the food pos

    for(int y = 0;y < myGM->getBoardSizeY(); y++)
    {
        for(int x = 0; x < myGM->getBoardSizeX(); x++)
        {
            drawn = false;

            // iterate through every element in the list
            for(int k = 0; k < playerBody->getSize(); k++)
            {
                playerBody->getElement(tempBody,y);
                if(tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;
            // if player body was drawn, don't draw anything below.

            if(y==0 || y == myGM->getBoardSizeY() - 1 || x==0 || x== myGM->getBoardSizeX() -1)
            {
                // Draw border with #
                drawPos.setObjPos(x,y,'#');
                MacUILib_printf("%c",drawPos.getSymbol());
            }
            else
            {
                // Draw space in the middle
                drawPos.setObjPos(x,y,' ');
                // If a character is here, don't print space
                
                else if(x == tempFoodPos.x && y == tempFoodPos.y)
                {
                    MacUILib_printf("%c", tempFoodPos.getSymbol());
                }
                else
                {
                    MacUILib_printf("%c", drawPos.getSymbol());
                }
            }
        }
        MacUILib_printf("\n"); // Move to the next line after each row
    }


    MacUILib_printf("BoardSize: %d%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX(),myGM->getBoardSizeY(),tempPos.x, tempPos.y,tempPos.symbol);
    MacUILib_printf("Food Pos: <%d, %d> + %c\n", tempFoodPos.x, tempFoodPos.y, tempFoodPos.getSymbol());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    
    delete myPlayer;

    delete myFood;
    
}
