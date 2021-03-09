#pragma once
#include<iostream>
#include<time.h>
#include<queue>
using namespace std;
#define M 1

class Sort {
private:
	int amount;//���������
	long long compare_degree,exchange_degree;//�Ƚϴ�������������
	int* randomArray;//���������

public:
	Sort(int a = 0) : compare_degree(0),exchange_degree(0)//���캯��
	{
		amount = a;
		randomArray = new int[amount];
	}
	void clear();//���㺯��
	void print();//��ӡ����
	void create();//�������һ�������������


	void bubbleSort();//ð������
	void selectionSort();//ѡ������
	void straightInsertion(int left, int right);//ֱ�Ӳ�������
	void shellSort(int left, int right);//ϣ������

	void quickSort(int left, int right);//��������
	int partition(const int left, const int right);//���ֺ���

	void heapSort(int left, int right);//������
	void siftDown(int start, int m);//�Դ�start��m�Ľ�����
	
	void mergeSort();//�鲢����
	void mergesort(int* L, int left, int right);//�ݹ���л���
	void merge(int* L, const int left, const int mid, const int right);//�ϲ�

	void radixSort(int left, int right);//��������
	
};
void menu() //��ӡѡ��˵�
{
	cout << "**                 �����㷨�Ƚ�               **" << '\n'
		<< "================================================" << '\n'
		<< "**                 1--ð������                **" << '\n'
		<< "**                 2--ѡ������                **" << '\n'
		<< "**                 3--ֱ�Ӳ�������            **" << '\n'
		<< "**                 4--ϣ������                **" << '\n'
		<< "**                 5--��������                **" << '\n'
		<< "**                 6--������                  **" << '\n'
		<< "**                 7--�鲢����                **" << '\n'
		<< "**                 8--��������                **" << '\n'
		<< "**                 9--�˳�����                **" << '\n'
		<< "================================================" << endl;
	cout << "������Ҫ�����������������";
	return;
}
void Sort::clear() { compare_degree = 0;exchange_degree = 0; }
void Sort::print() {//��ӡ����
	cout << "�������㷨�Ƚϴ�����" << compare_degree << endl;
	cout << "�������㷨����������" << exchange_degree << endl;
}
void Sort::create()//�������һ�������������
{
	srand((unsigned)time(NULL));
	for (int i = 0;i < amount;i++)
	{
		randomArray[i] = rand();
	}
	return;
}

void Sort::bubbleSort()//ð���㷨
{
	for (int i = 1;i < amount;i++)
		for (int j = amount - 1;j >= i;j--)
		{
			if (randomArray[j - 1] > randomArray[j])
			{
				swap(randomArray[j], randomArray[j - 1]);//���Ͻ������ô˺����Сֵ��λ
				exchange_degree++;
			}
			compare_degree++;
		}
	return;
}
void Sort::selectionSort()//ѡ������
{
	for (int i = 0;i < amount;i++)
	{
		int min = i;
		for (int j = i + 1;j < amount;j++)
		{
			if (randomArray[min] > randomArray[j])//�ҳ��˺����Сֵ����¼
			{
				min = j;

			}
			compare_degree++;
		}
		if (min != i)
		{
			swap(randomArray[i], randomArray[min]);
			exchange_degree++;
		}
	}
	return;
}
void Sort::straightInsertion(int left, int right)//ֱ�Ӳ�������
{
	int i, j;
	for (i = left + 1;i < right;i++)
	{
		if (randomArray[i] < randomArray[i - 1]) {//����ǰ�涼�Ѿ��ź�
			int temp = randomArray[i];
			for (j = i - 1;j >= left && temp <= randomArray[j];j--)//��Ҫȷ��������ǰ���κ���
			{
				randomArray[j + 1] = randomArray[j];
				exchange_degree++;
			}
			compare_degree++;
			randomArray[j + 1] = temp;//ֱ���ҵ���Ӧ���ڵ�λ�ý������
		}
	}
	return;
}
void Sort::shellSort(int left, int right)//ϣ������
{
	int i, j, gap = right - left + 1, temp;
	while (gap > 1) {
		gap = gap / 3 + 1;//��һ����ֵ
		for (i = left + gap;i < right;i++)//�������н��洦��
			if (randomArray[i] < randomArray[i - gap]) {//����ǰλ����ǰ����
				compare_degree++;
				temp = randomArray[i];
				j = i - gap;
				do {
					randomArray[j + gap] = randomArray[j];//������λ�ÿ�ʼ��������
					j -= gap;//��ÿ��������ͬλ�õ��ź�˳��ֱ��ÿ������ֻʣһ��ֵ
					exchange_degree++;
				} while (j >= left && temp < randomArray[j]);
				randomArray[j + gap] = temp;
			}
	}
	return;
}

void Sort::quickSort(int left, int right)//��������
{
	if (right - left <= M) { straightInsertion(left, right);return; }
	int pivotpos = partition(left, right - 1);
	quickSort(left, pivotpos);
	quickSort(pivotpos + 1, right);
	return;
}
int Sort::partition(const int left, const int right)//���ֺ���
{
	int mid = (left + right) / 2, k = left;
	if (randomArray[mid] < randomArray[k])
		k = mid;
	if (randomArray[right] < randomArray[k])
		k = right;
	if (k != left) { swap(randomArray[k], randomArray[left]);exchange_degree++; }
	if (mid != right && randomArray[mid] < randomArray[right]) { swap(randomArray[mid], randomArray[right]);exchange_degree++; }
	int pivot = randomArray[right];//����Сֵ��������࣬�м�ֵ�����Ҳ���Ϊ���ֻ�׼
	int i = left, j = right - 1;
	while (i < j) {
		while (i < j && randomArray[i] < pivot)i++;
		while (i < j && pivot < randomArray[j])j--;
		if (i < j) { swap(randomArray[i], randomArray[j]);i++;j--; }
		compare_degree++;
	} //�Ȼ�׼С���󣬴�ķ��ң�ֱ����ͷ����  
	if (randomArray[i] > pivot) { randomArray[right] = randomArray[i];randomArray[i] = pivot; }//pivot�Ƶ��������Ӧ���ڵ�λ��
	return i;
}

void Sort::heapSort(int left, int right)//������
{
	for (int i = (right - 2) / 2; i >= 0; i--)
		siftDown(i, right - 1);
	for (int i = right - 1; i >= 0; i--)
	{
		swap(randomArray[0], randomArray[i]);
		exchange_degree++;
		siftDown(0, i - 1);
	}
}
void Sort::siftDown(int start, int m)//�Դ�start��m�Ľ�����
{
	int i = start;int j = 2 * i + 1;
	int temp = randomArray[i];
	while (j <= m) {
		if (j < m && randomArray[j] < randomArray[j + 1])j++;//ѡ������Ů�д��
		if (temp >= randomArray[j])break;//��ǰ����������
		else {
			randomArray[i] = randomArray[j];//��ǰ���С���ô����Ů����
			i = j;j = 2 * j + 1;//i����
		}
		compare_degree++;
	}
	randomArray[i] = temp;
}

void Sort::mergeSort()//�鲢����
{
	int* temp = new int[amount];
	for (int i = 0; i < amount; i++)
		temp[i] = randomArray[i];
	mergesort(temp, 0, amount - 1);
	delete[] temp;
	temp = NULL;
}
void Sort::mergesort(int* L, int left, int right)//�ݹ���л���
{
	if (left >= right)return;
	int mid = (left + right) / 2;
	mergesort(L, left, mid);
	mergesort(L, mid + 1, right);
	merge(L, left, mid, right);
	return;
}
void Sort::merge(int* L, const int left, const int mid, const int right)//�ϲ�
{
	int s1 = left, s2 = mid + 1, t = left;//s1��s2���ָ�룬t���ָ��
	while (s1 <= mid && s2 <= right)
	{
		if (randomArray[s1] <= randomArray[s2])//���������бȽϺϲ�
			L[t++] = randomArray[s1++];
		else
			L[t++] = randomArray[s2++];
		compare_degree++;
	}
	for (;s1 <= mid;t++, s1++)L[t] = randomArray[s1];
	for (;s2 <= right;t++, s2++)L[t] = randomArray[s2];
	for (int i = left; i <= right; i++)//���ϲ������õ��ֶ�д��������
	{
		randomArray[i] = L[i];
		exchange_degree++;
	}
}

void Sort::radixSort(int left, int right) // ��������
{
	int i, maxNum = left;
	for (i = left + 1;i < right;i++)//�ҳ����ֵ�������ֵλ����������
		if (randomArray[i] > randomArray[maxNum])
			maxNum = i;
	int max = randomArray[maxNum];
	queue<int> bucket[10];
	for (int power = 1; max / power > 0; power *= 10) {//�ӵ�λ����λ����
		for (i = left; i < right; i++)//��ÿλ0~9����
			bucket[(randomArray[i] / power) % 10].push(randomArray[i]);
		int t = left;
		for (i = 0;i < 10;i++) //��ÿ��������ȡ�����������
			while (bucket[i].empty() == false)
			{
				randomArray[t++] = bucket[i].front();
				bucket[i].pop();
				compare_degree++;
				exchange_degree++;
			}
	}
	return;
}
