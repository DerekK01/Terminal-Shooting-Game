#include <stdio.h>
#include "newSleep.h"
#include "directionSymbol.h"
#include <stdlib.h>
#include "macro.h"
#include "userInterface.h"
#include "struct.h"
#include "linkedlist.h"
#include <unistd.h>


/* Declare static function */
static void bonusRainbowColour();

/* print the 2D array and the updated player location */
void userInterface(char **playerArea, int mapRow, int mapCol, LinkedList* logList)
{
    int row, col,i;
    /*create a struc to store the data*/
    StorePlayerArea* storeData = (StorePlayerArea*)malloc(sizeof(StorePlayerArea));
    /* create a 2D array to store the data */
    char**logData = (char **)malloc(mapRow * sizeof(char *));
    for (i = 0; i < mapRow; i++)
    {
        logData[i] = (char *)malloc(mapCol * sizeof(char));
    }
    

    /* clear the screen */
    system("clear");
    /* Loop through the whole 2D array */
    for (row = 0; row < mapRow; row++)
    {
        for (col = 0; col < mapCol; col++)
        {
            /* if the character is '-' or '|', it will change the color to red */
            if (playerArea[row][col] == '-' || playerArea[row][col] == '|')
            {
                bonusRainbowColour();
            }
            /* print out the value in the array */
            printf("%c ", playerArea[row][col]);
            logData[row][col] = playerArea[row][col];
            printf("\033[0m");
            /* If it reach the end of the column, it will start a new line */
            if (col == mapCol - 1)
            {
                printf("\n");
            }
        }
    }
    /*insert the data to the log linkedd list*/
    storeData->row = mapRow;
    storeData->col= mapCol;
    storeData->playerArea = logData;
    insertLast(logList, storeData);

}

/* print the instruction and get the user input */
void getInput(char *input, int *status)
{
    /* print the instruction */
    printf("w to go/face up\n");
    printf("s to go/face down\n");
    printf("a to go/face left\n");
    printf("d to go/face right\n");
    printf("f to shoot laser\n");
    printf("l to save log file\n");
    printf("action: ");

    /* get user input */
    scanf(" %c", input);
    /* check if the input is Valid */
    if (*input != 'a' && *input != 's' && *input != 'd' && *input != 'w' && *input != 'f' && *input != 'l')
    {
        printf("\n [ERROR] Invalid input, please try again \n");
        newSleep(1);
        *status = ERROR;
    }
    else
    {
        /* check if the player is not shooting laser */
        if (*input != 'f' && *input != 'l')
        {
            /* change the user input in to a direction character eg. 'r' 'l' 'u' 'd' */
            *input = getDirection(*input);
        }
        /* check if the player pressed l */
        else if (*input == 'l')
        {
            *input = 'g';
        }
        *status = SUCCESS;
        printf("\n");
    }
}

/* print the winning screen */
void winningScreen()
{
    printf("\n");
    printf("========================================\n");
    printf("=       \\                      /       =\n");
    printf("=        \\ THANKS FOR PLAYING /        =\n");
    printf("=         \\     YOU WIN      /         =\n");
    printf("=          \\                /          =\n");
    printf("========================================\n");
}

/* print the lossing screen */
void lossingScreen()
{
    printf("\n");
    printf("=======================================\n");
    printf("=                                     =\n");
    printf("=           AWWWWWW MANN              =\n");
    printf("=        ;-;   YOU LOSE  ;-;          =\n");
    printf("=                                     =\n");
    printf("=======================================\n");
}


/* BONUS RAINBOW COLOUR LASER */
static void bonusRainbowColour()
{
    /* Do I need to comment on bonus section ?? LOL */

    /* Set colour change static variable to 0 */
    static int colorChanges = 0;
    /* Each time the function is called it will switch in to a different colour */
    switch (colorChanges)
    {
    case 0:
        printf("\033[1;31m");
        colorChanges++;
        break; /* Red    */
    case 1:
        printf("\033[1;33m");
        colorChanges++;
        break; /* Yellow */
    case 2:
        printf("\033[1;36m");
        colorChanges++;
        break; /* Cyan   */
    case 3:
        printf("\033[1;34m");
        colorChanges++;
        break; /* Blue   */
    case 4:
        printf("\033[1;35m");
        colorChanges = 0;
        break; /* Purple */
    }
}
