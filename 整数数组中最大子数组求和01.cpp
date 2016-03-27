# githubCode
#include<iostream>
#include <algorithm>
using namespace std;

int main()
{
	int a[100];
	int NUM = 0;
	int MAXSUM = 0;
	int SUM = 0;
	for (; NUM<100; NUM++)
	{
		cin >> a[NUM];
		if (getchar() == '\n')
		{
			break;
		}
	}
	if (NUM == 100)
	{
		NUM = 99;
	}
	for (int i = 0; i <= NUM; i++)
	{
		SUM = max(SUM+a[i], a[i]);
		MAXSUM = max(SUM, MAXSUM);
	}
	cout <<"最大和："<< MAXSUM << endl;
	return 0;
}
