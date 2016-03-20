# githubCode
//2016/03/06
//打印100以内四则运算式，包含真分数。
//2016/03/11
//新增：题目避免重复；可定制（数量/打印方式）；可以控制以下参数：
//是否有乘除法；是否有括号（最多可以支持十个数参与计算）；数值范围；
//加减有无负数；除法有无余数；
#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<random>
#include<cmath>
#include<ctime>
#include<conio.h>
#include<windows.h>
using namespace std;

int NUM_equation = 0;               //打印数量
bool PrintToFile;               //是否输出到文件
bool HasMultAndDivi;            //是否有乘除法
bool HasBrackets;               //是否有括号
bool HasNegative;               //加减是否有负数
bool HasRemainder;              //除法是否有余数
int MaxOfRange = 100;                 //数值范围上限
int MinOfRange = -100;                 //数值范围下限

//int NUM_equation = 20;               //打印数量
//bool PrintToFile = false;               //是否输出到文件
//bool HasMultAndDivi = true;            //是否有乘除法
//bool HasBrackets = true;               //是否有括号
//bool HasNegative = true;               //加减是否有负数
//bool HasRemainder = true;              //除法是否有余数
//int MaxOfRange = 100;                 //数值范围上限
//int MinOfRange = -100;                 //数值范围下限
default_random_engine generator;
uniform_int_distribution<int> distribution(MinOfRange, MaxOfRange);
struct equation{                //定义结构体“算式”equation

	double value;               //值value，用于存算式的值
	int num;                    //当前算式为num元运算
	bool isFraction;            //标记是否为分数
	string shape;               //形式shape，用于存算式形式
}Equation[9999];

void MakeBrackets(equation*);

void absoluteValue(int &numfirst, int &numsecond)
{
	int tonumf;          //第一个数的绝对值
	int tonums;
	int flag_1;
	int flag_2;
	int temp;
	if (numfirst < 0)
	{
		tonumf = 0 - numfirst;
		flag_1 = -1;
	}
	else
	{
		tonumf = numfirst;
		flag_1 = 1;
	}
	if (numsecond < 0)
	{
		tonums = 0 - numsecond;
		flag_2 = -1;
	}
	else
	{
		tonums = numsecond;
		flag_2 = 1;
	}
	if (tonums < tonumf)
	{
		temp = tonumf;
		tonumf = tonums;
		tonums = temp;
	}
	int i;
	for (i = tonumf; i > 0; i--)
	{
		if (tonumf%i == 0 && tonums%i == 0)
		{
			break;
		}
	}
	if (i)
	{
		numfirst = tonumf / i;
		numsecond = tonums / i;
	}
	else
	{
		numfirst = tonumf;
		numsecond = tonums;
	}
	if (flag_1*flag_2 < 0)
	{
		numfirst = 0 - numfirst;
	}
}

void getRequirement()                    //输入要求
{
	string buffer;
	bool flag_NUM_right = false;
	do{
		cout << "请选择打印数量（1-9999整数）：";
		cin >> buffer;
		int i;
		if (buffer.length() < 5)
		{
			for (i = 0; i < buffer.length(); i++)                 //判断是否为数字
			{
				if (buffer[i] < 48 || buffer[i]>57)
				{
					break;                                      //不是数字则跳出
				}
			}
			if (i == buffer.length())                             //如果没有跳出（都是数字）
			{
				if (buffer[0] != '0')
				{
					for (i = 0; i < buffer.length(); i++)         //字符转为整形
					{
						NUM_equation += (buffer[i] - 48)*pow(10, buffer.length() - 1 - i);
					}
					flag_NUM_right = true;
				}
			}
		}
	} while (!flag_NUM_right);

	bool flag_Print_right = false;
	do{
		cout << "请选择输出方式（1.屏幕/2.文件）：";
		switch (getche())
		{
		case 49:                                        //'1'
			PrintToFile = false;
			flag_Print_right = true;
			cout << endl;
			break;
		case 50:                                        //'2'
			PrintToFile = true;
			flag_Print_right = true;
			cout << endl;
			break;
		default:
			cout << endl;
		}
	} while (!flag_Print_right);

	bool flag_MultAndDivi_right = false;
	do{
		cout << "请选择是否有乘除法（Y.有/N.无）：";
		switch (getche())
		{
		case 78:                                                   //'N'
			HasMultAndDivi = false;
			flag_MultAndDivi_right = true;
			cout << endl;
			break;
		case 89:                                                   //'Y'
			HasMultAndDivi = true;
			flag_MultAndDivi_right = true;
			cout << endl;
			break;
		default:
			cout << endl;
		}
	} while (!flag_MultAndDivi_right);


	bool flag_Brackets_right = false;
	do{
		cout << "请选择是否有括号（Y.有/N.无）：";
		switch (getche())
		{
		case 78:                                                   //'N'
			HasBrackets = false;
			flag_Brackets_right = true;
			cout << endl;
			break;
		case 89:                                                   //'Y'
			HasBrackets = true;
			flag_Brackets_right = true;
			cout << endl;
			break;
		default:
			cout << endl;
		}
	} while (!flag_Brackets_right);
	/////////////////////////////////
	string bufferforRage;
	bool flag_Rage_right = false;
	bool isNegative;
	MaxOfRange = 0;
	MinOfRange = 0;
	do{
		cout << "请规定数值范围（整数-99999~99999）：上限为：";
		cin >> bufferforRage;
		int i;
		if (bufferforRage[0] == '-')                                         //若可能为负数
		{
			if (bufferforRage.length() < 7)
			{
				for (i = 1; i < bufferforRage.length(); i++)                 //判断是否为数字
				{
					if (bufferforRage[i] < 48 || bufferforRage[i]>57)
					{
						break;                                      //不是数字则跳出
					}
				}
				if (i == bufferforRage.length())                             //如果没有跳出（都是数字）
				{
					if (bufferforRage[0] != '0')
					{
						for (i = 1; i < bufferforRage.length(); i++)         //字符转为整形
						{
							MaxOfRange -= (bufferforRage[i] - 48)*pow(10, bufferforRage.length() - i - 1);
						}
						flag_Rage_right = true;
					}
				}
			}
		}
		if (bufferforRage[0] != '-')                                         //若可能为正数
		{
			if (bufferforRage.length() < 6)
			{
				for (i = 0; i < bufferforRage.length(); i++)                 //判断是否为数字
				{
					if (bufferforRage[i] < 48 || bufferforRage[i]>57)
					{
						break;                                      //不是数字则跳出
					}
				}
				if (i == bufferforRage.length())                             //如果没有跳出（都是数字）
				{
					if (bufferforRage[0] != '0')
					{
						for (i = 0; i < bufferforRage.length(); i++)         //字符转为整形
						{
							MaxOfRange += (bufferforRage[i] - 48)*pow(10, bufferforRage.length() - 1 - i);
						}
						flag_Rage_right = true;
					}
					else
					{
						MaxOfRange = 0;
						flag_Rage_right = true;
					}
				}
			}
		}

	} while (!flag_Rage_right);

	flag_Rage_right = false;
	do{
		cout << "下限为：";
		cin >> bufferforRage;
		int i;
		if (bufferforRage[0] == '-')                                         //若可能为负数
		{
			if (bufferforRage.length() < 7)
			{
				for (i = 1; i < bufferforRage.length(); i++)                 //判断是否为数字
				{
					if (bufferforRage[i] < 48 || bufferforRage[i]>57)
					{
						break;                                      //不是数字则跳出
					}
				}
				if (i == bufferforRage.length())                             //如果没有跳出（都是数字）
				{
					if (bufferforRage[0] != '0')
					{
						for (i = 1; i < bufferforRage.length(); i++)         //字符转为整形
						{
							MinOfRange -= (bufferforRage[i] - 48)*pow(10, bufferforRage.length() - i - 1);
						}
						if (MinOfRange < MaxOfRange)
						{
							flag_Rage_right = true;
						}
						else
						{
							MinOfRange = 0;
						}
					}
				}
			}
		}
		if (bufferforRage[0] != '-')                                         //若可能为正数
		{
			if (bufferforRage.length() < 6)
			{
				for (i = 0; i < bufferforRage.length(); i++)                 //判断是否为数字
				{
					if (bufferforRage[i] < 48 || bufferforRage[i]>57)
					{
						break;                                      //不是数字则跳出
					}
				}
				if (i == bufferforRage.length())                             //如果没有跳出（都是数字）
				{
					if (bufferforRage[0] != '0')
					{
						for (i = 0; i < bufferforRage.length(); i++)         //字符转为整形
						{
							MinOfRange += (bufferforRage[i] - 48)*pow(10, bufferforRage.length() - 1 - i);
						}
					}
					else
					{
						MinOfRange = 0;
					}
					if (MinOfRange < MaxOfRange)
					{
						flag_Rage_right = true;
					}
					else
					{
						MinOfRange = 0;
					}
				}
			}
		}

	} while (!flag_Rage_right);

	///////////////////////////////////


	bool flag_Negative_right = false;
	do{
		cout << "请选择加减是否有负数（Y.有/N.无）：";
		switch (getche())
		{
		case 78:                                                   //'N'
			HasNegative = false;
			flag_Negative_right = true;
			cout << endl;
			break;
		case 89:                                                   //'Y'
			HasNegative = true;
			flag_Negative_right = true;
			cout << endl;
			break;
		default:
			cout << endl;
		}
	} while (!flag_Negative_right);

	if (HasMultAndDivi)
	{
		bool flag_Remainder_right = false;
		do{
			cout << "请选择除法是否有余数（Y.有/N.无）：";
			switch (getche())
			{
			case 78:                                                   //'N'
				HasRemainder = false;
				flag_Remainder_right = true;
				cout << endl;
				break;
			case 89:                                                   //'Y'
				HasRemainder = true;
				flag_Remainder_right = true;
				cout << endl;
				break;
			default:
				cout << endl;
			}
		} while (!flag_Remainder_right);
	}
}

void CreateEquation()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(MinOfRange, MaxOfRange);
	for (int i = 0; i < NUM_equation; i++)
	{
		if (rand() % 2 == 0)
		{
			Equation[i].isFraction = false;
		}
		else
		{
		 	Equation[i].isFraction = true;
		}
		string middle;
		char sign;                                           //生成初始运算符
		do
		{
			switch (rand() % 4)
			{
			case 0:
				sign = '+';
				break;
			case 1:
				sign = '-';
				break;
			case 2:
				sign = '*';
				break;
			case 3:
				sign = '/';
				break;
			}
		} while ((sign == '/' || sign == '*') && !HasMultAndDivi);
		bool wrong = false;
		double value = 0;
		do
		{
			wrong = false;
			if (!Equation[i].isFraction)                        //生成运算数-整数
			{
				int numFormer;
				int numLatter;
				numFormer = distribution(generator);
				do
				{
					numLatter = distribution(generator);
				} while (numLatter == 0 && sign == '/');
				char strnumFormer[7] = { '0' };
				itoa(numFormer, strnumFormer, 10);
				char strnumLatter[7] = { '0' };
				itoa(numLatter, strnumLatter, 10);
				if (sign == '+' || sign == '-')                            //加减
				{
					if (HasNegative)
					{
						if (sign == '+')
						{
							value = (double)numFormer + (double)numLatter;
						}
						else
						{
							value = (double)numFormer - (double)numLatter;
						}
						if (value<MinOfRange || value>MaxOfRange)
						{
							wrong = true;
						}
						else
						{
							middle = strnumFormer;
							middle = middle + sign;
							if (numLatter < 0)
							{
								middle = middle + '(' + strnumLatter + ')';
							}
							else
							{
								middle = middle + strnumLatter;
							}

							//Equation[i].shape = strnumFormer + sign;
							//Equation[i].shape = Equation[i].shape + strnumLatter;
						}
					}
					else
					{
						if (numFormer < 0 || numLatter < 0)
						{
							wrong = true;
						}
						else
						{
							if (sign == '+')
							{
								value = (double)numFormer + (double)numLatter;
							}
							else
							{
								value = (double)numFormer - (double)numLatter;
							}
							if (value<MinOfRange || value>MaxOfRange || value < 0)
							{
								wrong = true;
							}
							else
							{
								middle = strnumFormer;
								middle = middle + sign;
								middle = middle + strnumLatter;
								//Equation[i].shape = strnumFormer + sign;
								//Equation[i].shape = Equation[i].shape + strnumLatter;
							}
						}
					}
				}
				else if (sign == '*')                                                     //乘
				{
					value = (double)numFormer*(double)numLatter;
					if (value<MinOfRange || value>MaxOfRange)
					{
						wrong = true;
					}
					else
					{
						middle = strnumFormer;
						middle = middle + sign;
						if (numLatter < 0)
						{
							middle = middle + '(' + strnumLatter + ')';
						}
						else
						{
							middle = middle + strnumLatter;
						}
						//Equation[i].shape = strnumFormer + sign;
						//Equation[i].shape = Equation[i].shape + strnumLatter;
					}
				}
				else                                                                  //除
				{
					if (HasRemainder)
					{
						value = (double)numFormer / (double)numLatter;
						if (value<MinOfRange || value>MaxOfRange)
						{
							wrong = true;
						}
						else
						{
							middle = strnumFormer;
							middle = middle + sign;
							if (numLatter < 0)
							{
								middle = middle + '(' + strnumLatter + ')';
							}
							else
							{
								middle = middle + strnumLatter;
							}
							//Equation[i].shape = strnumFormer + sign;
							//Equation[i].shape = Equation[i].shape + strnumLatter;
						}
					}
					else
					{
						if (numFormer%numLatter != 0)
						{
							wrong = true;
						}
						else
						{
							value = (double)numFormer / (double)numLatter;
							if (value<MinOfRange || value>MaxOfRange)
							{
								wrong = true;
							}
							else
							{
								middle = strnumFormer;
								middle = middle + sign;
								if (numLatter < 0)
								{
									middle = middle + '(' + strnumLatter + ')';
								}
								else
								{
									middle = middle + strnumLatter;
								}
								//Equation[i].shape = strnumFormer + sign;
								//Equation[i].shape = Equation[i].shape + strnumLatter;
							}
						}
					}
				}
			}
			else                                               //生成运算数-分数
			{
				int NumeratorFormer;
				int NumeratorLatter;
				int DenominatorFormer;
				int DenominatorLatter;
				do
				{
					NumeratorFormer = distribution(generator);
				} while (NumeratorFormer == 0);
				do
				{
					DenominatorFormer = distribution(generator);
				} while (DenominatorFormer == 0 || DenominatorFormer == NumeratorFormer);
				absoluteValue(NumeratorFormer, DenominatorFormer);
				do
				{
					NumeratorLatter = distribution(generator);
				} while (NumeratorLatter == 0);
				do
				{
					DenominatorLatter = distribution(generator);
				} while (DenominatorLatter == 0 || DenominatorLatter == NumeratorLatter);
				absoluteValue(NumeratorLatter, DenominatorLatter);
				char strNF[7];
				itoa(NumeratorFormer, strNF, 10);
				char strDF[7];
				itoa(DenominatorFormer, strDF, 10);
				char strNL[7];
				itoa(NumeratorLatter, strNL, 10);
				char strDL[7];
				itoa(DenominatorLatter, strDL, 10);
				if (sign == '+' || sign == '-')                                          //加减
				{
					if (HasNegative)
					{
						if (sign == '+')
						{
							value = (double)NumeratorFormer / (double)DenominatorFormer + (double)NumeratorLatter / (double)DenominatorLatter;
						}
						else
						{
							value = (double)NumeratorFormer / (double)DenominatorFormer - (double)NumeratorLatter / (double)DenominatorLatter;
						}
						if (value<MinOfRange || value>MaxOfRange)
						{
							wrong = true;
						}
						else
						{
							middle = strNF;
							middle = middle + 'd';
							middle = middle + strDF;
							middle = middle + sign;
							middle = middle + strNL;
							middle = middle + 'd';
							middle = middle + strDL;
							//Equation[i].shape = strNF + 'd';
							//Equation[i].shape = Equation[i].shape + strDF + sign + strNL + 'd' + strDL;
						}
					}
					else
					{
						if (NumeratorFormer < 0 || NumeratorLatter < 0)
						{
							wrong = true;
						}
						else
						{
							if (sign == '+')
							{
								value = (double)NumeratorFormer / (double)DenominatorFormer + (double)NumeratorLatter / (double)DenominatorLatter;
							}
							else
							{
								value = (double)NumeratorFormer / (double)DenominatorFormer - (double)NumeratorLatter / (double)DenominatorLatter;
							}
							if (value<MinOfRange || value>MaxOfRange || value<0)
							{
								wrong = true;
							}
							else
							{
								middle = strNF;
								middle = middle + 'd';
								middle = middle + strDF;
								middle = middle + sign;
								middle = middle + strNL;
								middle = middle + 'd';
								middle = middle + strDL;
								//Equation[i].shape = strNF + 'd';
								//Equation[i].shape = Equation[i].shape + strDF + sign + strNL + 'd' + strDL;
							}
						}
					}
				}
				else                                                         //乘除
				{
					if (sign == '*')
					{
						value = ((double)NumeratorFormer / (double)DenominatorFormer) * ((double)NumeratorLatter / (double)DenominatorLatter);
					}
					else
					{
						value = ((double)NumeratorFormer / (double)DenominatorFormer) / ((double)NumeratorLatter / (double)DenominatorLatter);
					}
					if (value<MinOfRange || value>MaxOfRange)
					{
						wrong = true;
					}
					else
					{
						middle = strNF;
						middle = middle + 'd';
						middle = middle + strDF;
						middle = middle + sign;
						middle = middle + strNL;
						middle = middle + 'd';
						middle = middle + strDL;
						//Equation[i].shape = strNF + 'd';
						//Equation[i].shape = Equation[i].shape + strDF + sign + strNL + 'd' + strDL;
					}
				}
			}
		} while (wrong);
		Equation[i].shape = middle;
		Equation[i].value = value;
		Equation[i].num = 2;
		if (HasBrackets)
		{
			if (rand() % 5 != 0)
			{

				Equation[i].shape = '(' + Equation[i].shape + ')';
				equation *E = &Equation[i];
				MakeBrackets(E);

			}
		}
		for (int v = 0; v < i; v++)
		{
			if (Equation[i].shape == Equation[v].shape)
			{
				Equation[i].shape = "";
				Equation[i].value = 0;
				Equation[i].num = 0;
				i = i - 1;
				break;
			}

		}
		//cout << Equation[i].shape << endl;///////////////////////////////////////////////////////
	}
}

void MakeBrackets(equation *thisEquation)                        //加括号
{

	bool wrong = false;
	double value=0;
	string interForShape="";
	do{
		interForShape = (*thisEquation).shape;
		wrong = false;
		if ((*thisEquation).isFraction)                          //若为分数运算
		{
			int numerator;
			int denominator;
			do{
				numerator = distribution(generator);
			} while (numerator == 0);
			do{
				denominator = distribution(generator);
			} while (denominator == 0 || denominator == numerator);
			absoluteValue(numerator, denominator);
			/*if (numerator > denominator)
			{
				int tem;
				tem = numerator;
				numerator = denominator;
				denominator = tem;
			}*/
			char strNumerator[7];
			char strDenominator[7];
			itoa(numerator, strNumerator, 10);
			itoa(denominator, strDenominator, 10);
			switch (rand() % 8)
			{
			case 0:
				if (HasNegative)
				{
					value = (*thisEquation).value + (double)numerator / (double)denominator;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '+' + interForShape;
					interForShape = strDenominator + interForShape;
					interForShape = 'd' + interForShape;
					interForShape = strNumerator + interForShape;
				}
				else
				{
					if (numerator > 0 && denominator > 0)
					{
						value = (*thisEquation).value + (double)numerator / (double)denominator;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = '+' + interForShape;
						interForShape = strDenominator + interForShape;
						interForShape = 'd' + interForShape;
						interForShape = strNumerator + interForShape;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 1:
				if (HasNegative)
				{
					value = (*thisEquation).value + (double)numerator / (double)denominator;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '+';
					interForShape = interForShape + strNumerator;
					interForShape = interForShape + 'd';
					interForShape = interForShape + strDenominator;
				}
				else
				{
					if (numerator > 0 && denominator > 0)
					{
						value = (*thisEquation).value + (double)numerator / (double)denominator;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = interForShape + '+';
						interForShape = interForShape + strNumerator;
						interForShape = interForShape + 'd';
						interForShape = interForShape + strDenominator;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 2:
				if (HasNegative)
				{
					value = (double)numerator / (double)denominator - (*thisEquation).value;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '-' + interForShape;
					interForShape = strDenominator + interForShape;
					interForShape = 'd' + interForShape;
					interForShape = strNumerator + interForShape;
				}
				else
				{
					if (numerator > 0 && denominator > 0)
					{
						value = (double)numerator / (double)denominator - (*thisEquation).value;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = '-' + interForShape;
						interForShape = strDenominator + interForShape;
						interForShape = 'd' + interForShape;
						interForShape = strNumerator + interForShape;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 3:
				if (HasNegative)
				{
					value = (*thisEquation).value - (double)numerator / (double)denominator;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '-';
					interForShape = interForShape + strNumerator;
					interForShape = interForShape + 'd';
					interForShape = interForShape + strDenominator;
				}
				else
				{
					if (numerator > 0 && denominator > 0)
					{
						value = (double)numerator / (double)denominator - (*thisEquation).value;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = interForShape + '-';
						interForShape = interForShape + strNumerator;
						interForShape = interForShape + 'd';
						interForShape = interForShape + strDenominator;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 4:
				if (HasMultAndDivi)
				{
					value = (double)numerator / (double)denominator * (*thisEquation).value;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '*' + interForShape;
					interForShape = strDenominator + interForShape;
					interForShape = 'd' + interForShape;
					interForShape = strNumerator + interForShape;
				}
				else
				{
					wrong = true;
				}
				break;
			case 5:
				if (HasMultAndDivi)
				{
					value = (*thisEquation).value * (double)numerator / (double)denominator;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '*';
					interForShape = interForShape + strNumerator;
					interForShape = interForShape + 'd';
					interForShape = interForShape + strDenominator;
				}
				else
				{
					wrong = true;
				}
				break;
			case 6:
				if (HasMultAndDivi)
				{
					value = (double)numerator / (double)denominator / (*thisEquation).value;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '/' + interForShape;
					interForShape = strDenominator + interForShape;
					interForShape = 'd' + interForShape;
					interForShape = strNumerator + interForShape;
				}
				else
				{
					wrong = true;
				}
				break;
			case 7:
				if (HasMultAndDivi)
				{
					value = (*thisEquation).value / ((double)numerator / (double)denominator);
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '/';
					interForShape = interForShape + strNumerator;
					interForShape = interForShape + 'd';
					interForShape = interForShape + strDenominator;
				}
				else
				{
					wrong = true;
				}
				break;
			}
		}
		else                                                       //若为整数运算
		{
			int integer;
			integer = distribution(generator);
			char strInteger[7];
			itoa(integer, strInteger, 10);
			switch (rand() % 8)
			{
			case 0:
				if (HasNegative)
				{
					value = (*thisEquation).value + (double)integer;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '+' + interForShape;
					if (integer < 0)
					{
						//interForShape = '(' + strInteger + ')' + interForShape;
						interForShape = ')' + interForShape;
						interForShape = strInteger + interForShape;
						interForShape = '(' + interForShape;
					}
					else
					{
						interForShape = strInteger + interForShape;
					}
				}
				else
				{
					if (integer > 0)
					{
						value = (*thisEquation).value + (double)integer;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = '+' + interForShape;
						interForShape = strInteger + interForShape;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 1:
				if (HasNegative)
				{
					value = (*thisEquation).value + (double)integer;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '+';
					if (integer < 0)
					{
						//interForShape = interForShape + '(' + strInteger + ')';
						interForShape = interForShape + '(';
						interForShape = interForShape + strInteger;
						interForShape = interForShape + ')';
					}
					else
					{
						interForShape = interForShape + strInteger;
					}
				}
				else
				{
					if (integer > 0)
					{
						value = (*thisEquation).value + (double)integer;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = interForShape + '+';
						interForShape = interForShape + strInteger;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 2:
				if (HasNegative)
				{
					value = (double)integer - (*thisEquation).value;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '-' + interForShape;
					if (integer < 0)
					{
						//interForShape = '(' + strInteger + ')' + interForShape;
						interForShape = ')' + interForShape;
						interForShape = strInteger + interForShape;
						interForShape = '(' + interForShape;
					}
					else
					{
						interForShape = strInteger + interForShape;
					}
				}
				else
				{
					if (integer > 0)
					{
						value = (double)integer - (*thisEquation).value;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = '-' + interForShape;
						interForShape = strInteger + interForShape;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 3:
				if (HasNegative)
				{
					value = (*thisEquation).value - (double)integer;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '-';
					if (integer < 0)
					{
						//interForShape = interForShape + '(' + strInteger + ')';
						interForShape = interForShape + '(';
						interForShape = interForShape + strInteger;
						interForShape = interForShape + ')';
					}
					else
					{
						interForShape = interForShape + strInteger;
					}
				}
				else
				{
					if (integer > 0)
					{
						value = (*thisEquation).value - (double)integer;
						if (value > MaxOfRange || value < MinOfRange || value < 0)
						{
							wrong = true;
							break;
						}
						interForShape = interForShape + '-';
						interForShape = interForShape + strInteger;
					}
					else
					{
						wrong = true;
						break;
					}
				}
				break;
			case 4:
				if (HasMultAndDivi)
				{
					value = (double)integer * (*thisEquation).value;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = '*' + interForShape;
					if (integer < 0)
					{
						//interForShape = '(' + strInteger + ')' + interForShape;
						interForShape = ')' + interForShape;
						interForShape = strInteger + interForShape;
						interForShape = '(' + interForShape;
					}
					else
					{
						interForShape = strInteger + interForShape;
					}
				}
				else
				{
					wrong = true;
				}
				break;
			case 5:
				if (HasMultAndDivi)
				{
					value = (*thisEquation).value * (double)integer;
					if (value > MaxOfRange || value < MinOfRange)
					{
						wrong = true;
						break;
					}
					interForShape = interForShape + '*';
					if (integer < 0)
					{
						//interForShape = interForShape + '(' + strInteger + ')';
						interForShape = interForShape + '(';
						interForShape = interForShape + strInteger;
						interForShape = interForShape + ')';
					}
					else
					{
						interForShape = interForShape + strInteger;
					}
				}
				else
				{
					wrong = true;
				}
				break;
			case 6:
				if (HasMultAndDivi)
				{
					if ((*thisEquation).value<1E-7&&(*thisEquation).value>-(1E-7))          //若除数为0
					{
						wrong = true;
						break;
					}
					if (HasRemainder)
					{
						value = (double)integer / (*thisEquation).value;
						if (value > MaxOfRange || value < MinOfRange)
						{
							wrong = true;
							break;
						}
						interForShape = '/' + interForShape;
						if (integer < 0)
						{
							//interForShape = '(' + strInteger + ')' + interForShape;
							interForShape = ')' + interForShape;
							interForShape = strInteger + interForShape;
							interForShape = '(' + interForShape;
						}
						else
						{
							interForShape = strInteger + interForShape;
						}
					}
					else
					{
						if ((*thisEquation).value - int((*thisEquation).value) > 1E-7 || (*thisEquation).value - int((*thisEquation).value) < -(1E-7))
						{
							wrong = true;
							break;
						}
						if (integer%int((*thisEquation).value) > 1E-7 || integer%int((*thisEquation).value) < -(1E-7))
						{
							wrong = true;
							break;
						}
						else
						{////
							value = (double)integer / (*thisEquation).value;
							if (value > MaxOfRange || value < MinOfRange)
							{
								wrong = true;
								break;
							}
							interForShape = '/' + interForShape;
							if (integer < 0)
							{
								//interForShape = '(' + strInteger + ')' + interForShape;
								interForShape = ')' + interForShape;
								interForShape = strInteger + interForShape;
								interForShape = '(' + interForShape;
							}
							else
							{
								interForShape = strInteger + interForShape;
							}
						}
					}
				}
				else
				{
					wrong = true;
				}
				break;
			case 7:
				if (HasMultAndDivi)
				{
					if (0 == integer)          //若除数为0
					{
						wrong = true;
						break;
					}
					if (HasRemainder)
					{
						value = (*thisEquation).value / (double)integer;
						if (value > MaxOfRange || value < MinOfRange)
						{
							wrong = true;
							break;
						}
						interForShape = interForShape + '/';
						if (integer < 0)
						{
							//interForShape = interForShape + '(' + strInteger + ')';
							interForShape = interForShape + '(';
							interForShape = interForShape + strInteger;
							interForShape = interForShape + ')';
						}
						else
						{
							interForShape = interForShape + strInteger;
						}
					}
					else
					{
						if ((*thisEquation).value - int((*thisEquation).value) > 1E-7 || (*thisEquation).value - int((*thisEquation).value) < -(1E-7))
						{
							wrong = true;
							break;
						}
						if ((int((*thisEquation).value)) % integer > 1E-7 || (int((*thisEquation).value)) % integer < -(1E-7))
						{
							wrong = true;
							break;
						}
						else
						{////
							value = (*thisEquation).value / (double)integer;
							if (value > MaxOfRange || value < MinOfRange)
							{
								wrong = true;
								break;
							}
							interForShape = interForShape + '/';
							if (integer < 0)
							{
								//interForShape = interForShape + '(' + strInteger + ')';
								interForShape = interForShape + '(';
								interForShape = interForShape + strInteger;
								interForShape = interForShape + ')';
							}
							else
							{
								interForShape = interForShape + strInteger;
							}

						}
					}
				}
				else
				{
					wrong = true;
				}
				break;
			}
		}
	} while (wrong);
	(*thisEquation).shape = interForShape;
	(*thisEquation).value = value;
	(*thisEquation).num += 1;
	if (rand() % 2 > 0 && (*thisEquation).num < 10)
	{
		(*thisEquation).shape = '(' + (*thisEquation).shape + ')';
		MakeBrackets(thisEquation);
	}
}

void Print()
{
	int totalR=0;
	ofstream ofile;
	ofile.open("print.txt");
	for (int i = 0; i < NUM_equation; i++)
	{
		if (Equation[i].isFraction)
		{
			string line1 = "";
			string line2 = "";
			string line3 = "";
			bool Fin_Negative = false;
			bool Fin_Numerator = false;
			bool Fin_Denominator = false;
			int NumNumerator = 0;
			int NumDenominator = 0;
			for (int j = 0;j<Equation[i].shape.length(); j++)
			{
				if ((Equation[i].shape[j]<48 || Equation[i].shape[j]>57) && Equation[i].shape[j] != 'd'&& Equation[i].shape[j] != '-')
				{
					Fin_Denominator = true;
					Fin_Numerator = false;
					line1 = line1 + "   ";
					line2 = line2 + ' '+ Equation[i].shape[j] + ' ';
					line3 = line3 + "   ";
				}
				else if (Equation[i].shape[j] == '-')
				{
					if (j != 0 && (Equation[i].shape[j - 1] == '-' || Equation[i].shape[j - 1] == '+' || Equation[i].shape[j - 1] == '*' || Equation[i].shape[j - 1] == '/'))
					{
						line1 = line1 + '-';
						line2 = line2 + '-';
						line3 = line3 + ' ';
					}
					else
					{

						Fin_Denominator = true;
						Fin_Numerator = false;

						line1 = line1 + "   ";
						line2 = line2 + " - ";
						line3 = line3 + "   ";
					}
				}
				else if (Equation[i].shape[j] == 'd')
				{
					Fin_Numerator = true;
					Fin_Denominator = false;
					for (int k = 1;; k++)
					{
						//if ((Equation[i].shape[j + k]==NULL)||(Equation[i].shape[j + k] < 48 || Equation[i].shape[j + k] > 57))
						if ((j + k) > Equation[i].shape.length() || (Equation[i].shape[j + k] < 48 || Equation[i].shape[j + k] > 57))
						{
							NumDenominator = k - 1;
							break;
						}
					}
					for (int h = 1;; h++)
					{
						if ((j - h < 0) || (Equation[i].shape[j - h] < 48 || Equation[i].shape[j - h] > 57))
						{
							NumNumerator = h - 1;
							break;
						}
					}
					if (NumNumerator > NumDenominator)
					{
						for (int n = 0; n < NumNumerator - NumDenominator; n++)
						{
							line3 = line3 + ' ';
						}
						for (int n = 0; n < NumNumerator; n++)
						{
							line2 = line2 + '-';
						}
					}
					if (NumDenominator > NumNumerator)
					{
						for (int n = 0; n < NumDenominator - NumNumerator; n++)
						{
							line1 = line1 + ' ';
						}
						for (int n = 0; n < NumDenominator; n++)
						{
							line2 = line2 + '-';
						}
					}
					else
					{
						for (int n = 0; n < NumDenominator; n++)
						{
							line2 = line2 + '-';
						}
					}
				}
				else
				{
					if (!Fin_Numerator)
					{
						line1 = line1 + Equation[i].shape[j];
					}
					else if (!Fin_Denominator)
					{
						line3 = line3 + Equation[i].shape[j];
					}
				}
			}
			if (PrintToFile)
			{
				ofile << line1 << endl << line2 << endl << line3 << endl << endl;
			}
			//else
			//{
				cout << line1 << endl << line2 << endl << line3 << endl << endl;
			//}

		}
		else
		{
			if (PrintToFile)
			{
				ofile << Equation[i].shape << endl << endl;
			}
			//else
			//{
				cout << Equation[i].shape << endl << endl;
			//}
		}
		string buffer;
		bool Result_Right = true;
		int NumofDiv=0;
		int Numofdot = 0;
		int SpaceofDiv;
		cout << "结果:";
		cin >> buffer;
		if (!buffer.empty())
		{
			for (int m = 0; m < buffer.length(); m++)
			{
				if ((buffer[m] < 48 || buffer[m]>57) && buffer[m] != '/'&& buffer[m] != '.'&&buffer[m]=='-')
				{
					Result_Right = false;
					break;
				}
				if (buffer[m] == '/')
				{
					NumofDiv += 1;
					if (NumofDiv > 1)
					{
						Result_Right = false;
						break;
					}
					SpaceofDiv = m;
				}
				if (buffer[m] == '.')
				{
					Numofdot += 1;
					if (Numofdot > 1)
					{
						Result_Right = false;
						break;
					}
				}
			}
			if (Result_Right)
			{
				double result;
				if (NumofDiv == 1)
				{
					string strfor=buffer.substr(0,SpaceofDiv);
					string strlat = buffer.substr(SpaceofDiv+1,buffer.length()-SpaceofDiv-1);
					double former = atof(strfor.c_str());
					double latter = atof(strlat.c_str());
					if ((latter - 0) < 1E-7 && (latter - 0) > (-1E-7))
					{
						Result_Right = false;
						break;
					}
					result = former / latter;
				}
				else
				{
					result = atof(buffer.c_str());
				}
				if ((result - Equation[i].value) < 1E-2 && (result - Equation[i].value) > -(1E-2))
				{
					Result_Right = true;
				}
				else
				{
					Result_Right = false;
				}
			}
			if (Result_Right)
			{
				cout << "正确！" << endl << endl;
				totalR += 1;
			}
			else
			{
				cout << "错误！" << endl << endl;
			}
		}
		else
		{
			cout << "错误！" << endl << endl;
		}
	}
	ofile.close();
	cout << "共" << NUM_equation << "道题，其中答对了" << totalR << "道题。" << endl;
}

int main()
{
	system("mode con: cols=120 lines=40");
	srand(time(0));
	getRequirement();
	CreateEquation();
	Print();
	return 0;
}
