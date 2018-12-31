EXE=yamsStat
FLAGS= -Wall -g 

$(EXE) : yamsStat.o
	gcc -o $(EXE) yamsStat.o

yamsStat.o : yamsStat.c
	gcc $(FLAGS) -c yamsStat.c

clean : 
	rm -f -v *.gch *.o
.PHONY : clean

cleanall : clean
	rm -f -v $(EXE)
	rm -f -v *.data
	rm -f -v Rplots.pdf
.PHONY : cleanal