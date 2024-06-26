#include "array.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

struct array_t {
	size_t cap;
	size_t len;
	int buf[];
};

static struct array_t *array_create(void) {
	struct array_t *new = malloc(sizeof *new + 8 * sizeof *new->buf);
	new->cap = 8;
	new->len = 0;
	return new;
}

static int *array_search(struct array_t *arr, int val) {
	int *s = arr->buf;
	int *e = arr->buf + arr->len;
	while (s < e) {
		int *m = s + (e-s)/2;
		if (*m < val) {
			s = m + 1;
		} else {
			e = m;
		}
	}
	return s;
}

static void array_insert(struct array_t **arr, int val) {
	if ((*arr)->len == (*arr)->cap) {
		(*arr)->cap += (*arr)->cap / 2;
		*arr = realloc(*arr, sizeof **arr + (*arr)->cap * sizeof *(*arr)->buf);
	}
	int *s = array_search(*arr, val);
	(*arr)->len++;
	int *e = (*arr)->buf + (*arr)->len;
	for (int *c = e-1; c > s; --c) {
		*c = *(c-1);
	}
	*s = val;
}

static void array_remove(struct array_t **arr, int val) {
	int *c = array_search(*arr, val);
	if (*c != val) return;
	(*arr)->len--;
	int *e = (*arr)->buf + (*arr)->len;
	for (; c < e; ++c) {
		*c = *(c+1);
	}
}

static void array_pprint(struct array_t *arr) {
	int *s = arr->buf;
	int *e = arr->buf + arr->len;
	fprintf(stdout, "[");
	for (int *c = s; c < e; ++c) {
		fprintf(stdout, (c == s) ? "%d" : ", %d", *c);
	}
	fprintf(stdout, "]\n");
}

static void array_unmake(struct array_t **arr) {
	free(*arr);
	*arr = NULL;
}

// wrappers
static void *array_create_vt(void) {
	return array_create();
}
static void array_insert_vt(void **list, int val) {
	array_insert((struct array_t **)list, val);
}
static void *array_search_vt(void *list, int val) {
	return array_search((struct array_t *)list, val);
}
static void array_remove_vt(void **list, int val) {
	array_remove((struct array_t **)list, val);
}
static void array_pprint_vt(void *list) {
	array_pprint((struct array_t *)list);
}
static void array_unmake_vt(void **list) {
	array_unmake((struct array_t **)list);
}
struct list_vt array_vt = {
	.create = array_create_vt,
	.insert = array_insert_vt,
	.search = array_search_vt,
	.remove = array_remove_vt,
	.pprint = array_pprint_vt,
	.unmake = array_unmake_vt,
};
