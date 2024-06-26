#include "llist.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

struct llist_t {
	struct llist_t *prev;
	struct llist_t *next;
	int val;
};

static struct llist_t *llist_create(void) {
	return NULL;
}

static struct llist_t *llist_search(struct llist_t *list, int val) {
	while (list && list->next && list->val < val) {
		list = list->next;
	}
	return list;
}

static void llist_insert(struct llist_t **list, int val) {
	struct llist_t *c = llist_search(*list, val);
	struct llist_t *n = malloc(sizeof *n);
	n->val = val;
	n->prev = c;
	n->next = c ? c->next : NULL;
	if (c) {
		c->next = n;
		if (c->next) c->next->prev = n;
	} else {
		*list = n;
	}
}

static void llist_remove(struct llist_t **list, int val) {
	struct llist_t *c = llist_search(*list, val);
	if (c->val != val) return;
	if (c->prev) {
		c->prev->next = c->next;
	} else {
		*list = c->next;
	}
	if (c->next) c->next->prev = c->prev;
}

static void llist_pprint(struct llist_t *list) {
	int first = 1;
	while (list) {
		printf(first ? "%d" : "->%d", list->val);
		list = list->next;
		first = 0;
	}
	printf("\n");
}

static void llist_unmake(struct llist_t **list) {
	while (*list) {
		struct llist_t *n = (*list)->next;
		free(*list);
		*list = n;
	}
}

// wrappers
static void *llist_create_vt(void) {
	return llist_create();
}
static void llist_insert_vt(void **list, int val) {
	llist_insert((struct llist_t **)list, val);
}
static void *llist_search_vt(void *list, int val) {
	return llist_search((struct llist_t *)list, val);
}
static void llist_remove_vt(void **list, int val) {
	llist_remove((struct llist_t **)list, val);
}
static void llist_pprint_vt(void *list) {
	llist_pprint((struct llist_t *)list);
}
static void llist_unmake_vt(void **list) {
	llist_unmake((struct llist_t **)list);
}
struct list_vt llist_vt = {
	.create = llist_create_vt,
	.insert = llist_insert_vt,
	.search = llist_search_vt,
	.remove = llist_remove_vt,
	.pprint = llist_pprint_vt,
	.unmake = llist_unmake_vt,
};
