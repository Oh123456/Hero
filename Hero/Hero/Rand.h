#pragma once

#include <iostream>	
#include <ctime>


inline void Setsrand()
{
	srand((unsigned)time(NULL));
}

// Range범위의 랜덤값
inline int RandRange(int Range, int start = 0)
{
	return rand() % Range + start;
}

// A~B 사이의 값랜덤값
inline int RandRangeAToB(int A, int B, int start = 0)
{
	int min = 0;
	int max = 0;
	if (A > B)
	{
		max = A;
		min = B;
	}
	else
	{
		max = B;
		min = A;
	}
	if (start == 0)
		return rand() % (max - min + 1) + min;
	else
		return rand() % (max - min + 1) + start;
}


inline bool RandomInCount()
{
	int Num = RandRange(10);
	if (Num == 3)
		return true;
	return false;
}