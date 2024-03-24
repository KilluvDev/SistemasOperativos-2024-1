#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{

	DIR *folder, *check, *subfolder;
	FILE *archivo, *archivo_origen, *archivo_destino;
	struct dirent *directorio, *subdirectorio;
	char buffer[BUFFER_SIZE], alfaname, genname;
	int counter;
	size_t bytes_leidos;

	folder = opendir("./Sprites"); // Directorio a registrar
	if (folder == NULL)
	{
		printf("Error al abrir la carpeta");
		return 1;
	}

	// PAUSAO
	while ((directorio = readdir(folder)))
	{
		// printf("%c\n", directorio->d_name[0]);
		alfaname = directorio->d_name[0];
		archivo_origen = fopen(directorio->d_name, "rb");
		check = opendir(alfaname);
		if (check == NULL)
		{
			mkdir(alfaname, 0777);
			archivo_destino = fopen(directorio, "wb");
		}
		else
		{
			archivo_destino = fopen(directorio, "wb");
		}
		while ((bytes_leidos = fread(buffer, 1, BUFFER_SIZE, archivo_origen)) > 0)
		{
			fwrite(buffer, 1, bytes_leidos, archivo_destino);
		}
		fclose(archivo_origen);
		fclose(archivo_destino);
	}

	/*
	folder = opendir("./Generación");
	while ((directorio = readdir(folder)))
	{
	}
	*/

	// CONTADOR POR LETRA
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
	return 0;
}
