Generate: struct.h generate.o wBitmap.o
	gcc generate.o -o generate.out wBitmap.o
	rm *.o
generate.o: generate.c struct.h
	gcc -c generate.c
wBitmap.o: wBitmap.c wBitmap.h struct.h
	gcc -c wBitmap.c
