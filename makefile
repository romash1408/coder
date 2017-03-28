all: build/coder.o build/command.o build/main.o
	gcc -o bin/main.exe build/coder.o build/command.o build/main.o

build/coder.o: src/coder.c
	gcc -c -o build/coder.o build/coder.o

build/command.o: src/command.c
	gcc -c -o build/command.o build/command.o

build/main.o: src/main.c
	gcc -c -o build/main.o build/main.o
	
debug: clean src/coder.c src/command.c src/main.c
	gcc -O0 -g3 -o bin/main.exe src/coder.c src/command.c src/main.c

clean:
	rm build/*