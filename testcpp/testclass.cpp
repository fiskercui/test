#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class CTestClass
{
public:
	CTestClass():m_a(10000)
	{
		printf("CTestClass()\n");
	}
	~CTestClass()
	{
		printf("~CTestClass()\n");
	}

	/* data */
public:
	int m_a;
};


int main(int argc, char const *argv[])
{
	/* code */
	CTestClass * pcls = new CTestClass;
	delete pcls;

	printf("m_a%d\n", pcls->m_a);
	delete pcls;
	
	return 0;
}