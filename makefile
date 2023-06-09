CC = g++
RM = rm -f
VOR = Voraz/voraz
GENV = Generador/generador_voraz
GENPVC = Generador-pvc/generador_pvc
DGEN1 = Generador/datagen
DGEN2 = Generador-pvc/datagen
OBJS = $(VOR).o $(GENV).o $(GENPVC).o Pvc1/pvc1.o Pvc2/pvc2.o Pvc3/pvc3.o 
EXEC = $(VOR) $(DGEN1) $(DGEN2) Pvc1/pvc1 Pvc2/pvc2 Pvc3/pvc3

all: pvc1 pvc2 pvc3 voraz datagen1 datagen2

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

datagen1: $(GENV).o
	$(CC) $(GENV).o -o $(DGEN1)

generador_voraz.o: $(GENV).cpp
	$(CC) -o $(GENV).cpp

datagen2: $(GENPVC).o
	$(CC) $(GENPVC).o -o $(DGEN2)

generador_pvc.o: $(GENPVC).cpp
	$(CC) -o $(GENPVC).cpp
	
clean:
	$(RM) $(OBJS) $(EXEC) Generador/data Generador-pvc/data
	
cleanobj:
	$(RM) $(OBJS)

cleanexec:
	$(RM) $(EXEC)


