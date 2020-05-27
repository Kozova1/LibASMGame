CXX:=g++

test:
	$(CXX) cpu.cpp test.cpp -std=c++17 -Wall -Wpedantic -Werror -o tester
	./tester

asm:
	cp ./testasm.asm ../assembler/testasm.asm
	cd ../assembler
	make test
	cd ../vm

debug:
	$(CXX) cpu.cpp test.cpp -std=c++17 -g -Wall -Wpedantic -Werror -o tester
	gdb -tui ./tester
