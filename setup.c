#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"
#include "directionSymbol.h"
#include "struct.h"
#include "linkedlist.h"

#define ERROR 1
#define SUCCESS !ERROR
#define MAPMIN 5
#define MAPMAX 25

/* Declare the static function */
static int setupCheck(int mapRow, int mapCol, int playerRow, int playerCol, int enemyRow, int enemyCol, char playerDir, char enemyDir);
static void mapSetup(int mapRow, int mapCol, char **playerArea);
static void mirrorSetup(char **playerArea, LinkedList *mirrorList, int *status, int mapRow, int mapCol, int playerRow, int playerCol, int enemyRow, int enemyCol, char enemyDir);
static void mirrorDetect(int mapRow, int mapCol, int mirrorRow, int mirrorCol, int enemyRow, int enemyCol, char enemyDir, int *status);
/* check if the argument is correct, and check if the player/enemy is out of bound */
static int setupCheck(int mapRow, int mapCol, int playerRow, int playerCol, int enemyRow, int enemyCol, char playerDir, char enemyDir)
{
    int status;
    /* Check if the map area is between 5 to 25 */
    if (MAPMIN <= mapRow && mapRow <= MAPMAX && MAPMIN <= mapCol && mapCol <= MAPMAX)
    {
        /* Check if the player is outside or at the border of the map */
        if (playerRow > 0 && playerRow < mapRow - 1 && playerCol > 0 && playerCol < mapCol - 1)
        {
            /* Check if the enemy is outside or at the border of the map */
            if (enemyRow > 0 && enemyRow < mapRow - 1 && enemyCol > 0 && enemyCol < mapCol - 1)
            {
                /* Check if the player direction is valid */
                if (playerDir != 'r' && playerDir != 'l' && playerDir != 'u' && playerDir != 'd')
                {
                    status = ERROR;
                    printf("\n[ERROR] Unknow player direction");
                }
                else
                {
                    /* Check if the enemy direction is valid */
                    if (enemyDir != 'r' && enemyDir != 'l' && enemyDir != 'u' && enemyDir != 'd')
                    {
                        status = ERROR;
                        printf("\n[ERROR] Unknow enemy direction");
                    }
                    else
                    {
                        status = SUCCESS;
                    }
                }
            }
            else
            {
                status = ERROR;
                printf("\n[ERROR] Enemy position is outside the map or at the border.");
            }
        }
        else
        {
            status = ERROR;
            printf("\n[ERROR] Player position is outside the map or at the border.");
        }
    }
    else
    {
        status = ERROR;
        printf("\n[ERROR] Map Row and Column must be between 5 to 25 ");
    }
    return status;
}

/* Set up the 2D array and the boundary as well as the player and enemy */
void setup(int mapRow, int mapCol, int playerRow, int playerCol, char playerDir, int enemyRow, int enemyCol, char enemyDir, char **playerArea, int *status, LinkedList *mirrorList)
{
    int check;
    /* Initiate the check function, to check if value is valid */
    check = setupCheck(mapRow, mapCol, playerRow, playerCol, enemyRow, enemyCol, playerDir, enemyDir);
    if (check == SUCCESS)
    {
        /* Initiate the mapSetup function which will set up our 2D array with the border */
        mapSetup(mapRow, mapCol, playerArea);
        mirrorSetup(playerArea, mirrorList, status, mapRow, mapCol,playerRow,playerCol,enemyRow,enemyCol,enemyDir);
        /* set the player/enemy symbol and location */
        playerArea[playerRow][playerCol] = getSymbol(playerDir);
        playerArea[enemyRow][enemyCol] = getSymbol(enemyDir);
        if (*status != ERROR)
        {
            *status = SUCCESS;
        }
    }
    else
    {
        printf("\n[ERROR] Setup failed\n");
        *status = ERROR;
    }
}

/* set up the 2D array with border */
static void mapSetup(int mapRow, int mapCol, char **playerArea)
{
    int row_i, col_i;
    /* Loop and assigned value for the player Area 2D array */
    for (row_i = 0; row_i < mapRow; row_i++)
    {
        for (col_i = 0; col_i < mapCol; col_i++)
        {
            /* Assigned space for every value aside from the first row and last row  */
            if (row_i != 0 && row_i != mapRow - 1)
            {
                playerArea[row_i][col_i] = ' ';
            }
            /* Assigned * for the first row and the last row */
            playerArea[0][col_i] = '*';
            playerArea[mapRow - 1][col_i] = '*';
        }
        /* Assigned * for the first column and the last column */
        playerArea[row_i][0] = '*';
        playerArea[row_i][mapCol - 1] = '*';
    }
}

/* setup the mirror */
static void mirrorSetup(char **playerArea, LinkedList *mirrorList, int *status, int mapRow, int mapCol, int playerRow, int playerCol, int enemyRow, int enemyCol, char enemyDir)
{
    int i;
    Mirror *mirrorData;
    for (i = 0; i < mirrorList->count; i++)
    {
        mirrorData = (Mirror *)getNodeData(mirrorList, i);
        /* check if the miirror is in the bound of the map*/
        if (mirrorData->mirrorRow > 0 && mirrorData->mirrorRow < mapRow-1 && mirrorData->mirrorCol > 0 && mirrorData->mirrorCol < mapCol-1)
        {
            /*check if the mirror overlap the player*/
            if (mirrorData->mirrorRow == playerRow && mirrorData->mirrorCol == playerCol)
            {
                *status = ERROR;
                printf("[ERROR] Mirror overlap with the player location! \n");
                i = mirrorList->count;
            }
            else
            {
                /*check if the mirror overlap the enemy*/
                if (mirrorData->mirrorRow == enemyRow && mirrorData->mirrorCol == enemyCol)
                {
                    *status = ERROR;
                    printf("[ERROR] Mirror overlap with the enemy location! \n");
                    i = mirrorList->count;
                }
                else
                {
                    /*check if the mirror is in the line of sight of the enemy*/
                    mirrorDetect(mapRow,mapCol,mirrorData->mirrorRow,mirrorData->mirrorCol,enemyRow,enemyCol,enemyDir,status);
                    if (*status == ERROR)
                    {
                        printf("[ERROR] Mirror is in the line of sight of the enemy! \n");
                        i = mirrorList->count;
                    }
                    else
                    {
                        /*print the mirror*/
                        playerArea[mirrorData->mirrorRow][mirrorData->mirrorCol] = getMirrorDirection(mirrorData->mirrorDir);
                    }
                }
            }
           
        }
        else
        {
            *status = ERROR;
            printf("[ERROR] Mirror is outside the map! \n");
            i = mirrorList->count;
        }
    }
}

/* Detect if the mirror is in the line of sight of the enemy, if yes status = error */
static void mirrorDetect(int mapRow, int mapCol, int mirrorRow, int mirrorCol, int enemyRow, int enemyCol, char enemyDir, int *status)
{
    int i;
    /* if the enemy is facing left */
    if (enemyDir == 'l')
    {
        /* check if the mirror is in the left side of the enemy, eg. column 0 to the enemy column */
        for (i = 0; i != enemyCol; i++)
        {
            /* check if the mirror is on the same row as the enemy */
            if (mirrorRow == enemyRow && mirrorCol == i)
            {
                /* return error */
                *status = ERROR;
            }
        }
    }
    if (enemyDir == 'r')
    {
        for (i = mapCol - 1; i != enemyCol; i--)
        {
            if (mirrorRow == enemyRow && mirrorCol == i)
            {
                *status = ERROR;
            }
        }
    }
    if (enemyDir == 'd')
    {
        for (i = mapRow - 1; i != enemyRow; i--)
        {
            if (mirrorRow == i && mirrorCol == enemyCol)
            {
                *status = ERROR;
            }
        }
    }
    if (enemyDir == 'u')
    {
        for (i = 0; i != enemyRow; i++)
        {
            if (mirrorRow == i && mirrorCol == enemyCol)
            {
                *status = ERROR;
            }
        }
    }
}