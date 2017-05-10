Main: Generate.cpp Generate_Fun.cpp Refsol.cpp Refsol_Fun.cpp Usersol.cpp
	gcc Generate.cpp Generate_Fun.cpp -o Generator
	gcc Refsol.cpp Refsol_Fun.cpp -o Refsol
	gcc Usersol.cpp Refsol_Fun.cpp -o Usersol
	rm Usersol.cpp
Usersol.cpp:
	touch Usersol.cpp
	cat  Refsol.cpp > Usersol.cpp





