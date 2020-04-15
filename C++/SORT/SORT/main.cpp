#include <iostream>
#include <vector>
#include <list>
//����
void Swap(std::vector<int>& unorder_array, int a, int b) 
{ 
	// ��������,��ʹ���м���� 
	unorder_array[a] = unorder_array[a] + unorder_array[b]; 
	// ע��������unorder_array[b]������b 
	unorder_array[b] = unorder_array[a] - unorder_array[b]; 
	unorder_array[a] = unorder_array[a] - unorder_array[b]; 
}

// ð������ 
void BubbleSort(std::vector<int>& unorder_array) 
{ 
	for (int i = 1; i < unorder_array.size(); ++i)
	{ 
		// i������ǵ�ǰ�ĵ�i�� 
		for (int j = unorder_array.size() - 1; j >= i; --j)
		{
			if (unorder_array[j] < unorder_array[j - 1])
			{
				Swap(unorder_array, j, j - 1);
			}
		}
	} 
} 

// ����������ӳ��� 
int QuickSortPartition(std::vector<int>& unorder_array, int left, int right) 
{ 
	// ������������ʹ��"˫ָ��" 
	int i = left;
	int j = right; 
	// ��������ѡ����ǵ�һ������ 
	int temp = unorder_array[left]; 

	while (i < j) 
	{ 
		while (i < j && unorder_array[j] > temp) 
		{ 
			// ���������ȴ��Ҳ�ѭ���ҵ���tempС������ 
			--j; 
		} 
		if (i < j) 
		{ 
			// ��ʾ�����ҵ���
			// ������� 
			unorder_array[i] = unorder_array[j]; 
			// ��ߵ�ָ�������ƶ� 
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
	// temp����λ���м�,��߶�С��temp,�ұߴ���temp 
	unorder_array[i] = temp; 
	return i;
}

// ���������㷨 
void QuickSort(std::vector<int>& unorder_array, int left, int right) 
{ 
	if (left < right) 
	{ 
		// �õ��м�λ�� 
		int middle = QuickSortPartition(unorder_array, left, right); 
		// �ݹ��֮ 
		QuickSort(unorder_array, left, middle - 1); 
		
		QuickSort(unorder_array, middle + 1, right); 
	} 
}

//�鲢�����ӳ���
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

//�鲢�����㷨
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
	//insert����iter֮ǰ�������ݣ����������ȶ����� 
	bucket.insert(iter,val);
}

//Ͱ����
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
	//kΪ����֮��ļ��
	int k = 10; 
	//����ȡ�����������k = 10 min = 2 max = 33 ���ĸ�Ͱ{[2,11] };{[12,21]};{[22,31]};{[32,33]}; 
	int bucketsNum = (max - min)/k + 1; 
	std::vector<std::list<int>> buckets(bucketsNum); 
	for(int i=0;i<len;++i) 
	{ 
		int value = arr[i]; 
		//(value-min)/k�������ĸ�Ͱ���棬����21-2 = 19 19/2 = 1 Ҳ����buckets[1]�ڶ���Ͱ
		//�����ʱ���ǰ�˳������
		insert(buckets[(value-min)/k],value); 
	} 
	int index = 0; 
	for(int i=0;i<bucketsNum;++i) 
	{ 
		//�ж��Ƿ�Ϊ��Ͱ
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
	std::cout << "ԭʼ���ݣ� "; 
	for (auto it = unorder_array.begin(); it != unorder_array.end(); ++it) 
	{ 
		std::cout << *it << " "; 
	} 
	std::cout << "\n"; 

	//��������
	//QuickSort(unorder_array, 0, unorder_array.size() - 1); 
	//std::cout << "�������� "; 


	//ð������
	//BubbleSort(unorder_array); 
	//std::cout << "ð������ "; 


	//�鲢����
	//mergeSort(unorder_array, 0, unorder_array.size() - 1);
	//std::cout << "�鲢���� ";

	//Ͱ����
	BucketSort(unorder_array);
	std::cout << "Ͱ���� ";

	for (int i = 0; i < unorder_array.size(); ++i) 
	{ 
		std::cout << unorder_array[i] << " "; 
	} 
	std::cout << std::endl;
	return 0;
}