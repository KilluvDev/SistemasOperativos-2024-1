#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void Registro()
{
	char letra, path[256];
	struct dirent *directorio;
	FILE *archivo;
	DIR *folder;
	int c;

	archivo = fopen("RegistroPokemon.txt", "w");
	fprintf(archivo, "Generación\n");
	sprintf(path, "./Generación/I");
	c = -2;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		c++;
	}
	fprintf(archivo, "I - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/II");
	c = -2;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		c++;
	}
	fprintf(archivo, "II - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/III");
	c = -2;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		c++;
	}
	fprintf(archivo, "III - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/IV");
	c = -2;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		c++;
	}
	fprintf(archivo, "IV - %d\n", c);
	closedir(folder);

	fprintf(archivo, "Alfabético\n");
	for (letra = 'A'; letra <= 'Z'; letra++)
	{
		c = -2;
		sprintf(path, "./Alfabético/%c", letra);
		folder = opendir(path);
		while ((directorio = readdir(folder)))
		{
			c++;
		}
		closedir(folder);
		fprintf(archivo, "%c - %d\n", letra, c);
	}
	fclose(archivo);
}

void crearDirectoriosAnidados(char *ruta, int profundidad)
{
	if (profundidad == 0)
		return;
	mkdir("./Alfabético", 0777);
	for (char letra = 'A'; letra <= 'Z'; letra++)
	{
		char nuevoDirectorio[256];
		sprintf(nuevoDirectorio, "%s/%c", ruta, letra);
		if (mkdir(nuevoDirectorio, 0777) == 0)
		{
			crearDirectoriosAnidados(nuevoDirectorio, profundidad - 1);
		}
	}
	mkdir("./Generación", 0777);
	mkdir("./Generación/I", 0777);
	mkdir("./Generación/II", 0777);
	mkdir("./Generación/III", 0777);
	mkdir("./Generación/IV", 0777);
	
}

int main(int argc, char *argv[])
{
	DIR *folder;
	struct dirent *directorio;
	char letter[3], destino[256], comando[2048], origen[1024];
	char rutaInicial[] = "./Alfabético/";
	int profundidad = 1;
	crearDirectoriosAnidados(rutaInicial, profundidad);

	folder = opendir("./Sprites");
	while ((directorio = readdir(folder)))
	{
		strcpy(destino, rutaInicial);
		letter[0] = directorio->d_name[0] - 32;
		letter[1] = '/';
		letter[2] = '\0';
		strcat(destino, letter);
		strcat(destino, directorio->d_name);
		sprintf(origen, "./Sprites/%s", directorio->d_name);
		sprintf(comando, "cp %s %s", origen, destino);
		system(comando);
	}
	closedir(folder);

	folder = opendir("./Sprites");
	int number;
	while ((directorio = readdir(folder)))
	{
		for (int i = 0; i < strlen(directorio->d_name); i++)
		{
			if (isdigit(directorio->d_name[i]))
			{
				number = atoi(&directorio->d_name[i]);
				break;
			}
		}
		sprintf(origen, "./Sprites/%s", directorio->d_name);
		if (number >= 1 && number <= 151)
		{
			sprintf(comando, "cp %s ./Generación/I/%s", origen, directorio->d_name);
			system(comando);
		}
		else if (number > 151 && number <= 251)
		{
			sprintf(comando, "cp %s ./Generación/II/%s", origen, directorio->d_name);
			system(comando);
		}
		else if (number > 251 && number <= 386)
		{
			sprintf(comando, "cp %s ./Generación/III/%s", origen, directorio->d_name);
			system(comando);
		}
		else if (number > 386 && number <= 493)
		{
			sprintf(comando, "cp %s ./Generación/IV/%s", origen, directorio->d_name);
			system(comando);
		}
	}
	closedir(folder);
	Registro();
	return 0;
}
