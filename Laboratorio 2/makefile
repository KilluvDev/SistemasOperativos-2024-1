main: run

bin:
	mkdir ./bin

bin/WrestleMania: bin bin/main.o bin/parent.o bin/children.o
	gcc ./bin/main.o ./bin/parent.o ./bin/children.o -o ./bin/WrestleMania -Wall

bin/main.o: bin src/main.c src/types.h src/parent.h src/children.h src/settings.h
	gcc -c ./src/main.c -o ./bin/main.o -Wall

bin/parent.o: bin src/parent.c src/parent.h src/types.h src/settings.h
	gcc -c ./src/parent.c -o ./bin/parent.o -Wall

bin/children.o: bin src/children.c src/children.h src/types.h src/settings.h
	gcc -c ./src/children.c -o ./bin/children.o -Wall

.PHONY: clear run

clear: bin
	rm -rf ./bin

run: bin/WrestleMania
	./bin/WrestleMania
