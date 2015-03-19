#include "concesionario.h"
#include <getopt.h>

int main(int argc, char *argv[])
{
	int val, i = 0, option_index = 0;
	char info[4000];
	struct coche *c1;
	struct concesionario *con;
	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm'},
		{ "id", required_argument, 0, 'i'},
		{"gama", required_argument, 0, 'g'},
		{"dueno", required_argument, 0, 'd'},
		{"help", required_argument, 0, 'h'},
		{ 0 }
	};
	c1 = curso_coche_alloc();
	con  = curso_concesionario_alloc();
	while(i<argc){
		i++;
		val = getopt_long(argc, argv, "m:i:g:d:h",
		       		long_options, &option_index);
		if (val == -1)
			return val;

		switch (val) {
		case 'm':
			curso_coche_attr_set_str(c1,
				       	CURSO_COCHE_ATTR_MATRICULA, (char *)argv);
			break;
		case 'i':
			curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID,
				       		(uint32_t)argv);
			break;
		case 'g':
			curso_coche_attr_set_str(c1,CURSO_COCHE_ATTR_MARCA,
						(char *)argv);
			break;
		case 'd':
			curso_concesionario_attr_set_str(con,
				       	CURSO_CONCESIONARIO_ATTR_DUENO,
				       	(char *)argv);
			curso_concesionario_attr_set_coche(con,
					CURSO_CONCESIONARIO_ATTR_COCHE,c1);
			break;
		case 'h':
		default:
			printf("Debe usar el parametro -m/-matricula,\
				       	-i/-id, -g/-gama, -d/dueno\n");
		}
	}
	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);
	return 0;
}
