CC = g++
RM = rm -f
VOR = Voraz/voraz
GEN = Generador/data_generator
DGEN = Generador/datagen
OBJS = $(VOR).o $(GEN).o Pvc1/pvc1.o Pvc2/pvc2.o Pvc3/pvc3.o 
EXEC = $(VOR) $(DGEN) Pvc1/pvc1 Pvc2/pvc2 Pvc3/pvc3

all: pvc1 pvc2 pvc3 voraz datagen

pvc1: Pvc1/pvc1.o 
	$(CC) Pvc1/pvc1.o -o Pvc1/pvc1
	
pvc1.o: Pvc1/pvc1.cpp
	$(CC) -o Pvc1/pvc1.cpp 
	
pvc2: Pvc2/pvc2.o 
	$(CC) Pvc2/pvc2.o -o Pvc2/pvc2
	
pvc2.o: Pvc2/pvc2.cpp
	$(CC) -o Pvc2/pvc2.cpp 
	
pvc3: Pvc3/pvc3.o 
	$(CC) Pvc3/pvc3.o -o Pvc3/pvc3
	
pvc3.o: Pvc3/pvc3.cpp
	$(CC) -o Pvc3/pvc3.cpp 

voraz: $(VOR).o
	$(CC) $(VOR).o -o $(VOR)
	
voraz.o: $(VOR).cpp
	$(CC) -o $(VOR).cpp

datagen: $(GEN).o
	$(CC) $(GEN).o -o $(DGEN)

data_generator.o: $(GEN).cpp
	$(CC) -o $(GEN).cpp
	
clean:
	$(RM) $(OBJS) $(EXEC) Generador/data
	
cleanobj:
	$(RM) $(OBJS)

cleanexec:
	$(RM) $(EXEC)


