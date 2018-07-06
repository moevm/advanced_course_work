
all: refsol clean

refsol: refsol.o sortingword.o wovelsymble.o quantityword.o quantitysent.o readcommand.o runcommand.o finalfile.o
	gcc refsol.o sortingword.o wovelsymble.o quantityword.o quantitysent.o readcommand.o runcommand.o finalfile.o -o refsol

refsol.o: refsol.c
	gcc -c refsol.c
	
sortingword.o: sortingword.c
	gcc -c sortingword.c

wovelsymble.o: wovelsymble.c
	gcc -c wovelsymble.c

quantityword.o: quantityword.c
	gcc -c quantityword.c

quantitysent.o: quantitysent.c
	gcc -c quantitysent.c

readcommand.o: readcommand.c
	gcc -c readcommand.c

runcommand.o: runcommand.c
	gcc -c runcommand.c

finalfile.o: finalfile.c
	gcc -c finalfile.c
	
clean:
	rm -rf *.o
