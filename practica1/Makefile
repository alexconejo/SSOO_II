
# Macros

CC = gcc
DIRS = ./src/
DIRE = ./exec/

# Reglas explícitas

all: $(DIRS)manager.c $(DIRS)PA.c $(DIRS)PB.c $(DIRS)PC.c $(DIRS)PD.c $(DIRS)daemon.c 
		$(CC) $(DIRS)manager.c -o $(DIRE)manager.o
		$(CC) $(DIRS)PA.c -o $(DIRE)PA.o
		$(CC) $(DIRS)PB.c -o $(DIRE)PB.o
		$(CC) $(DIRS)PC.c -o $(DIRE)PC.o
		$(CC) $(DIRS)PD.c -o $(DIRE)PD.o
		$(CC) $(DIRS)daemon.c -o $(DIRE)daemon.o

manager: 

clean:
	rm -rf $(DIRE)*.o