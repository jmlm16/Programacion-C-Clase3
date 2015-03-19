#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	fputs("El mensaje a escribir es Alvaro", file);
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+");
	//comprobar apertura del archivo
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return -1;

	genera_mensaje(file);

	code = malloc(101);
	if(code == NULL)
		return -1;
	//comprobar malloc no devuelve null
	while(fgets(code, 101, file)) {
		printf("%s\n", code);
	}

	free(code);
	if(fclose(file))
		return -1;
	//comprobar liberacion de fclose
	return 0;
}
