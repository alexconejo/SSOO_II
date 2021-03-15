DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
DIRUTILS := utils/

CFLAGS := -c 
LDLIBS := -lpthread -lrt
CC := gcc

all : dirs manager PA PB PC PD daemon

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

manager: $(DIROBJ)manager.o 
	$(CC) -o $(DIREXE)$@ $^ $(LDLIBS)

PA: $(DIROBJ)PA.o 
	$(CC) -o $(DIREXE)$@ $^ 

PB: $(DIROBJ)PB.o 
	$(CC) -o $(DIREXE)$@ $^

PC: $(DIROBJ)PC.o 
	$(CC) -o $(DIREXE)$@ $^ 

PD: $(DIROBJ)PD.o 
	$(CC) -o $(DIREXE)$@ $^ 

daemon: $(DIROBJ)daemon.o 
	$(CC) -o $(DIREXE)$@ $^ 

$(DIROBJ)%.o: $(DIRSRC)%.c
	$(CC) $(CFLAGS) $^ -o $@

solution:
	./$(DIREXE)manager 

clean : 
	rm -rf *~ $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ $(DIRUTILS)estudiantes 
