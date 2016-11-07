all: compile
compile:
	g++ DAA2.cpp
	./a.out > output.txt
clean:
	rm a.out *.cpp~ *.h~
