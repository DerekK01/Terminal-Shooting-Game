#ifndef STRUCT_H
#define STRUCT_H

typedef struct 
{
    int mapRow;
    int mapCol;
    int enemyRow;
    int enemyCol;
    char enemyDir;
    int playerRow;
    int playerCol;
    char playerDir;
}Setting;

typedef struct 
{
    int mirrorRow;
    int mirrorCol;
    char mirrorDir;
}Mirror;

typedef struct 
{
    int row;
    int col;
    char** playerArea;
}StorePlayerArea;


#endif