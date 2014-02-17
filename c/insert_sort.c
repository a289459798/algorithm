/*
 * 插入排序
 */
#include <stdio.h>
#define size 7
int main(void)
{
	void insert_sort(int *arr);
	int arr[size] = {2, 1, 5, 3, 7, 4, 1}, *p;
	insert_sort(arr);
	return 0;
}

void insert_sort(int *arr)
{
	int i, j, t;
	for(i = 1; i < size; i++){
		j = i - 1;
		t = arr[i];
		while(arr[j] > t && j >= 0){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = t;
	}
	for(j = 0; j <= size; j++)
		printf("%3d", arr[j]);
	printf("\n");
}
