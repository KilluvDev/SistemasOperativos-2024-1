main: run

bin:
	mkdir ./bin

bin/WrestleMania: bin src/main.c
	gcc -o ./bin/WrestleMania ./src/main.c

.PHONY: clear run

clear:
	rm -rf ./bin

run: bin/WrestleMania
	./bin/WrestleMania
