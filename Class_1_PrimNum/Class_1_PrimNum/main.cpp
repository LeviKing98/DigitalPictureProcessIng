
#include "stdlib.h"
#include "iostream"

using namespace std;

int CheckPrimeNum(int x)
{
	int i;
	for (i = 2; i <= x / 2; i++)
	{
		if (x%i == 0)
			return 0;
	}
	return 1;
}

int main()
{
	int i;
	for (i = 2; i < 100; i++)
	{
		if (CheckPrimeNum(i) == 1)
			cout << "The Number is " << i << endl;
	}
	system("pause");
}