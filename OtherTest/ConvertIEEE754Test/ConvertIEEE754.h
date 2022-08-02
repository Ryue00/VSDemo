#pragma once
/**
 * Copyright (c) 2021, INTRE All rights reserved.
 *
 * @Description: IEEE754 ����ת��
 * @author: RYue00
 * @date: 2021-10-20
 * @version: v1.1
 */

#include <iostream>
#include<math.h>

//========================================================================================
//                    IEEE754 --> float  ��16����IEEE754����ת���ɵ����ȸ�����
//========================================================================================

/**
 * ��ʮ����������������ת��Ϊ�����Ƹ�ʽ
 *
 * @param x
 * @return void
 */

void Decimal_Integer_To_Binary(int x, int* pa, int* pb)
{
	int m, i;
	for (i = 0;; i++)
	{
		*(pa + i) = x % 2;
		m = x / 2;
		x = m;
		if (m == 0)
		{
			// ��ʱ��i��ʵ�ʵ�λ��������1
			*(pa + 32) = i;  
			break;
		}
	}
	for (int j(0); j <= i; j++)
		*(pb + j) = *(pa + i - j);
}

/**
 * �����յ����ĸ��ֽڵ�IEEE754��ʽ����ת��������
 *
 * @param input  16������ 0x3e 80 00 00  --> 1.000000
 * @return �����ȸ�����
 */
float IEEE754_To_Float(int* input_result)
{
	// ���ĸ��ֽ�16������ ת�� int�� ����
	//int input_result[4] = { 0 };
	// input_result[0] = (input & 0xff000000) >> 24;
	// input_result[1] = (input & 0x00ff0000) >> 16;
	// input_result[2] = (input & 0x0000ff00) >> 8;
	// input_result[3] = (input & 0x000000ff) >> 0;
	
	int i = 0, j = 0, flag = 0, Exp_Part = 0, exp_part = 0;
	int	ieee754_result[33] = { 0 }, Decimal_Part[33] = { 0 };
	__int64 Integer_Part[33] = { 0 };
	float back_float = 0.0, multi0_5 = 1.0;
	int a[33], b[33], * pa = a, * pb = b;
	for (i = 0; i < 4; i++)
	{
		Decimal_Integer_To_Binary(*(input_result + i),pa,pb);
		flag = a[32];
		for (j = 0; j <= flag; j++)
			// ieee754_result[1]~ieee754_result[32]
			ieee754_result[i * 8 + (8 - flag + j)] = b[j];					
	}
	for (i = 2; i <= 9; i++)
	{
		Exp_Part += ieee754_result[i] * (1 << (9 - i));
	}
	// ȡ��ָ������λ����
	exp_part = Exp_Part - 127;											
	if (exp_part >= 0)
	{
		//1~32
		Integer_Part[1] = 1;											
		for (i = 0; i < exp_part; i++)
		{
			// ieee754_result[]ά�����ܳ���32��Integer_Part[]�Ͳ��ܳ���24
			if (i >= 23)  break;
			// װ����������
			Integer_Part[i + 2] = ieee754_result[i + 10];					
		}
		// �������ֵĸ���
		Integer_Part[32] = exp_part + 1;							
		if (exp_part < 23)
		{
			for (i = 0; i < 23 - exp_part; i++)
			{
				// 1~32,װ��С������
				Decimal_Part[i + 1] = ieee754_result[10 + exp_part + i];	
			}
			// С�����ֵĸ���
			Decimal_Part[32] = 23 - exp_part;								
		}
	}
	else
	{
		exp_part = -exp_part;
		// �������ֵĸ���
		Integer_Part[32] = 0;											
		for (i = 0; i < exp_part; i++)
		{
			// 1~32,װ��С������.��ȫ����0�������exp_part����1�滻
			Decimal_Part[i + 1] = 0;									
		}
		Decimal_Part[exp_part] = 1;
		for (i = 0; i < 23; i++)
		{
			// 1~32,װ��С������
			Decimal_Part[exp_part + i + 1] = ieee754_result[10 + i];		
		}
		// С�����ֵĸ���	
		Decimal_Part[32] = exp_part + 23;									
	}
	// �����������
	for (i = 1; i <= Integer_Part[32]; i++)								
	{
		// Integer_Part���ܳ���24
		if (i > 24) break;												
		back_float += Integer_Part[i] * (1 << (Integer_Part[32] - i));
	}
	// ���С������
	for (i = 1; i <= Decimal_Part[32]; i++)								
	{
		if (i > 24) break;
		for (j = 1; j <= i; j++)
		{
			multi0_5 *= 0.5;
		}
		back_float += Decimal_Part[i] * multi0_5;
		multi0_5 = 1.0;
	}

	if (1 == ieee754_result[1])
	{
		back_float = -back_float;
	}
	for (i = 0; i < 33; i++)
	{
		*(pa + i) = 0;
		*(pb + i) = 0;
	}
	return back_float;
}


//========================================================================================
//                     float --> IEEE754 �������ȸ���������ת����IEEE754����
//========================================================================================


// #include<iostream>
#include<math.h>
// using namespace std;
int aa[66], bb[66], * paa = aa, * pbb = bb;

/**
 * ��ʮ��������С������ת��Ϊ�����Ƹ�ʽ
 */
void Decimal_Decimal_To_Binary(float x)
{
	int i;
	for (i = 0; i < 66; i++)
	{
		*(paa + i) = 0;
		*(pbb + i) = 0;
	}
	double m = x * 2;
	for (i = 0; i <= 22; i++)
	{
		if (m < 1)
		{
			*(pbb + i) = 0;
			m *= 2;
			continue;
		}
		if (m >= 1)
		{
			*(pbb + i) = 1;
			m -= 1;
			if (0.0000001 >= m) break;
			m *= 2;

		}
	}
}
//***********test����*************//
void test(int ieee754_result[])
{
	IEEE754_To_Float(ieee754_result);
}



