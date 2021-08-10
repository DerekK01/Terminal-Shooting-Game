#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"
#include "userInterface.h"
#include "event.h"
#include "macro.h"
#include "struct.h"
#include "linkedlist.h"
#include "input.h"

/* get thee settings from the input file*/
void getFileInput(Setting* input, char* fileName, LinkedList* mirrorList)
{
    /*open the file in read mode*/
    FILE *file = fopen(fileName, "r");
    /*error if we cant open the file*/
    if (file == NULL)
    {
        perror("Error opening the file");
    }
    else
    {
        /* create a mirror struc pointer*/
        Mirror* mirrorData= (Mirror *)malloc(sizeof(Mirror));
        /*assigned all the input to the input struc*/
        fscanf(file,"%d %d %d %d %c %d %d %c ", &input->mapRow,&input->mapCol,&input->playerRow,&input->playerCol,&input->playerDir,&input->enemyRow,&input->enemyCol,&input->enemyDir);
        while(fscanf(file, "%d %d %c ", &mirrorData->mirrorRow, &mirrorData->mirrorCol, &mirrorData->mirrorDir) == 3)
        {
            /*assigned all the mirror data to the mirror linkedlist*/
            insertLast(mirrorList, mirrorData);
            mirrorData = (Mirror *)malloc(sizeof(Mirror));
        }
        /*free struc pointer and close the fiile*/
        free(mirrorData);
        mirrorData = NULL;
        fclose(file);
    }
}