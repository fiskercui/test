#include <stdio.h>
#include <stdlib.h>
#include <string>


using namespace std;

#define MAX_LEN 1024

static char s_temp[MAX_LEN];

std::string FloatToChar10(float f)
{
    snprintf(s_temp, MAX_LEN, "%f", f);
    return (std::string) s_temp; 
}

std::string IntToChar10(int num)
{
	snprintf(s_temp, MAX_LEN, "%d", num);
	return (std::string) s_temp;
}

std::string FloatArrayToString(float f[], int size)
{
	printf("convertFloatArrayToString\n");
	std::string sTemp;
	for (int i = 0; i < size; ++i)
	{
		sTemp += "[" + IntToChar10(i) + "]:" + FloatToChar10(f[i]) + ",";
	}
	return sTemp;
}

void convertFloatToString(float f[], int size)
{
	printf("function convertFloatToString\n");
	char temp[MAX_LEN] = {'\0'};
	for(int i = 0; i < size; i++)
	{
		snprintf(&temp[i], 2, "%d", (int)f[i]);
		// printf("%d\n", );
	}
	for (int i = 0; i < MAX_LEN; ++i)
	{
		printf("%c", temp[i]);
	}
	printf("\n");
}


int main(int argc, char const *argv[])
{
	/* code */
	char temp[MAX_LEN] = {'\0'};

	float fTest = 3.1415926;

	snprintf(temp, MAX_LEN, "%f", fTest);
	printf("float start\n");
	for (int i = 0; i < MAX_LEN; ++i)
	{
		printf("%c", temp[i]);
	}
	printf("\nfloat end\n");


	memset(temp, 0 , MAX_LEN);
	snprintf(temp, MAX_LEN, "%d", (int)fTest);
	printf("int start\n");
	for (int i = 0; i < MAX_LEN; ++i)
	{
		printf("%c", temp[i]);
	}
	printf("\nint end\n");


	printf("testfloat\n");
	float fTemp[] = {
		0.2f, 0.1f, 0.3f,1.2f,2.5f,3.5656556f
	};
	std::string s = FloatArrayToString(fTemp, sizeof(fTemp)/sizeof(float));
	printf("FloatArrayToString:%s\n", s.c_str());

	return 0;
}