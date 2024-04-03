a.out: Pokemon.c
	gcc Pokemon.c

Sprites: Sprites.zip
	unzip -q Sprites.zip -d .
	rm -rf "__MACOSX"

.PHONY: run clean

run: clean Sprites a.out
	./a.out

clean:
	rm a.out || true
	rm RegistroPokemon.txt || true
	rm -rf "__MACOSX"
	rm -rf "Alfabético"
	rm -rf "Generación"
	rm -rf "Sprites"
