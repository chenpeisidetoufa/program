#include <iostream>
#include <vector>
#include <list>
//交换
void Swap(std::vector<int>& unorder_array, int a, int b) 
{ 
	// 交换数据,不使用中间变量 
	unorder_array[a] = unorder_array[a] + unorder_array[b]; 
	// 注意这里是unorder_array[b]而不是b 
	unorder_array[b] = unorder_array[a] - unorder_array[b]; 
	unorder_array[a] = unorder_array[a] - unorder_array[b]; 
}

// 冒泡排序 
void BubbleSort(std::vector<int>& unorder_array) 
{ 
	for (int i = 1; i < unorder_array.size(); ++i)
	{ 
		// i代表的是当前的第i轮 
		for (int j = unorder_array.size() - 1; j >= i; --j)
		{
			if (unorder_array[j] < unorder_array[j - 1])
			{
				Swap(unorder_array, j, j - 1);
			}
		}
	} 
} 

// 快速排序的子程序 
int QuickSortPartition(std::vector<int>& unorder_array, int left, int right) 
{ 
	// 快速排序这里使用"双指针" 
	int i = left;
	int j = right; 
	// 假设我们选择的是第一个数据 
	int temp = unorder_array[left]; 

	while (i < j) 
	{ 
		while (i < j && unorder_array[j] > temp) 
		{ 
			// 首先我们先从右侧循环找到比temp小的数据 
			--j; 
		} 
		if (i < j) 
		{ 
			// 表示我们找到了
			// 进行填坑 
			unorder_array[i] = unorder_array[j]; 
			// 左边的指针向右移动 
			++i; 
		} 

		while(i < j && unorder_array[i] < temp) 
		{ 
			++i;
		} 
		if (i < j) 
		{ 
			unorder_array[j] = unorder_array[i];
			--j; 
		} 
	} 
	// temp现在位于中间,左边都小于temp,右边大于temp 
	unorder_array[i] = temp; 
	return i;
}

// 快速排序算法 
void QuickSort(std::vector<int>& unorder_array, int left, int right) 
{ 
	if (left < right) 
	{ 
		// 得到中间位置 
		int middle = QuickSortPartition(unorder_array, left, right); 
		// 递归分之 
		QuickSort(unorder_array, left, middle - 1); 
		
		QuickSort(unorder_array, middle + 1, right); 
	} 
}

//归并排序子程序
void merge(std::vector<int>&arr, int start, int mid, int end)
{
	std::vector<int> tmp;

	int i = start;
	int j = mid + 1;

	while (i <= mid&&j <= end)
	{
		if (arr[i] <= arr[j])
			tmp.push_back(arr[i++]);
		else
			tmp.push_back(arr[j++]);
	}
	while (i <= mid)
		tmp.push_back(arr[i++]);
	while (j <= mid)
		tmp.push_back(arr[j++]);

	for (int i = 0; i < tmp.size(); i++)
		arr[start + i] = tmp[i];
}

//归并排序算法
void mergeSort(std::vector<int> &arr, int start, int end)
{
	if (arr.empty() || start >= end)
		return;
	int mid = (end + start) / 2;

	mergeSort(arr, start, mid);
	mergeSort(arr, mid + 1, end);

	merge(arr, start, mid, end);
	//for (int i = 0; i < arr.size(); i++)
	//{
	//	std::cout << arr[i] << " ";
	//}
	//std::cout << std::endl;
}

void insert(std::list<int>& bucket, int val) 
{
	auto iter = bucket.begin();
	while (iter != bucket.end() && val >= *iter) 
		++iter; 
	//insert会在iter之前插入数据，这样可以稳定排序 
	bucket.insert(iter,val);
}

//桶排序
void BucketSort(std::vector<int>& arr) 
{
	int len = arr.size();
	if (len <= 1) return; 
	int min = arr[0], max = min; 
	for (int i = 1; i < len; ++i) 
	{ 
		if (min > arr[i])
			min = arr[i]; 
		if (max < arr[i]) 
			max = arr[i]; 
	} 
	//k为数字之间的间隔
	int k = 10; 
	//向上取整，例如比如k = 10 min = 2 max = 33 分四个桶{[2,11] };{[12,21]};{[22,31]};{[32,33]}; 
	int bucketsNum = (max - min)/k + 1; 
	std::vector<std::list<int>> buckets(bucketsNum); 
	for(int i=0;i<len;++i) 
	{ 
		int value = arr[i]; 
		//(value-min)/k就是在哪个桶里面，例如21-2 = 19 19/2 = 1 也就是buckets[1]第二个桶
		//插入的时候是按顺序插入的
		insert(buckets[(value-min)/k],value); 
	} 
	int index = 0; 
	for(int i=0;i<bucketsNum;++i) 
	{ 
		//判断是否为空桶
		if(buckets[i].size()) 
		{ 
			for(auto& value:buckets[i]) 
				arr[index++] = value;
		}
	} 
}

int main()
{
	std::vector<int> unorder_array; 
	int data; 
	std::cin >> data; 
	unorder_array.push_back(data); 
	while (std::cin.get() != '\n') 
	{ 
		std::cin >> data;
		unorder_array.push_back(data); 
	} 
	std::cout << "原始数据： "; 
	for (auto it = unorder_array.begin(); it != unorder_array.end(); ++it) 
	{ 
		std::cout << *it << " "; 
	} 
	std::cout << "\n"; 

	//快速排序
	//QuickSort(unorder_array, 0, unorder_array.size() - 1); 
	//std::cout << "快速排序： "; 


	//冒泡排序
	//BubbleSort(unorder_array); 
	//std::cout << "冒泡排序： "; 


	//归并排序
	//mergeSort(unorder_array, 0, unorder_array.size() - 1);
	//std::cout << "归并排序： ";

	//桶排序
	BucketSort(unorder_array);
	std::cout << "桶排序： ";

	for (int i = 0; i < unorder_array.size(); ++i) 
	{ 
		std::cout << unorder_array[i] << " "; 
	} 
	std::cout << std::endl;
	return 0;
}