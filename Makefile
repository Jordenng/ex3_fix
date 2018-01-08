CC=gcc
CFLAGS= -std=c99 -Wall -Wextra -Wvla -c

#target : dep
#    command for bash


%.o:%.c %.h
	$(CC) $(CFLAGS) $< -o $@

HashIntSearch:libgenericHashTable.a MyIntFunctions.o HashIntSearch.o
	$(CC) MyIntFunctions.o HashIntSearch.o -L. libgenericHashTable.a -lm
	
HashStrSearch:libgenericHashTable.a MyStringFunctions.o HashStrSearch.o
	$(CC) MyStringFunctions.o HashStrSearch.o -L. libgenericHashTable.a -lm

libgenericHashTable.a: GenericHashTable.o TableErrorHandle.o Key.h
	ar rcs libgenericHashTable.a $^

clean:
	rm -f *.o *.a
