OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o Estudiant.o ArbIOest.o
	g++ -o program.exe program.o Estudiant.o ArbIOest.o
	rm *.o

program.o: program.cc PRO2Excepcio.hh Arbre.hh ArbIOest.hh
	g++ -c program.cc $(OPCIONS)

ArbIOest.o: ArbIOest.cc PRO2Excepcio.hh Estudiant.hh
	g++ -c ArbIOest.cc $(OPCIONS)

Estudiant.o: Estudiant.cc PRO2Excepcio.hh Estudiant.hh
	g++ -c Estudiant.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
