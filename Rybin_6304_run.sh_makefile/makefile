Main: Generate Refsol Usersol.cpp
#	gcc Usersol.cpp Refsol_Fun.cpp -o Usersol
	gcc Usersol.cpp -o Usersol
	rm Usersol.cpp
Generate: Generate.cpp Generate_Fun.cpp Generate_Header.h
	gcc Generate.cpp Generate_Fun.cpp -o Generator
Refsol: Refsol.cpp Refsol_Fun.cpp Refsol_Header.h Generate_Header.h
	gcc Refsol.cpp Refsol_Fun.cpp -o Refsol
#Usersol.cpp:
#	touch Usersol.cpp
#	cat  Refsol.cpp > Usersol.cpp





