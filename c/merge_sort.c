/*
 * 分治法
 */
#include <stdio.h>
void merge_sort(int *, int, int);
void merge(int *, int, int, int);
int main(void)
{
	int a[8] = {2, 5, 3, 7, 1, 9, 8, 4}, i;
	merge_sort(a, 0, 7);
	for(i = 0; i<=7; i++){
		printf("%3d", a[i]);
	}
	printf("\n");
	return 0;
}


void merge_sort(int *arr, int s, int e)
{
	int m;
	if(s < e){
		m = (s+e)/2;
		merge_sort(arr, s, m);
		merge_sort(arr, m+1, e);
		merge(arr, s, m, e);
	}
}

void merge(int *arr, int s, int m, int e)
{
	int i, j, k;
	int llen = m-s+1;
	int rlen = e-m;
	int larr[llen], rarr[rlen];
	for(i = 0; i < llen; i++){
		larr[i] = arr[s+i];
	}
	for(j = 0; j < rlen; j++){
		rarr[j] = arr[m+j+1];
	}
	i = j = 0;
	for(k = s; k <= e; k++){
		if(j >= rlen || (larr[i] < rarr[j] && i < llen)){
			arr[k] = larr[i];
			i++;
		}else{
			arr[k] = rarr[j];
			j++;
		}
	}
}
