#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
using namespace std;

bool is_even(int n)
{
	return (n % 2 == 0);
}

int main(void)
{
	vector<int> v1(100);
	vector<int>::iterator it;
	srand((size_t)time(NULL));

	for (int i = 0; i < 100; i++) // ��������, ���Ϳ� ����
	{
		int n = rand();
		v1[i] = n;
	}

	for (it = v1.begin(); it != v1.end(); it++) //���� ���
	{
		cout << *it << " ";
	}

	size_t count = count_if(v1.begin(), v1.end(), is_even);
	cout << endl << "¦������: "<< count << endl;
	return 0;
}