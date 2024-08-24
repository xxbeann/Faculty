#include <iostream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;

int main(void)
{
	vector<int> a = {1, 2, 3, 4, 5};
	vector<int> b = {1, 2, 3, 4, 5};
	vector<int> c(5);
	vector<int>::iterator it;

	transform(a.begin(), a.end(), b.begin(), c.begin(), plus<int>());

	for (it = c.begin(); it != c.end(); it++)
	{
		cout << *it << " ";
	}

	return 0;
}