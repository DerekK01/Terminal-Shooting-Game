#ifndef EVENT_H
#define EVENT_H

void playerMovement(char input, char **playerArea, int *playerRow, int *playerCol, char *playerDir, char enemyDir);
void laser(int mapRow, int mapCol, int playerRow, int playerCol, char playerDir, char **playerArea, int *gameStatus, int enemyDetect, int *laserRow, int *laserCol, char *laserDir, int temp_enemyRow, int temp_enemyCol, int temp_playerRow, int temp_playerCol, LinkedList* logList);

#endif