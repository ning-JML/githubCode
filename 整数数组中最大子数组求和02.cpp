# githubCode
//20160327
#include<iostream>
#include<algorithm>
using namespace std;

int main()
{
	int arr[100];
	int NUM = 0;
	int MAXSUM = 0;
	int MINNUMend = 0;
	int MINSUM = 0;
	int SUM = 0;
	int jump = 0;
	int start = -1;
	for (; NUM < 100; NUM++)
	{
		cin >> arr[NUM];
		if (getchar() == '\n')
		{
			break;
		}
	}
	if (NUM == 100)
	{
		NUM = 99;
	}
	for (int i = 0;; i < NUM ? i++ : i = 0)
	{
		if (i == 0)
		{
			jump += 1;
			if (jump == 3)
			{
				break;
			}
		}
		if (start == i)
		{
			break;
		}
		SUM = min(SUM + arr[i], arr[i]);
		if (MINSUM > SUM)
		{
			MINNUMend = i;
		}
		MINSUM = min(SUM, MINSUM);
		if (start == -1)
		{
			start = 0;
		}
		if (SUM >= 0)
		{
			start = i;
		}
	}
	SUM = 0;
	jump = 0;
	start = -1;
	for (int i = MINNUMend;; i < NUM ? i++ : i = 0)
	{
		if (i == MINNUMend)
		{
			jump += 1;
			if (jump == 3)
			{
				break;
			}
		}
		if (start == i)
		{
			break;
		}
		SUM = max(SUM + arr[i], arr[i]);
		MAXSUM = max(SUM, MAXSUM);
		if (start == -1)
		{
			start = MINNUMend;
		}
		if (SUM <= 0)
		{
			start = i;
		}
	}
	cout << "最大和：" << MAXSUM << endl;
	return 0;
}
