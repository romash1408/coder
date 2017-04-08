CC := gcc
CDBG := -O0 -g3
CFLAGS := -Wall -Werror
SRC = $(patsubst src/%.c,%,$(wildcard src/*.c))
APP_NAME = bin/main.exe
DIRS = bin build debug

all: $(addprefix folder-,$(DIRS)) build
allDebug: $(addprefix folder-,$(DIRS)) debug

build: $(addprefix build/,$(addsuffix .o,$(SRC)))
	$(CC) -o $(APP_NAME) $^

debug: $(addprefix debug/,$(addsuffix .o,$(SRC)))
	$(CC) -o $(APP_NAME) $^

folder-%:
	mkdir -p $(subst -,/,$(patsubst folder-%,%,$@))

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

debug/%.o: src/%.c
	$(CC) $(CFLAGS) $(CDBG) -c -o $@ $<

clean:
	rm -rdf $(DIRS)