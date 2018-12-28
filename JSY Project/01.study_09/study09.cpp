#include<stdio.h>

int main(void)
{
	unsigned char fourBitVal1 = 0x05, fourBitval2 = 0x07;
	unsigned char eightBitVal;
	eightBitVal = fourBitVal1 << 4;
	eightBitVal |= fourBitval2;
	printf("%x, %x -> %x\n", fourBitVal1, fourBitval2, eightBitVal);

	getchar();

	return 0;

}