# githubCode
//2016/03/06
//打印100以内四则运算式，包含真分数。
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
	int numa, numb, numc, numd, tmp, x, y, n = 0;
	char sign;                                        //运算符
	srand(time(0));
	for (; n < 30; n++)                               //生成30个算式
	{
		x = rand() % 4;                               //生成算式符号
		switch (x)
		{
		case 0:sign = '+'; break;
		case 1:sign = '-'; break;
		case 2:sign = '*'; break;
		case 3:sign = '/';
		}
		y = rand() % 9;                               //生成算式形式
		switch (y)
		{
		case 0:                                       //整数与整数运算
		case 1:
		case 2:
		case 3:
		case 4:
			numa = rand() % 100;
			do{
				numb = rand() % 100;
			} while (0 == numb&&'÷' == sign);
			cout << numa << sign << numb << "=" << endl << endl;   //打印
			break;
		case 5:                                       //分数与整数运算
			do{
				numa = rand() % 100;
			} while (0 == numa);
			do{
				numb = rand() % 100;
			} while (0 == numb||numb == numa);
			if (numa > numb)
			{
				tmp = numa;
				numa = numb;
				numb = tmp;
			}
			do{
				numc = rand() % 100;
			} while (0 == numc&&'÷' == sign);
			cout << numa << endl << "—" << sign << numc << "=" << endl << numb << endl<<endl;   //打印
			break;
		case 6:                                       //整数与分数运算
			numa = rand() % 100;
			do{
				numb = rand() % 100;
			} while (0 == numb);
			do{
				numc = rand() % 100;
			} while (0 == numc||numb == numc);
			if (numb > numc)
			{
				tmp = numc;
				numc = numb;
				numb = tmp;
			}
			cout << "   " << numb << endl << numa << sign << "—=" << endl << "   " << numc << endl << endl;   //打印
			break;
		case 7:                                       //分数与分数运算
		case 8:
			do{
				numa = rand() % 100;
			} while (0 == numa);
			do{
				numb = rand() % 100;
			} while (0 == numb||numb == numa);
			if (numa > numb)
			{
				tmp = numa;
				numa = numb;
				numb = tmp;
			}
			do{
				numc = rand() % 100;
			} while (0 == numc);
			do{
				numd = rand() % 100;
			} while (0 == numd||numd == numc);
			if (numc > numd)
			{
				tmp = numc;
				numc = numd;
				numd = tmp;
			}
			cout << numa << " ";
			if (numa < 10)                            //打印
				cout << " ";
			cout << numc<< endl << "—" << sign << "—=" << endl << numb ;
			if (numb < 10)
				cout << " ";
			cout<< " " << numd << endl << endl;
			break;
		}
	}
	return 0;
}
