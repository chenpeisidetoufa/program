#include <iostream>

using namespace std;
int main()
{
	int array[100]; 
	//����Ĵ�С 
	int size = 0; 
	cout << "������Ҫ�����������Ԫ�ظ�����" << endl; 
	cin >> size; 
	//�������а������Ԫ�� 
	for (auto i = 0; i < size; i++)
	{ 
		array[i] = i; 
	} 
	//����Ҫ�������в��ҵ���
	int checkElement; 
	cout << "����Ҫ�������в��ҵ�����" << endl;
	cin >> checkElement; 
	//����ĵ�һ��Ԫ�� ��Сֵ
	int headIndex = 0;
	//��������һ��Ԫ�� ���ֵ
	int tailIndex = (size - 1); 
	if (checkElement<headIndex || checkElement>tailIndex)
	{ 
		cout << "����������ֲ��ڵ�ǰ�����ķ�Χ��" << endl;
		return 0;
	}
	//��������б������ҳ���Ӧ�����������е��±����� 
	int centerIndex = (headIndex + tailIndex) / 2; 
	//����м�������ֵ����Ҫ������ֵ��������߽��в��� 
	while (headIndex <= tailIndex) 
	{
		if (array[centerIndex] < checkElement) 
		{
			headIndex = centerIndex + 1; 
			cout << "������----�ұ�" << endl; 
		}
		else if (array[centerIndex] == checkElement) 
		{
			cout << "���ҵ��˵�ǰ������" <<array[centerIndex]<<endl;
			break;
		}
		else
		{
			tailIndex = centerIndex - 1; 
			cout << "������----���" << endl;
		}
		centerIndex = (headIndex + tailIndex) / 2;
	}
	if (headIndex > tailIndex) 
	{ 
		cout << "��ǰ������û�в��ҵ�����Ҫ������" << endl; 
	}
	return 0;
}