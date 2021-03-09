#pragma once
#include<iostream>
#include<time.h>
#include<queue>
using namespace std;
#define M 1

class Sort {
private:
	int amount;//随机数个数
	long long compare_degree,exchange_degree;//比较次数，交换次数
	int* randomArray;//随机数序列

public:
	Sort(int a = 0) : compare_degree(0),exchange_degree(0)//构造函数
	{
		amount = a;
		randomArray = new int[amount];
	}
	void clear();//清零函数
	void print();//打印计数
	void create();//随机生成一定数量的随机数


	void bubbleSort();//冒泡排序
	void selectionSort();//选择排序
	void straightInsertion(int left, int right);//直接插入排序
	void shellSort(int left, int right);//希尔排序

	void quickSort(int left, int right);//快速排序
	int partition(const int left, const int right);//划分函数

	void heapSort(int left, int right);//堆排序
	void siftDown(int start, int m);//对从start到m的结点调整
	
	void mergeSort();//归并排序
	void mergesort(int* L, int left, int right);//递归进行划分
	void merge(int* L, const int left, const int mid, const int right);//合并

	void radixSort(int left, int right);//基数排序
	
};
void menu() //打印选择菜单
{
	cout << "**                 排序算法比较               **" << '\n'
		<< "================================================" << '\n'
		<< "**                 1--冒泡排序                **" << '\n'
		<< "**                 2--选择排序                **" << '\n'
		<< "**                 3--直接插入排序            **" << '\n'
		<< "**                 4--希尔排序                **" << '\n'
		<< "**                 5--快速排序                **" << '\n'
		<< "**                 6--堆排序                  **" << '\n'
		<< "**                 7--归并排序                **" << '\n'
		<< "**                 8--基数排序                **" << '\n'
		<< "**                 9--退出程序                **" << '\n'
		<< "================================================" << endl;
	cout << "请输入要产生的随机数个数：";
	return;
}
void Sort::clear() { compare_degree = 0;exchange_degree = 0; }
void Sort::print() {//打印计数
	cout << "该排序算法比较次数：" << compare_degree << endl;
	cout << "该排序算法交换次数：" << exchange_degree << endl;
}
void Sort::create()//随机生成一定数量的随机数
{
	srand((unsigned)time(NULL));
	for (int i = 0;i < amount;i++)
	{
		randomArray[i] = rand();
	}
	return;
}

void Sort::bubbleSort()//冒泡算法
{
	for (int i = 1;i < amount;i++)
		for (int j = amount - 1;j >= i;j--)
		{
			if (randomArray[j - 1] > randomArray[j])
			{
				swap(randomArray[j], randomArray[j - 1]);//不断交换，让此后的最小值到位
				exchange_degree++;
			}
			compare_degree++;
		}
	return;
}
void Sort::selectionSort()//选择排序
{
	for (int i = 0;i < amount;i++)
	{
		int min = i;
		for (int j = i + 1;j < amount;j++)
		{
			if (randomArray[min] > randomArray[j])//找出此后的最小值并记录
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
void Sort::straightInsertion(int left, int right)//直接插入排序
{
	int i, j;
	for (i = left + 1;i < right;i++)
	{
		if (randomArray[i] < randomArray[i - 1]) {//假设前面都已经排好
			int temp = randomArray[i];
			for (j = i - 1;j >= left && temp <= randomArray[j];j--)//从要确定的数向前依次后移
			{
				randomArray[j + 1] = randomArray[j];
				exchange_degree++;
			}
			compare_degree++;
			randomArray[j + 1] = temp;//直到找到它应该在的位置将其插入
		}
	}
	return;
}
void Sort::shellSort(int left, int right)//希尔排序
{
	int i, j, gap = right - left + 1, temp;
	while (gap > 1) {
		gap = gap / 3 + 1;//下一增量值
		for (i = left + gap;i < right;i++)//各子序列交替处理
			if (randomArray[i] < randomArray[i - gap]) {//当当前位置与前逆序
				compare_degree++;
				temp = randomArray[i];
				j = i - gap;
				do {
					randomArray[j + gap] = randomArray[j];//从逆序位置开始后移排序
					j -= gap;//将每个子列相同位置的排好顺序，直到每个子列只剩一个值
					exchange_degree++;
				} while (j >= left && temp < randomArray[j]);
				randomArray[j + gap] = temp;
			}
	}
	return;
}

void Sort::quickSort(int left, int right)//快速排序
{
	if (right - left <= M) { straightInsertion(left, right);return; }
	int pivotpos = partition(left, right - 1);
	quickSort(left, pivotpos);
	quickSort(pivotpos + 1, right);
	return;
}
int Sort::partition(const int left, const int right)//划分函数
{
	int mid = (left + right) / 2, k = left;
	if (randomArray[mid] < randomArray[k])
		k = mid;
	if (randomArray[right] < randomArray[k])
		k = right;
	if (k != left) { swap(randomArray[k], randomArray[left]);exchange_degree++; }
	if (mid != right && randomArray[mid] < randomArray[right]) { swap(randomArray[mid], randomArray[right]);exchange_degree++; }
	int pivot = randomArray[right];//将最小值交换到左侧，中间值到最右侧作为划分基准
	int i = left, j = right - 1;
	while (i < j) {
		while (i < j && randomArray[i] < pivot)i++;
		while (i < j && pivot < randomArray[j])j--;
		if (i < j) { swap(randomArray[i], randomArray[j]);i++;j--; }
		compare_degree++;
	} //比基准小放左，大的放右，直到两头相遇  
	if (randomArray[i] > pivot) { randomArray[right] = randomArray[i];randomArray[i] = pivot; }//pivot移到它排序后应该在的位置
	return i;
}

void Sort::heapSort(int left, int right)//堆排序
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
void Sort::siftDown(int start, int m)//对从start到m的结点调整
{
	int i = start;int j = 2 * i + 1;
	int temp = randomArray[i];
	while (j <= m) {
		if (j < m && randomArray[j] < randomArray[j + 1])j++;//选择两子女中大的
		if (temp >= randomArray[j])break;//当前结点大不作调整
		else {
			randomArray[i] = randomArray[j];//当前结点小则让大的子女上移
			i = j;j = 2 * j + 1;//i下移
		}
		compare_degree++;
	}
	randomArray[i] = temp;
}

void Sort::mergeSort()//归并排序
{
	int* temp = new int[amount];
	for (int i = 0; i < amount; i++)
		temp[i] = randomArray[i];
	mergesort(temp, 0, amount - 1);
	delete[] temp;
	temp = NULL;
}
void Sort::mergesort(int* L, int left, int right)//递归进行划分
{
	if (left >= right)return;
	int mid = (left + right) / 2;
	mergesort(L, left, mid);
	mergesort(L, mid + 1, right);
	merge(L, left, mid, right);
	return;
}
void Sort::merge(int* L, const int left, const int mid, const int right)//合并
{
	int s1 = left, s2 = mid + 1, t = left;//s1、s2检测指针，t存放指针
	while (s1 <= mid && s2 <= right)
	{
		if (randomArray[s1] <= randomArray[s2])//两划分序列比较合并
			L[t++] = randomArray[s1++];
		else
			L[t++] = randomArray[s2++];
		compare_degree++;
	}
	for (;s1 <= mid;t++, s1++)L[t] = randomArray[s1];
	for (;s2 <= right;t++, s2++)L[t] = randomArray[s2];
	for (int i = left; i <= right; i++)//将合并调整好的字段写入结果序列
	{
		randomArray[i] = L[i];
		exchange_degree++;
	}
}

void Sort::radixSort(int left, int right) // 基数排序
{
	int i, maxNum = left;
	for (i = left + 1;i < right;i++)//找出最大值，用最大值位数决定基数
		if (randomArray[i] > randomArray[maxNum])
			maxNum = i;
	int max = randomArray[maxNum];
	queue<int> bucket[10];
	for (int power = 1; max / power > 0; power *= 10) {//从低位到高位处理
		for (i = left; i < right; i++)//按每位0~9链入
			bucket[(randomArray[i] / power) % 10].push(randomArray[i]);
		int t = left;
		for (i = 0;i < 10;i++) //从每个链依次取出组成新排序
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
