#include "slist.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

#define LEFT 0
#define RIGHT 1

struct slist_t {
	size_t height;
	struct node_t **layer;
};

struct node_t {
	struct slist_t next;
	int val;
};

static struct slist_t *slist_create(void) {
	struct slist_t *n = malloc(sizeof *n);
	n->height = 1;
	n->layer = malloc(sizeof *n->layer);
	n->layer[0] = NULL;
	return n;
}

static struct slist_t *slist_search(struct slist_t *list, int val) {
	size_t h = list->height - 1;
	struct slist_t *c = list;
	while (1) {
		struct node_t *n = c->layer[h];
		// try to go right
			// if right is equal return
			// if right is less advance and continue
		if (n && n->val <= val) {
			c = &n->next;
			if (n->val == val) break;
			if (n->val < val) continue;
		}
		// try to go down and if we can't break
		if (h == 0) break;
		h -= 1;
	}
	return c;
}

// logic is quite similar to searching, since traversal is the same
// however we have to inline modification through the traversal loop,
// so it seems difficult to re-use the code
static void slist_insert(struct slist_t **list, int val) {
	size_t height = 1;
	// HACK Is random() bad? I neither know nor care atm
	// What is random() vs rand()
	while (random()&1) height++;
	if (height > (*list)->height) {
		(*list)->layer = realloc((*list)->layer, height * sizeof (*list)->layer);
		for (size_t i = (*list)->height; i < height; ++i) {
			(*list)->layer[i] = NULL;
		}
		(*list)->height = height;
	}
	struct node_t *new = malloc(sizeof *new);
	new->val = val;
	new->next.height = height;
	new->next.layer = malloc(height * sizeof *new->next.layer);

	size_t h = (*list)->height - 1;
	struct slist_t *c = *list;
	while (1) {
		struct node_t *n = c->layer[h];
		if (n && n->val <= val) {
			c = &n->next;
			continue;
		}
		if (h < height) {
			// insert into list
			c->layer[h] = new;
			new->next.layer[h] = n;
		}
		if (h == 0) break;
		h -= 1;
	}
}

static void slist_remove(struct slist_t **list, int val) {
	struct node_t *f = NULL;

	struct slist_t *c = *list;
	size_t h = (*list)->height - 1;

	while (1) {
		struct node_t *n = c->layer[h];
		if (n && n->val < val) {
			c = &n->next;
			continue;
		}
		if (n && ((!f && n->val == val) || f == n)) {
			f = n;
			c->layer[h] = n->next.layer[h];
		}
		if (h == 0) break;
		h -= 1;
	}
}

static void slist_pprint(struct slist_t *list) {
	// TODO align nodes
	for (size_t i = 0; i < list->height; ++i) {
		printf("%zu:", i);
		struct slist_t *c = list;
		while (c->layer[i]) {
			printf((c == list) ? "%d" : "->%d", c->layer[i]->val);
			c = &c->layer[i]->next;
		}
		printf("\n");
	}
	printf("\n");
}

static void slist_unmake(struct slist_t **list) {
	struct slist_t *c = *list;
	while (c->layer[0]) {
		struct slist_t *n = &c->layer[0]->next;
		free(c->layer);
		free(c);
		c = n;
	}
}

// wrappers
static void *slist_create_vt(void) {
	return slist_create();
}
static void slist_insert_vt(void **list, int val) {
	slist_insert((struct slist_t **)list, val);
}
static void *slist_search_vt(void *list, int val) {
	return slist_search((struct slist_t *)list, val);
}
static void slist_remove_vt(void **list, int val) {
	slist_remove((struct slist_t **)list, val);
}
static void slist_pprint_vt(void *list) {
	slist_pprint((struct slist_t *)list);
}
static void slist_unmake_vt(void **list) {
	slist_unmake((struct slist_t **)list);
}
struct list_vt slist_vt = {
	.create = slist_create_vt,
	.insert = slist_insert_vt,
	.search = slist_search_vt,
	.remove = slist_remove_vt,
	.pprint = slist_pprint_vt,
	.unmake = slist_unmake_vt,
};
