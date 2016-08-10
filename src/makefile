CC 	  	 = gcc
HOME	 = ..
CLIBS	 = -lapue -L$(HOME)/lib
CHEADERS = -I$(HOME)/headers

pager: pager.o
	$(CC) -o $@ pager.o $(CLIBS)

pager.o: pager.c
	$(CC) -c -o $@ pager.c $(CHEADERS)

clean:
	rm *.o 
