#include <stdio.h>


int main(int argc, char const *argv[])
{
	printf("Hello pandy!\n");

	int ai = 0;
	float af  = 0.123;
	double bd = 123.34;
	// 64位sizeof  的结果是 4 4 8
	printf("sizeof int:%lu\n", sizeof(int));
	printf("sizeof float: %lu\n", sizeof(float));
	printf("sizeof double: %lu\n", sizeof(double));

	// 64位sizeof  的结果是 8
	char* p = "hello pandy";
	printf("sizeof char *:%lu\n", sizeof(p));

	return 0;
}
