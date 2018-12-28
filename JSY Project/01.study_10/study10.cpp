#include<stdio.h>

int main(void)
{
	unsigned char eightBitVal = 0x57;
	unsigned char fourBitVal1, fourBitval2;
	fourBitVal1 = eightBitVal >> 4;
	fourBitval2 |= eightBitVal& 0x0F;
	printf("%x, %x -> %x\n", eightBitVal, fourBitVal1, fourBitval2);

	getchar();

	return 0;

}