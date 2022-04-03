#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

void merge(int *data, int *buffer, size_t begin0, size_t begin1, size_t end)
{
	int *dataPtr = data + begin0;
	int *dataBeginPtr = data + begin0;
	
	const size_t bufBegin0 = 0;
	const size_t bufBegin1 = begin1 - begin0;
	const size_t bufEnd = end - begin0;
	size_t bufFrom0 = bufBegin0;
	size_t bufFrom1 = bufBegin1;
	
	memcpy(buffer, dataBeginPtr, (bufEnd + 1) * sizeof(int));
	
	while(bufFrom0 < bufBegin1 && bufFrom1 <= bufEnd)
	{
		if(buffer[bufFrom0] > buffer[bufFrom1])
		{
			*dataPtr = buffer[bufFrom1];
			++bufFrom1;
			++dataPtr;
		}
		else // if(buffer[bufFrom0] < buffer[bufFrom1])
		{
			*dataPtr = buffer[bufFrom0];
			++bufFrom0;
			++dataPtr;
		}
	}
	while(bufFrom1 <= bufEnd)
	{
		*dataPtr = buffer[bufFrom1];
		++dataPtr;
		++bufFrom1;
	}
	
	while(bufFrom0 < bufBegin1)
	{
		*dataPtr = buffer[bufFrom0];
		++dataPtr;
		++bufFrom0;
	}
}

void merge_sort(int *data, int *buffer, size_t begin, size_t end)
{
	if (begin < end)
	{
		size_t middle = (begin + end) / 2;
		merge_sort(data, buffer, begin, middle);
		merge_sort(data, buffer, middle + 1, end);
		merge(data, buffer, begin, middle + 1, end);
	}
}

void sort(int *data, size_t size)
{
	int *buffer = calloc(size, sizeof(int)); 
	merge_sort(data, buffer, 0, size - 1);
	free(buffer);
}

