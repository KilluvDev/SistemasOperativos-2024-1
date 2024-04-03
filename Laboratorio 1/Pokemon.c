#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void Registro()
{
	/*
	Función Registro.
	tipo void.
	*****
	Parámetros:
	sin parámetros.
	*****
	La función genera el archivo de texto que contiene la información de el contenido de los directorios
	Crea y cierra el archivo, y revisa directorios uno a uno para contabilizar.
	*****
	Sin retorno.
	*/
	char letra, path[256];
	struct dirent *directorio;
	FILE *archivo;
	DIR *folder;
	int c;

	archivo = fopen("RegistroPokemon.txt", "w");
	fprintf(archivo, "Generación\n");
	sprintf(path, "./Generación/I");
	c = 0;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
		{
			c++;
		}
	}
	fprintf(archivo, "I - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/II");
	c = 0;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
		{
			c++;
		}
	}
	fprintf(archivo, "II - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/III");
	c = 0;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
		{
			c++;
		}
	}
	fprintf(archivo, "III - %d\n", c);
	closedir(folder);

	sprintf(path, "./Generación/IV");
	c = 0;
	folder = opendir(path);
	while ((directorio = readdir(folder)))
	{
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
		{
			c++;
		}
	}
	fprintf(archivo, "IV - %d\n", c);
	closedir(folder);

	fprintf(archivo, "Alfabético\n");
	for (letra = 'A'; letra <= 'Z'; letra++)
	{
		c = 0;

		sprintf(path, "./Alfabético/%c", letra);
		folder = opendir(path);
		while ((directorio = readdir(folder)))
		{
			if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
			{
				c++;
			}
		}
		closedir(folder);
		fprintf(archivo, "%c - %d\n", letra, c);
	}
	fclose(archivo);
}

void crearDirectorios()
{
	/*
	Función crearDirectorios.
	tipo void.
	*****
	Parámetros:
	sin parámetros
	*****
	La función crea los directorios
	*****
	Sin retorno
	*/
	char *ruta = "./Alfabético";
	mkdir(ruta, 0777);
	for (char letra = 'A'; letra <= 'Z'; letra++)
	{
		char nuevoDirectorio[256];
		sprintf(nuevoDirectorio, "%s/%c", ruta, letra);
		mkdir(nuevoDirectorio, 0777);
	}
	mkdir("./Generación", 0777);
	mkdir("./Generación/I", 0777);
	mkdir("./Generación/II", 0777);
	mkdir("./Generación/III", 0777);
	mkdir("./Generación/IV", 0777);
}

int main(int argc, char *argv[])
{
	/*
	Función main.
	tipo int.
	*****

	*****
	Dentro de la función main, se gestionan los archivos desde la carpeta Sprites
	Se llama a funciones de generado de directorios para distribuir en la ruta correspondiente
	cada archivo que se encuentre en la carpeta inicial.
	Se generan copias de los archivos en los subdirectorios de la carpeta Alfabético y en los de
	la carpeta Generación, los cuales al copiarse en el directorio Generación, se eliminan de la carpeta inicial
	Finalmente se llama a la función de Registro.
	*****
	Retorna 0.
	*/
	DIR *folder;
	struct dirent *directorio;
	char letter[3], destino[256], comando[2048], origen[1024];
	char rutaInicial[] = "./Alfabético/";
	crearDirectorios();

	folder = opendir("./Sprites");
	while ((directorio = readdir(folder)))
	{
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
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
	}
	closedir(folder);

	folder = opendir("./Sprites");
	int number, maxnum;
	while ((directorio = readdir(folder)))
	{
		number = 0;
		if (strcmp(directorio->d_name, ".") != 0 && strcmp(directorio->d_name, "..") != 0)
		{

			for (int i = 0; i < strlen(directorio->d_name); i++)
			{
				if (isdigit(directorio->d_name[i]))
				{
					maxnum = atoi(&directorio->d_name[i]);
				}
				if (number < maxnum)
				{
					number = maxnum;
				}
			}
			sprintf(origen, "./Sprites/%s", directorio->d_name);
			if (number >= 1 && number <= 151)
			{
				sprintf(comando, "cp %s ./Generación/I/%s", origen, directorio->d_name);
				system(comando);
				sprintf(comando, "rm ./Sprites/%s", directorio->d_name);
				system(comando);
			}
			else if (number > 151 && number <= 251)
			{
				sprintf(comando, "cp %s ./Generación/II/%s", origen, directorio->d_name);
				system(comando);
				sprintf(comando, "rm ./Sprites/%s", directorio->d_name);
				system(comando);
			}
			else if (number > 251 && number <= 386)
			{
				sprintf(comando, "cp %s ./Generación/III/%s", origen, directorio->d_name);
				system(comando);
				sprintf(comando, "rm ./Sprites/%s", directorio->d_name);
				system(comando);
			}
			else if (number > 386 && number <= 493)
			{
				sprintf(comando, "cp %s ./Generación/IV/%s", origen, directorio->d_name);
				system(comando);
				sprintf(comando, "rm ./Sprites/%s", directorio->d_name);
				system(comando);
			}
		}
	}
	closedir(folder);
	Registro();
	return 0;
}
