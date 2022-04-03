#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sort.h"

int main(int argc, char **argv)
{
	printf("--- Sorting ---");
	
	FILE *file = fopen(argv[1], "r");
	
	size_t size = 8192;
	int *arr = calloc(size, sizeof(int));
	int temp;
	
	size_t ix = 0;
	while(fscanf(file, "%d\n", &temp) != EOF)
	{
		// printf("%d\n", temp);
		arr[ix] = temp;
		++ix;
	}
  
	sort(arr, size);
	
	FILE *results = fopen("output.txt", "w");
	for (size_t ix = 0; ix < size; ++ix)
		fprintf(results, "%d\n", arr[ix]);
	
	fclose(file);
	fclose(results);
	free(arr);

	return 0;
}
