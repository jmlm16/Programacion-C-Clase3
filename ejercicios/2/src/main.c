#include "../includes/concesionario.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
	int val, i,cont = 0, option_index = 0;
	char info[4000];
	char *argumento;
	struct coche *c1;
	struct concesionario *con;
	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm'},
		{ "id", required_argument, 0, 'i'},
		{"gama", required_argument, 0, 'g'},
		{"dueno", required_argument, 0, 'd'},
		{"help", optional_argument, 0, 'h'},
		{ 0 }
	};
	c1 = curso_coche_alloc();
	con  = curso_concesionario_alloc();
	while(1){
		
		val = getopt_long(argc, argv, "m:i:g:d:h:",
		       		long_options, &option_index);
		if (val == -1)
		{
			if(cont<4){
			printf("val negativo\n");
			}
			break;
		}
		cont++;
		switch (val) {
		case 'm':
			argumento = optarg;
			printf("Matricula: %s\n",argumento);
			curso_coche_attr_set_str(c1,
				       	CURSO_COCHE_ATTR_MATRICULA, argumento);
			break;
		case 'i':
			i = atoi(optarg);
			printf("Id: %d\n",i);
			curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID,i);
			break;
		case 'g':
			argumento = optarg;
			printf("Gama: %s\n",argumento);
			curso_coche_attr_set_str(c1,CURSO_COCHE_ATTR_MARCA,
						argumento);
			break;
		case 'd':
			argumento = optarg;
			printf("Dueño: %s\n",argumento);
			curso_concesionario_attr_set_str(con,
				       	CURSO_CONCESIONARIO_ATTR_DUENO,
				       	argumento);
			break;
		case 'h':
		default:
			printf("Debe usar el parametro -m/-matricula,"\
				       	"-i/-id, -g/-gama, -d/dueno\n");
			break;
		}
	}
	if(cont <4){
		printf("Faltan valores\n");
		return -1;
	}
	curso_concesionario_attr_set_coche(con,
					CURSO_CONCESIONARIO_ATTR_COCHE,c1);

	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);
	return 0;
}
