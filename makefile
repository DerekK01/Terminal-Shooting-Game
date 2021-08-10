CC = gcc
CFLAGS = -Wall -pedantic -ansi -g -Werror
OBJ = main.o setup.o directionSymbol.o userInterface.o event.o newSleep.o input.o linkedlist.o linklistfuncptr.o
EXEC = laserTank

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c setup.h userInterface.h event.h macro.h input.h linkedlist.h
	$(CC) -c main.c $(CFLAGS)

setup.o : setup.c setup.h directionSymbol.h
	$(CC) -c setup.c $(CFLAGS)

directionSymbol.o : directionSymbol.c directionSymbol.h
	$(CC) -c directionSymbol.c $(CFLAGS)

userInterface.o : userInterface.c userInterface.h directionSymbol.h newSleep.h macro.h
	$(CC) -c userInterface.c $(CFLAGS)

event.o : event.c event.h directionSymbol.h newSleep.h userInterface.h macro.h
	$(CC) -c event.c $(CFLAGS)
	

newSleep.o : newSleep.c newSleep.h
	$(CC) -c newSleep.c $(CFLAGS)

input.o : input.c input.h
	$(CC) -c input.c $(CFLAGS)

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) -c linkedlist.c $(CFLAGS)

linklistfuncptr.o : linklistfuncptr.c linklistfuncptr.h
	$(CC) -c linklistfuncptr.c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)
