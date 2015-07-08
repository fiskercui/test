#include <stdio.h>
#include <random>


void swap(int&x, int&y)
{
	int temp = x;
	x = y;
	y = temp;
}

//直接插入排序

void insert_sort(int a[], int n)
{
	for(int i = 1; i < n ; i++)
	{
		for (int j = i-1; j> 0; j--)
		{
			if(a[j+1] < a[j])
				swap(a[j+1], a[j]);
			else
				break;
		}
	}
}

//快速排序
void quick_sort(int s[], int l, int r)
{
	if(l < r)
	{
		int i =l, j=r ,x = s[i];
		while(i < j ){
			while(i < j && s[j] >= x) //从右边向左找出第一个小于x的数
				j--;
			if(i < j)
				s[i++] = s[j];

			while(i < j && s[i] < x) // 从左边向右找出第一个大于x的树
				i++;
			if (i < j)
				s[j--] = s[i];
		}

		s[i] = x;
		quick_sort(s, l, i-1);
		quick_sort(s, i+1, r);
	}
}


//归并算法
void mergeArray(int a[], int first,int last, int temp[])
{
	int mid = (first + last) / 2;
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;

	while(i <= m && j <<n)
	{
		if(a[i] <= a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while( i <= m)
		temp[k++] = a[i++];
	while( j <= n)
		temp[k++] = a[j++];
	for (int i = 0; i < k; ++i)
	{
		a[first + i] = temp[i];
	}
}


void mergeSort(int a[], int first, int last, int temp[])
{
	if (first< last)
	{
		mergeSort(a,first, (first+last)/2, temp);
		mergeSort(a,(first + last)/2 + 1, last, temp);
		mergeArray(a, first, last, temp);
	}
}

void testMergeSort(int a[], int n)
{
	int *p = new int[n];
	if(p == NULL)
		return ;
	mergeSort(a, 0, n-1, p);
	return ;
}


int main(int argc, char const *argv[])
{
	/* code */
	std::default_random_engine generator;
	std::uniform_int_distribution<int> dis(0,100);
	int array[10];
	printf("before sort\n");
	for (int i = 0; i < 10; ++i)
	{
		array[i] = dis(generator);
		printf("  %d", array[i]);
	}
	printf("\n");
	// quick_sort(array, 0, 9);
	// insert_sort(array, 10);
	testMergeSort(array, 10);

	printf("after sort\n");
	for (int i = 0; i < 10; ++i)
	{
		printf("  %d", array[i]);		
	}
	printf("\n");
	return 0;
}