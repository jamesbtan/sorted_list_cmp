#include "main.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array.h"
#include "llist.h"
#include "treap.h"
#include "slist.h"

#define COUNT 10000

#define NDEBUG
#ifndef NDEBUG
#define PPRINT(l) L[i].pprint(l)
#else
#define PPRINT(l)
#endif

int main(void) {
	srandom(time(NULL));

	struct list_vt L[] = {
		array_vt,
		llist_vt,
		treap_vt,
		slist_vt,
		// TODO RB-Tree
		// TODO AVL-Tree
		// TODO B-Tree
	};
	char const *names[] = {
		"array",
		"llist",
		"treap",
		"slist",
	};

	for (size_t i = 0; i < sizeof L / sizeof *L; ++i) {
		printf("%s\t", names[i]);
		void *list = L[i].create();
		PPRINT(list);

		clock_t start, end;
		(void)start; (void)end;

		start = clock();
		for (int j = 0; j < COUNT; ++j) {
			L[i].insert(&list, j);
			PPRINT(list);
		}
		end = clock();
		printf("%.2f\t", (double)(end - start)/CLOCKS_PER_SEC * 1000000);

		start = clock();
		for (int j = 0; j < COUNT; ++j) {
			L[i].search(list, j);
			PPRINT(list);
		}
		end = clock();
		printf("%.2f\t", (double)(end - start)/CLOCKS_PER_SEC * 1000000);

		start = clock();
		for (int j = 0; j < COUNT; ++j) {
			L[i].remove(&list, j);
			PPRINT(list);
		}
		end = clock();
		printf("%.2f", (double)(end - start)/CLOCKS_PER_SEC * 1000000);

		L[i].unmake(&list);
		printf("\n");
	}
}
