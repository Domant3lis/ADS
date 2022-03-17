#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

char *STR;
#define INT_TO_STR(c)\
	STR = calloc(3, sizeof(char));\
	sprintf(STR, "%zu", c);\

int main()
{
	HashTable *hashTable = HT_create(96);

	HT_put(hashTable, -1, (void *) strdup("LOL"));

	for (size_t i = 0; i < 64; ++i)
	{
		INT_TO_STR(i);
		HT_put(hashTable, i, (void *) STR);
	}

	for (size_t i = 0; i < 64; ++i)
		puts(HT_get(hashTable, i));

	puts( (char *) HT_get(hashTable, -1));
	free(HT_remove(hashTable, -1));
	
	printf("%s\n", (char *) HT_get(hashTable, -1));

	HT_free_with_objects(&hashTable, NULL);

	return 0;
}
