#include <iostream>

using namespace std;
int main()
{
	int array[100]; 
	//数组的大小 
	int size = 0; 
	cout << "输入需要创建的数组的元素个数：" << endl; 
	cin >> size; 
	//向数组中按序添加元素 
	for (auto i = 0; i < size; i++)
	{ 
		array[i] = i; 
	} 
	//输入要在数组中查找的数
	int checkElement; 
	cout << "输入要在数组中查找的数：" << endl;
	cin >> checkElement; 
	//数组的第一个元素 最小值
	int headIndex = 0;
	//数组的最后一个元素 最大值
	int tailIndex = (size - 1); 
	if (checkElement<headIndex || checkElement>tailIndex)
	{ 
		cout << "你输入的数字不在当前搜索的范围内" << endl;
		return 0;
	}
	//对数组进行遍历，找出对应数字在数组中的下标索引 
	int centerIndex = (headIndex + tailIndex) / 2; 
	//如果中间索引的值大于要搜索的值，则在左边进行查找 
	while (headIndex <= tailIndex) 
	{
		if (array[centerIndex] < checkElement) 
		{
			headIndex = centerIndex + 1; 
			cout << "查找中----右边" << endl; 
		}
		else if (array[centerIndex] == checkElement) 
		{
			cout << "查找到了当前的数字" <<array[centerIndex]<<endl;
			break;
		}
		else
		{
			tailIndex = centerIndex - 1; 
			cout << "查找中----左边" << endl;
		}
		centerIndex = (headIndex + tailIndex) / 2;
	}
	if (headIndex > tailIndex) 
	{ 
		cout << "当前数组中没有查找到你想要的数字" << endl; 
	}
	return 0;
}