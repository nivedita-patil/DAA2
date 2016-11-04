all: compile
compile:
	g++ DAA2.cpp
	./a.out
clean:
	rm a.out *.cpp~ *.h~
