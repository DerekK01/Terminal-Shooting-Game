#include <stdio.h>
#include "newSleep.h"
#include "directionSymbol.h"
#include "userInterface.h"
#include "macro.h"
#include "event.h"
#include "linkedlist.h"

/* Static function declaration */
static void laserAnimation(int mapRow, int mapCol, int playerRow, int playerCol, char playerDir, int upDown, int leftRight, char symbol, char **playerArea, int *gameStatus, int enemyDetect, int *laserRow, int *laserCol, char *laserDir, int temp_enemyRow, int temp_enemyCol, int temp_playerRow, int temp_playerCol, LinkedList*Loglist);

/**
 * Update the player location according to the user input
 * 
 * Parameters
 * input          - the character of the user input
 * playerArea     - a 2D array (the map)
 * playerRow      - an integer pointer (the row of the current player location).
 * playerCol      - an integer pointer (the coloum of the current player location).
 * playerDir      - an character pointer (the direction of the current player).
 * enemyDir       - a character (the direction of the enemy)
 */
void playerMovement(char input, char **playerArea, int *playerRow, int *playerCol, char *playerDir, char enemyDir)
{
    /* if the input is the same as the player direction then the player will move */
    if (input == *playerDir)
    {
        /* Assign space for the current player location */
        playerArea[*playerRow][*playerCol] = ' ';

        /* Update the player location depending on their direction */
        switch (input)
        {
        case 'l':
            /* check if * and enemy is at the left of the player location */
            if (playerArea[*playerRow][*playerCol - 1] != '*' && playerArea[*playerRow][*playerCol - 1] != getSymbol(enemyDir) && playerArea[*playerRow][*playerCol - 1] != '\\' && playerArea[*playerRow][*playerCol - 1] != '/')
            {
                /* move the player to the left */
                *playerCol -= 1;
            }
            break;
        case 'r':
            if (playerArea[*playerRow][*playerCol + 1] != '*' && playerArea[*playerRow][*playerCol + 1] != getSymbol(enemyDir) && playerArea[*playerRow][*playerCol + 1] != '\\' && playerArea[*playerRow][*playerCol + 1] != '/')
            {
                *playerCol += 1;
            }
            break;
        case 'd':
            if (playerArea[*playerRow + 1][*playerCol] != '*' && playerArea[*playerRow + 1][*playerCol] != getSymbol(enemyDir) && playerArea[*playerRow + 1][*playerCol] != '\\' && playerArea[*playerRow + 1][*playerCol] != '/')
            {
                *playerRow += 1;
            }
            break;
        case 'u':
            if (playerArea[*playerRow - 1][*playerCol] != '*' && playerArea[*playerRow - 1][*playerCol] != getSymbol(enemyDir) && playerArea[*playerRow - 1][*playerCol] != '\\' && playerArea[*playerRow - 1][*playerCol] != '/')
            {
                *playerRow -= 1;
            }
            break;
        }
    }
    else
    {
        /* if the input is not the same as the player direction 
           The player will now faced that direction */
        *playerDir = input;
    }
    /* update the player Symbol eg '>' '<' '^' 'V' */
    playerArea[*playerRow][*playerCol] = getSymbol(*playerDir);
}

/**
 * Start the laser animation according to the player location
 * 
 * Parameters
 * mapRow         - the integer of the player Area row
 * mapCol         - the integer of the player Area column
 * playerRow      - an integer (the row of the current player location).
 * playerCol      - an integer (the coloum of the current player location).
 * playerDir      - an character (the direction of the current player).
 * enemyDir       - a character (the direction of the enemy)
 * playerArea     - a 2D array (the map)
 * gameStatus     - a pointer to the current game status (WIN/LOSS/PROGRESS)
 * enemyDetect    - a integer with true/false (TRUE if this function is used as player detection)
 */
void laser(int mapRow, int mapCol, int playerRow, int playerCol, char playerDir, char **playerArea, int *gameStatus, int enemyDetect, int *laserRow, int *laserCol, char *laserDir, int temp_enemyRow, int temp_enemyCol, int temp_playerRow, int temp_playerCol, LinkedList* logList)
{
    int leftRight = 0;
    int upDown = 0;
    int symbol;
    /* get the laser symbol according to the player direction eg '-' '|' */
    symbol = getLaserSymbol(playerDir);
    /* if the player is facing right */
    if (playerDir == 'r')
    {
        /* set leftRight to Right */
        leftRight = RIGHT;
        /* Call the laser animation function */
        laserAnimation(mapRow, mapCol, playerRow, playerCol, playerDir, upDown, leftRight, symbol, playerArea, gameStatus, enemyDetect, laserRow, laserCol, laserDir, temp_enemyRow, temp_enemyCol, temp_playerRow, temp_playerCol,logList);
    }
    else if (playerDir == 'l')
    {
        leftRight = LEFT;
        laserAnimation(mapRow, mapCol, playerRow, playerCol, playerDir, upDown, leftRight, symbol, playerArea, gameStatus, enemyDetect, laserRow, laserCol, laserDir, temp_enemyRow, temp_enemyCol, temp_playerRow, temp_playerCol,logList);
    }
    else if (playerDir == 'u')
    {
        /* set upDown to up */
        upDown = UP;
        /* Call the laser animation function */
        laserAnimation(mapRow, mapCol, playerRow, playerCol, playerDir, upDown, leftRight, symbol, playerArea, gameStatus, enemyDetect, laserRow, laserCol, laserDir, temp_enemyRow, temp_enemyCol, temp_playerRow, temp_playerCol,logList);
    }
    else if (playerDir == 'd')
    {
        upDown = DOWN;
        laserAnimation(mapRow, mapCol, playerRow, playerCol, playerDir, upDown, leftRight, symbol, playerArea, gameStatus, enemyDetect, laserRow, laserCol, laserDir, temp_enemyRow, temp_enemyCol, temp_playerRow, temp_playerCol,logList);
    }
}

/* Initiate the laser animation */
static void laserAnimation(int mapRow, int mapCol, int playerRow, int playerCol, char playerDir, int upDown, int leftRight, char symbol, char **playerArea, int *gameStatus, int enemyDetect, int *laserRow, int *laserCol, char *laserDir,int temp_enemyRow, int temp_enemyCol, int temp_playerRow, int temp_playerCol,LinkedList* logList)
{
    int i;
    int stop = 1;
    /* check if the laser is next to the border and loop until it is next to it*/
    for (i = 1; playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] != '*' && stop != 0; i++)
    {
        /* check if the laser is next to the enemy */
        if (playerRow + (i * upDown) == temp_enemyRow && playerCol + (i * leftRight) == temp_enemyCol)
        {
            /* set the position of the enemy to 'X' */
            playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] = 'X';
            /* print the array once more time */
            userInterface(playerArea, mapRow, mapCol,logList);
            *gameStatus = WIN;
            stop = 0;
        }
        /* check if the laser is next to the player*/
        else if (playerRow + (i * upDown) == temp_playerRow && playerCol + (i * leftRight) == temp_playerCol)
        {
            /* if enemy detect is true, game end because player is in the line of sight of the enemy */
            if (enemyDetect)
            {
                *gameStatus = LOSS;
            }
            else
            {
                /* the laser reflected and kill the player*/
                playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] = 'X';
                userInterface(playerArea, mapRow, mapCol,logList);
                /* player killed themself*/
                *gameStatus = PLAYERLOSS;
            }
            stop = 0;
        }
        /* check if it is next to the mirror*/
        else if (playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] == '\\')
        {
            /* change the laser direction */
            *laserRow = playerRow + (i * upDown);
            *laserCol = playerCol + (i * leftRight);
            *gameStatus = MIRROR;
            switch (playerDir)
            {
            case 'r':
                *laserDir = 'd';
                break;
            case 'l':
                *laserDir = 'u';
                break;
            case 'u':
                *laserDir = 'l';
                break;
            case 'd':
                *laserDir = 'r';
                break;
            }
            stop = 0;
        }
        /* check if it is next to the mirror*/
        else if (playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] == '/')
        {
            /* change the laser direction */
            *laserRow = playerRow + (i * upDown);
            *laserCol = playerCol + (i * leftRight);
            *gameStatus = MIRROR;
            switch (playerDir)
            {
            case 'r':
                *laserDir = 'u';
                break;
            case 'l':
                *laserDir = 'd';
                break;
            case 'u':
                *laserDir = 'r';
                break;
            case 'd':
                *laserDir = 'l';
                break;
            }
            stop = 0;
        }
        else
        {
            /* if the enemyDetect is not turn on */
            if (!enemyDetect)
            {
                /* assign the laser symbol eg '-' '|' */
                playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] = symbol;
                /* print the 2D array/User interface */
                userInterface(playerArea, mapRow, mapCol,logList);
                /* sleep for 0.1 second */
                newSleep(0.1);
                /* assign a space to the current laser position */
                playerArea[playerRow + (i * upDown)][playerCol + (i * leftRight)] = ' ';

                *gameStatus = PROGRESS;
            }
        }
    }
}