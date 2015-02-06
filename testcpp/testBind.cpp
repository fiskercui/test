#include <stdio.h>
#include <iostream>
#include <functional>

using namespace std;


#define CC_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CC_CALLBACK_1(__selector__, __target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1,##__VA_ARGS__)


class CObject
{

};

class CTarget
{
public:
	void onTestBind()
	{
		std::cout << "onTestBind" << std::endl;
	}
	void onTestBind1(int num)
	{
		std::cout << "onTestBind1:" << num << std::endl;
	}
};


class CSource:public CObject
{


};


void testBind(){
	CSource src;
	CTarget dst;
	auto callback = CC_CALLBACK_0(CTarget::onTestBind, dst);
	callback();

	auto num = 456;
	auto callback2 = CC_CALLBACK_1(CTarget::onTestBind1, dst);
	callback2(num);
}




int sayHello(){
	std::cout << "say hello!" << std::endl;
	return 0;
}

int sayHelloWorld(char*h, char*w){
	std::cout << "say!" << h << " " << w << std::endl; 		
}


template<typename T>
class Func{
public:
	Func(T fun){
		if(!fun){
			throw "fun nullptr";
		}
		_fun = fun;
	}

	template<typename R>
	R call(){
		return _fun();
	}

	template<typename R, typename t1, typename t2>
	R call(t1 s1, t2 s2){
		return _fun(s1, s2);
	}

private:
	T _fun;


};

void testFun()
{
	Func<int (*)()> sayHelloFunc(sayHello);
	sayHelloFunc.call<int>();

	//注意与上面的写法的不同
	Func<std::function<int()>> sayHelloFunc2(sayHello);
	sayHelloFunc2.call<int>();

	Func<int (*)(char*s1, char*s2)> sayHelloWorld(sayHello);
	sayHelloWorld.call<int>("hello", "world");
}





int main(int argc, char const *argv[])
{
	/* code */
	testBind();
	testFun();
	return 0;
}