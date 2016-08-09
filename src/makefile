CC 	  	 = gcc
CLIBS	 = -lapue -L$(UCHOME)/source/mylib
CHEADERS = -I$(UCHOME)/source/myheaders

pager: pager.o
	$(CC) -o $@ pager.o $(CLIBS)

pager.o: pager.c
	$(CC) -c -o $@ pager.c $(CHEADERS)

clean:
	rm *.o pager
