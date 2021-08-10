#include <stdio.h>
#include "directionSymbol.h"

/* Return the corresponding player/enemy symbol according to the direction */
char getSymbol(char direction)
{
    char symbol;
    /* assigned variable symbol depending on the direction */
    switch (direction)
    {
    case 'u': symbol = '^'; break;
    case 'd': symbol = 'V'; break;
    case 'l': symbol = '<'; break;
    case 'r': symbol = '>'; break;
    }
    return symbol;
}


/* Return the corresponding direction according to the input */
char getDirection(char input)
{
    int direction;
    /* assigned variable direction depending on the user input */
    switch (input)
    {
    case 'd': direction = 'r'; break;
    case 'a': direction = 'l'; break;
    case 'w': direction = 'u'; break;
    case 's': direction = 'd'; break;
    }
    return direction;
}

/* Return the corresponding laser symbol according to the direction */
char getLaserSymbol(char direction)
{
    char symbol;
    /* assigned variable symbol depending on the direction */
    switch (direction)
    {
    case 'u': symbol = '|'; break;
    case 'd': symbol = '|'; break;
    case 'l': symbol = '-'; break;
    case 'r': symbol = '-'; break;
    }
    return symbol;
}


char getMirrorDirection(char direction)
{
    char symbol;
    switch (direction)
    {
    case 'f': symbol = '/'; break;
    case 'b': symbol = '\\'; break;
    }
    return symbol;
}
