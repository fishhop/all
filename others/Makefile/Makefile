CC = gcc
CFLAGS = -Wall -O -g 

INC = ./include
BIN = ./bin
SRC = ./src

vpath %.h $(INC)
vpath %.c $(SRC)

TARGETS = myThread
OBJ = main.o thread.o userInterface.o 

all : $(TARGETS) clean
#clean 表示生成targets后运行下面的clean标号

myThread : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread 
	mv $(TARGETS) $(BIN)

main.o : main.c thread.h userInterface.h 
	$(CC) $(CFLAGS) -c $< -I$(INC)
	
thread.o : thread.c thread.h 
	$(CC) $(CFLAGS) -c $< -I$(INC)
	
userInterface.o : userInterface.c thread.h userInterface.h 
	$(CC) $(CFLAGS) -c $< -I$(INC)
	
.PHONY : all clean install uninstall

clean :
	rm $(OBJ)
install :  
	cp $(TARGETS) /usr/bin  
uninstall :  
	rm /usr/bin/$(TARGETS)
	
