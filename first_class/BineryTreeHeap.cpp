#include <iostream>
#include <assert.h>

typedef int DataType;
typedef struct Heap {
	DataType* arr;
	int size;
	int capacity;
}HP;

void HPInit(HP* php) {
	assert(php);
	php->arr = NULL;
	php->size = php->capacity = 0;
}
void HPDestory(HP* php) {
	assert(php);
	if (php->arr)
		free(php->arr);
	php->arr = NULL;
	php->size = php->capacity = 0;
}
void HPPush(HP* php, DataType x) 
{
	assert(php);
	if (php->size == php->capacity) 
	{
		int newCapacity = php->capacity == 0 ? 4 : 2 * php->capacity;
		DataType* tmp = (DataType*)realloc(php->arr, newCapacity * sizeof(DataType));
		if (tmp == NULL) 
		{
			perror("realloc faild");
			exit(1);
		}
		php->arr = tmp;
		php->capacity = newCapacity;
	}
	php->arr[php->size] = x;
	AdjustUP(php->arr, php->size);
		++php->size;
}
void HPPop(HP* php) 
{
	assert(php && php->size);
	Swap(&php->arr[0], &php->arr[php->size - 1]);
	--php->size;
	AdjustDown(php->arr, 0, php->size);
}
void AdjustUP(DataType*arr,int child) 
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (arr[child] < arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
void AdjustDown(DataType* arr, int parent, int n) 
{
	int child = parent * 2 + 1;
	while (true)
	{
		if (arr[child] > arr[child + 1] && child + 1 < n )
		{
			child++;
		}
		if (arr[child] < arr[parent])
		{

		}
	}
}
void Swap(int* x, int* y) 
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
bool HPEmpty() 
{

}

int main() {
	return 0;
}