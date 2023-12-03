#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    boardSizeX = 20;    // default board size
    boardSizeY = 10;
    score = 0;
    loseFlag = false;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    boardSizeX = boardX;    
    boardSizeY = boardY;
    score = 0;
    loseFlag = false;
}

// do you need a destructor?

GameMechs::~GameMechs()
{
    
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    if(input == 27)
    {
        exitFlag = true;
        
    }
    else if(input == 0)
    {
        return '\0';
    }
    return input;

}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore(int points)
{
    score += points;
}


