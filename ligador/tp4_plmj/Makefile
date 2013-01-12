#----- Variáveis de path -----#
SRC_MONTADOR=./src_montador
SRC_LIGADOR=./src_ligador

#----- Regras para make -----#
all: montador ligador clean

#----- Regras para Montador -----#
montador:	mounterdata.o mounter.o
	gcc -o montador $(SRC_MONTADOR)/main.o $(SRC_MONTADOR)/mounterdata.o
mounterdata.o:	$(SRC_MONTADOR)/mounterdata.c
	gcc -o $(SRC_MONTADOR)/mounterdata.o -c $(SRC_MONTADOR)/mounterdata.c -Wall
mounter.o: $(SRC_MONTADOR)/mounter.c $(SRC_MONTADOR)/mounterdata.h
	gcc -o $(SRC_MONTADOR)/main.o -c $(SRC_MONTADOR)/mounter.c -Wall

#----- Regras para Ligador -----#
ligador:	linkerdata.o linker.o
	gcc -o ligador $(SRC_LIGADOR)/main.o $(SRC_LIGADOR)/linkerdata.o
linkerdata.o:	$(SRC_LIGADOR)/linkerdata.c
	gcc -o $(SRC_LIGADOR)/linkerdata.o -c $(SRC_LIGADOR)/linkerdata.c -Wall
linker.o: $(SRC_LIGADOR)/linker.c $(SRC_LIGADOR)/linkerdata.h
	gcc -o $(SRC_LIGADOR)/main.o -c $(SRC_LIGADOR)/linker.c -Wall

#----- Regras para limpeza -----#
clean: cleanm cleanl
cleanm:
	rm -rf $(SRC_MONTADOR)/*.o
cleanl:
	rm -rf $(SRC_LIGADOR)/*.o

#----- Regras para remoção -----#
remove: clean removel removem
removel:
	rm -rf ligador
removem:
	rm -rf montador
