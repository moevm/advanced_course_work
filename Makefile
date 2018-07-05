all: sol gen

sol: gen.c
	gcc gen.c -o Gen

gen: sol.c
	gcc sol.c -o Sol