#include "treap.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"

enum dir {
	LEFT,
	RIGHT,
};

struct treap_t {
	struct treap_t *children[2];
	struct treap_t *parent;
	size_t priority;
	int val;
};

static struct treap_t *treap_create(void) {
	return NULL;
}

static struct treap_t *treap_search(struct treap_t *t, int val) {
	while (t) {
		if (t->val == val) break;
		t = t->children[val > t->val];
	}
	return t;
}

static void treap_rotate(struct treap_t **t, enum dir d) {
}

static void treap_insert(struct treap_t **t, int val) {
	struct treap_t **c = t;
	struct treap_t *p = NULL;
	while (*c) {
		p = *c;
		c = &(*c)->children[val > (*c)->val];
	}
	*c = malloc(sizeof **c);
	**c = (struct treap_t){ .val = val, .priority = random(), .parent = p };
	while ((*c)->parent && (*c)->parent->priority > (*c)->priority) {
		// rotate towards parent
		c = &(*c)->parent;
	}
	if (!(*c)->parent) *t = *c;
}

static void treap_remove(struct treap_t **t, int val) {
	// sift down
	// delete when it is a leaf
}

static void treap_pprint(struct treap_t *t) {
	// in order traversal
}

static void treap_unmake(struct treap_t **t) {
}

// wrappers
static void *treap_create_vt(void) {
	return treap_create();
}
static void treap_insert_vt(void **list, int val) {
	treap_insert((struct treap_t **)list, val);
}
static void *treap_search_vt(void *list, int val) {
	return treap_search((struct treap_t *)list, val);
}
static void treap_remove_vt(void **list, int val) {
	treap_remove((struct treap_t **)list, val);
}
static void treap_pprint_vt(void *list) {
	treap_pprint((struct treap_t *)list);
}
static void treap_unmake_vt(void **list) {
	treap_unmake((struct treap_t **)list);
}
struct list_vt treap_vt = {
	.create = treap_create_vt,
	.insert = treap_insert_vt,
	.search = treap_search_vt,
	.remove = treap_remove_vt,
	.pprint = treap_pprint_vt,
	.unmake = treap_unmake_vt,
};
