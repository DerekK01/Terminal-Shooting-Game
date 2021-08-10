#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"
#include "userInterface.h"
#include "event.h"
#include "macro.h"
#include "struct.h"
#include "linkedlist.h"
#include "linklistfuncptr.h"

/* function pointer for writing the linkedlist to the log file */
void outputData(FILE *file, void *data)
{

    int i, x;
    /* typecast the data */
    StorePlayerArea *mapData = (StorePlayerArea *)data;
    if (file == NULL)
    {
        perror("Error opening the file");
    }
    else
    {
        /* loop through the array and print to the file */
        for (i = 0; i < mapData->row; i++)
        {
            for (x = 0; x < mapData->col; x++)
            {
                fprintf(file, "%c", mapData->playerArea[i][x]);
                if (x == mapData->col - 1)
                {
                    fprintf(file, "\n");
                }
            }
        }
        fprintf(file, "\n");
        fprintf(file, "=======================================\n");
        fprintf(file, "\n");
    }
}

/* function pointer for freeing the log linkedlist */
void freeLogData(void *data)
{
    int i;
    /* typecast the data*/
    StorePlayerArea* mapData = (StorePlayerArea*)data;
    /* free the 2D array */
    for (i = 0; i < mapData->row; i++)
    {
        free(mapData->playerArea[i]);
        mapData->playerArea[i] = NULL;
    }
    free(mapData->playerArea);
    free(data);
}

/* function pointer for freeing the mirror linkedlist*/
void freeMirrorData(void *data)
{
    free(data);
}