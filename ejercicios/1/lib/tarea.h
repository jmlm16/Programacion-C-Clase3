#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

enum {
	CURSO_TAREA_ATTR_NOMBRE_TAREA = 0,
	CURSO_TAREA_ATTR_DESC_TAREA,
	CURSO_TAREA_ATTR_ID,
	CURSO_TAREA_ATTR_USUARIO,
	CURSO_TAREA_ATTR_PRIORIDAD,
	__CURSO_TAREA_ATTR_MAX
};

#define CURSO_TAREA_ATTR_MAX (__CURSO_TAREA_ATTR_MAX - 1)

#define xfree(ptr)	free((void *)ptr);

struct tarea {
	struct list_head	head;
	const char		*nombre_tarea;
	const char		*desc_tarea;
	uint32_t		id;
	const char		*usuario;
	uint32_t		prioridad;

	uint32_t		flags;
};

struct tarea *curso_tarea_alloc(void);
void curso_tarea_free(struct tarea *);

bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr);

void cruso_tarea_attr_unset(struct tarea *t, uint16_t attr);

void curso_tarea_attr_set_data(struct tarea *t, uint16_t attr,
	       			const void *data, uint32_t data_len);

void curso_tarea_attr_set_u32(struct tarea *t, uint16_t attr, uint32_t data);
void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr,
				const char *data);

const void *curso_tarea_attr_get_data(struct tarea *t, uint16_t attr);
uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr);
const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr);

int curso_tarea_snprintf(char *buf, size_t size, struct tarea *t);
