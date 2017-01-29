OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Wno-uninitialized -Wno-sign-compare -std=c++0x

program.exe: program.o ArbIOparint.o
	g++ -o program.exe program.o ArbIOparint.o
	rm *.o

program.o: program.cc PRO2Excepcio.hh ArbIOparint.hh
	g++ -c program.cc $(OPCIONS)

ArbIOparint.o: ArbIOparint.cc PRO2Excepcio.hh Arbre.hh ArbIOparint.hh
	g++ -c ArbIOparint.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe
	rm *.gch
