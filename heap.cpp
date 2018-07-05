#include <stdio.h>
#include<iostream>
#include<vector>
using namespace std;

class Heap
{
public:
	int size;
	int* arr;
	void heapify(int i)
	{
		int l = left(i);
		int r = right(i);
		int max = i;
		if (l< size && arr[max]<arr[l])
			max = l;
		if (r< size && arr[max]<arr[r])
			max = r;
		if (max != i)
		{
			int temp = arr[i];
			arr[i] = arr[max];
			arr[max] = temp;
			heapify(max);
		}
	}
	void BuildMinimum_List(int x)
	{
		if (x < arr[0])
			arr[0] = x;
		heapify(0);
	}

	void build_max_heap()
	{
		for (int k = size / 2; k >= 0; k--)
			heapify(k);
	}
	Heap(int n, vector<int> &v)
	{
		size = n;
		arr = new int[n];
		for (int i = 0; i<size; i++)
			arr[i] = v[i];
	}
	~Heap()
	{
		delete[] arr;
	}
	int left(int i)
	{
		return   2 * i + 1;

	}
	int right(int i)
	{
		return  2 * i + 2;
	}
};
//int main() {
int fun()
{
	int t;
	int n;
	int k;
	int m;
	cin >> t;
	while (t--)
	{
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i<n; i++)
			cin >> a[i];
//		cin >> k;
//		Heap h(k, a);
//		h.build_max_heap();
//		for (int i = k; i<n; i++)
//		{
//			h.BuildMinimum_List(a[i]);
//		}
//
//		cout << h.arr[0] << endl;
	}
	return 0;
}
