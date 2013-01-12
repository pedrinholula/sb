SRC=./src
PROGRAM=expansor
MAIN=main
TAD=expansor
COMPILER=g++
EXTENSION=.cpp
all:	$(PROGRAM) clean
$(PROGRAM):	$(MAIN).o $(TAD).o
	$(COMPILER) -o $(PROGRAM) $(SRC)/$(MAIN).o $(SRC)/$(TAD).o
$(TAD).o:	$(SRC)/$(TAD)$(EXTENSION)
	$(COMPILER) -o $(SRC)/$(TAD).o -c $(SRC)/$(TAD)$(EXTENSION) -Wall
$(MAIN).o: $(SRC)/$(MAIN)$(EXTENSION) $(SRC)/$(TAD).h
	$(COMPILER) -o $(SRC)/$(MAIN).o -c $(SRC)/$(MAIN)$(EXTENSION) -Wall
clean:
	rm -rf $(SRC)/*.o
remove: clean
	rm -rf $(PROGRAM)
