#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> 

void crearDirectoriosAnidados(char *ruta, int profundidad) {
    if (profundidad == 0) return;
    for (char letra = 'A'; letra <= 'Z'; letra++) {
        char nuevoDirectorio[256];
        sprintf(nuevoDirectorio, "%s/%c", ruta, letra);
        if (mkdir(nuevoDirectorio, 0777) == 0) {
            crearDirectoriosAnidados(nuevoDirectorio, profundidad - 1);
        }
    }
}


int main(int argc, char *argv[])
{

	DIR *folder, *check;
	FILE *archivoOrigen, *archivoDestino;
	char buffer[1024];
    size_t bytesLeidos;
	struct dirent *directorio;

	mkdir("./Generación",0777);
	mkdir("./Generación/I",0777);
	mkdir("./Generación/II",0777);
	mkdir("./Generación/III",0777);
	mkdir("./Generación/IV",0777);
	mkdir("./Alfabético",0777);

	char rutaInicial[] = "./Alfabético/"; // Comienza en el directorio actual
    int profundidad = 1; // Profundidad de anidación
    crearDirectoriosAnidados(rutaInicial, profundidad);

	folder = opendir("./Sprites"); // Directorio a registrar
	if (folder == NULL)
	{
		printf("Error al abrir la carpeta");
		return 1;
	}

	while((directorio = readdir(folder))){
		printf("%s\n", directorio->d_name);
	}
	closedir(folder);



	return 0;
}





// gcc -o out Pokemon.c
// ./out
