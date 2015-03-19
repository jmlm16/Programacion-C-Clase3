#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	int linea = 0;
	int writes;

	while (linea < 6) {
		writes = fprintf(file, "Linea %d: Mensaje de prueba\n", linea);
		if (writes < 0)
			return;
		//comprobar fprintf no sea menor que 0
		linea++;
	}
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return -1;

	genera_mensaje(file);

	code = malloc(100);
	if (code == NULL)
		return -1;
	//comprobar malloc creando bien
	while(fgets(code, 100, file)) {
		//comprobar fgets (la linea del while en realidad lo comprueba)
		printf("%s", code);
	}

	free(code);
	if (fclose(file))
		return -1;
	//liberar fichero fclose y comprobamos
	return 0;
}
