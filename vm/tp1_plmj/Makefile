SRC=./src
all:	vm clean
vm:	vmdata.o main.o
	gcc -o vm $(SRC)/main.o $(SRC)/vmdata.o
vmdata.o:	$(SRC)/vmdata.c
	gcc -o $(SRC)/vmdata.o -c $(SRC)/vmdata.c -Wall
main.o: $(SRC)/vm.c $(SRC)/vmdata.h
	gcc -o $(SRC)/main.o -c $(SRC)/vm.c -Wall
clean:
	rm -rf $(SRC)/*.o
remove: clean
	rm -rf vm
