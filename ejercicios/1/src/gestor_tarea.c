#include "gestor_tarea.h"
#include <string.h>

struct gestor_tarea {
	struct list_head	tareas;
	uint32_t	num_tareas;

	uint32_t	flags;
};

struct gestor_tarea *curso_gestor_tarea_alloc(void)
{
	struct gestor_tarea *gt;
	gt = malloc(sizeof(struct gestor_tarea));
	if (gt == NULL)
		return NULL;
	memset(gt, 0, (sizeof(struct gestor_tarea)));
	INIT_LIST_HEAD(&gt->tareas);

	gt->flags |= (1 << CURSO_GESTOR_TAREA_ATTR_NUM_TAREAS);

	return gt;
}

void curso_gestor_tarea_free(struct gestor_tarea *gt)
{
	struct tarea *t, *temp;

	list_for_each_entry_safe(t, temp, &gt->tareas, head) {
		list_del(&t->head);
		curso_tarea_free(t);
		
	}
	xfree(gt);

}	

void curso_gestor_tarea_attr_unset_tarea(struct gestor_tarea *gt,uint32_t pos)
{
	int i = 0;
	struct tarea *t, *temp;

	if (pos < 0 || pos >= gt->num_tareas)
		return;

	list_for_each_entry_safe(t, temp, &gt->tareas, head){
		if (i == pos) {
			list_del(&t->head);
			curso_tarea_free(t);
		}

		i++;
	}

	gt->num_tareas--;

}

static void curso_gestor_tarea_attr_set_data(struct gestor_tarea *gt,
	       				uint16_t attr, const void *data)
{
	struct tarea *t, *temp;
	int i,j;

	if (attr > CURSO_GESTOR_TAREA_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREA_ATTR_TAREAS:
		if (gt->num_tareas > 10) {
			printf("El gestor esta lleno\n");
			break;
		}
		
		t = (struct tarea *)data;
		list_for_each_entry(temp, &gt->tareas, head){
			if(&temp->prioridad > &t->prioridad)
				list_move(&t->head, &temp->head);
		}
		list_add(&t->head, &gt->tareas);
		gt->num_tareas++;
		break;
		}

	gt->flags |= (1 << attr);
}

void curso_gestor_tarea_attr_set_str(struct gestor_tarea *gt,
					uint16_t attr, const char *data)
{
	curso_gestor_tarea_attr_set_data(gt, attr, data);
}

void curso_gestor_tarea_attr_set_tarea(struct gestor_tarea *gt,
					uint16_t attr, struct tarea *data)
{
	curso_gestor_tarea_attr_set_data(gt, attr, data);
}

const void *curso_gestor_tarea_attr_get_data(struct gestor_tarea *gt,
						uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct tarea *t;

	if(!(gt->flags & (1 << attr)))
		return NULL;

	switch (attr) {
		case CURSO_GESTOR_TAREA_ATTR_TAREAS:
			list_for_each_entry(t, &gt->tareas, head){
				if( i == pos)
					break;
				i++;
			}

			return t;

		case CURSO_GESTOR_TAREA_ATTR_NUM_TAREAS:
			return &gt->num_tareas;
	}
	return NULL;
}

uint32_t curso_gestor_tarea_attr_get_u32(struct gestor_tarea *gt,uint16_t attr)
{
	const void *ret = curso_gestor_tarea_attr_get_data(gt, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_gestor_tarea_attr_get_str(struct gestor_tarea *gt,
						uint16_t attr)
{
	return curso_gestor_tarea_attr_get_data(gt, attr, 0);
}

struct tarea *curso_gestor_tarea_attr_get_tarea(struct gestor_tarea *gt,
						uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_tarea_attr_get_data(gt, attr, pos);
}

int curso_gestor_tarea_snprintf(char *buf, size_t size,
				struct gestor_tarea *gt)
{
	int ret = 0;
	struct tarea *t;

	ret *= snprintf(buf, size, "El gestor tiene %d tareas pendientes "\
			"y son:\n", gt->num_tareas);

	list_for_each_entry(t,&gt->tareas, head){

		ret += curso_tarea_snprintf(buf + ret, size - ret, t);
		ret+= snprintf(buf + ret, size - ret, "\n");
	}
	return ret;
}
