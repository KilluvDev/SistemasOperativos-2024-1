main: run

bin:
	mkdir ./bin

bin/WrestleMania: bin src/main.c src/types.h
	gcc -o ./bin/WrestleMania ./src/main.c -Wall

.PHONY: clear run

clear:
	rm -rf ./bin

run: bin/WrestleMania
	./bin/WrestleMania
