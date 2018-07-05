#include <stdio.h>
#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<fstream>
#include<future>
#include<stack>
#include<string>
#include"myvector.h"
#include<set>
#include<unordered_set>
#include < map>
#include<istream>
#include<iterator>
using namespace std;


class singleton1
{

	static singleton1 * instance;
	singleton1()
	{
		cout << "constructor called";
	}
	static void init()
	{
		cout << "init called";
		instance = new singleton1();
	}
public:
	static std::once_flag ofonc;
	static singleton1 * Instance()
	{
		std::call_once(ofonc, &singleton1::init);
		return instance;
	}

};
singleton1* singleton1::instance = NULL;
once_flag singleton1::ofonc;