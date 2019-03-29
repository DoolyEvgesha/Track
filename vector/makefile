OBJ = vector.o main.o
PROG = run
CFLAGS += -Wall -Werror -pedantic -g
HDR = vector.h
CC = g++

all : $(PROG)
main.cpp : $(HDR)
$(OBJ) : $(HDR)
	
$(PROG) : *.cpp
	$(CC) $^ -o $@ $(CFLAGS)
clean:
	$(RM) $(OBJ) $(PROG)
