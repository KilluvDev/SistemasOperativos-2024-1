#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void Organizacion(){
	mkdir("./Generación",0777);
	mkdir("./Generación/I",0777);
	mkdir("./Generación/II",0777);
	mkdir("./Generación/III",0777);
	mkdir("./Generación/IV",0777);
	
	char dirName[2]="A";
	for(int i=0;i<26;i++){
		mkdir(dirName)
	}

}


int main(int argc, char *argv[])
{

	DIR *folder, *check;
	FILE *archivo,*copia;
	struct dirent *directorio;
	Organizacion();
	folder = opendir("./Sprites"); // Directorio a registrar
	if (folder == NULL)
	{
		printf("Error al abrir la carpeta");
		return 1;
	}
	return 0;
}






	/*
	folder = opendir("./Generación");
	while ((directorio = readdir(folder)))
	{
	}
	*/

	// CONTADOR POR LETRA
    /*
	archivo = fopen("RegistroPokemon.txt", "w");
	folder = opendir("./Alfabetico");
	while ((directorio = readdir(folder)))
	{
		counter = 0;
		subfolder = opendir(directorio->d_name);
		while ((subdirectorio = readdir(subfolder)))
		{
			counter++;
		}
		fputs(("%c - %d\n", directorio->d_name, counter), "RegistroPokemon.txt");
	}
	fclose(archivo);
    */



// gcc -o out Pokemon.c
// ./out
