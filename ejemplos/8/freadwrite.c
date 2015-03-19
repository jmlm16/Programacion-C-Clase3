#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char c[] = "ejemplo fwrite/fread";
	char buffer[20];
	int leidos,escritos;

	fp = fopen("datos.dat", "w+");
	if (fp == NULL)
		return -1;

	escritos = fwrite(c, strlen(c) + 1, 1, fp);
	if(escritos < 0)
		return -1;
	rewind(fp);
	//CONTROL DE ESCRITURAS Y LECTURAS!!!
	//comprobar que caracteres leidos y escritos son iguales al tamaño de char.
	leidos = fread(buffer, strlen(c) + 1, 1, fp);
	if(leidos < 0)
		return -1;
	if (leidos != escritos)
		return -1;
	printf("%s\n", buffer);

	if(fclose(fp))
		return -1;
	return 0;
}
