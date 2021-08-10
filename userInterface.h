#ifndef UI_H
#define UI_H
#include "linkedlist.h"
void userInterface(char **playerArea, int mapRow, int mapCol,LinkedList* logList);
void getInput(char *input, int* status);
void winningScreen();
void lossingScreen();

#endif