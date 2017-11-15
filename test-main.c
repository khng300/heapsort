#include "heapsort.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define offset_of(type, field) ((size_t)(&((type *)0)->field))
#define node_of(ptr, type, field) ((type *)((char *)(ptr) - offset_of(type, field)))

#define COUNT 200

static int my_cmp(TYPE_T a, TYPE_T b) {
	if (a < b)
		return -1;
	if (a > b)
		return 1;
	return 0;
}

int
main()
{
	int i;
	TYPE_T *nodes = malloc(sizeof(TYPE_T) * COUNT);

	for (i = 0; i < COUNT; i++) {
		nodes[i] = rand();
		printf(" %lu ", nodes[i]);
	}
	
	printf("\n");
	printf("\n");
	
	heapsort_s(nodes, COUNT, my_cmp);
	for (i = 0; i < COUNT; i++) {
		printf(" %lu ", nodes[i]);
	}
	
	free(nodes);
	return 0;
}
