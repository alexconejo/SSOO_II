DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/

CFLAGS := -c 
LDLIBS := -lpthread -lrt
CC := gcc

all : dirs manager PA PB PC PD daemon

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

manager: $(DIROBJ)manager.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PA: $(DIROBJ)PA.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PB: $(DIROBJ)PB.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PC: $(DIROBJ)PC.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PD: $(DIROBJ)PD.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

daemon: $(DIROBJ)daemon.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

solution:
	./$(DIREXE)manager 

clean : 
	rm -rf *~ $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~
