SRC=./src
all:	montador clean
montador:	mounterdata.o main.o
	gcc -o montador $(SRC)/main.o $(SRC)/mounterdata.o
mounterdata.o:	$(SRC)/mounterdata.c
	gcc -o $(SRC)/mounterdata.o -c $(SRC)/mounterdata.c -Wall
main.o: $(SRC)/mounter.c $(SRC)/mounterdata.h
	gcc -o $(SRC)/main.o -c $(SRC)/mounter.c -Wall
clean:
	rm -rf $(SRC)/*.o
remove: clean
	rm -rf montador
