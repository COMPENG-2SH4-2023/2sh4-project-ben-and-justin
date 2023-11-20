#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"



using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

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

    myGM = new GameMechs(30,15); // make the board size 20x10
    myPlayer = new Player(myGM);

    
}

void GetInput(void)
{
   myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    if(myGM->getInput()=='/')
    {
        myGM->setExitTrue();
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    objPos tempPos;
    objPos drawPos;
    myPlayer->getPlayerPos(tempPos); // get the player pos

    for(int y = 0;y<15;y++)
    {
        for(int x = 0;x<30;x++)
        {
            if(y==0 || y==14 || x==0 || x==29)
            {
                // Draw border with #
                drawPos.setObjPos(x,y,'#');
                MacUILib_printf("%c",drawPos.getSymbol());
            }
            else
            {
                // Draw space in the middle
                drawPos.setObjPos(x,y,' ');
                MacUILib_printf("%c",drawPos.getSymbol());
            }
        }
        MacUILib_printf("\n"); // Move to the next line after each row
    }


    MacUILib_printf("BoardSize: %d%d, Player Pos: <%d, %d> + %c\n", myGM->getBoardSizeX(),myGM->getBoardSizeY(),tempPos.x, tempPos.y,tempPos.symbol);

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
    myGM = NULL;
    delete myPlayer;
    
}
