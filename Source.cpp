// C++ program to print DFS traversal from a given vertex in a  given graph
#include<iostream>
#include<list>
#include<vector>
#include"Cvehicle.h"
#include <map>
#include <thread>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <set>
#include<stack>
#include<stdarg.h>
using namespace std;

class Pizza
{
public :
	virtual string bake_pizza() = 0;
	~Pizza()
	{
		cout << "base class destructor called";
	}

};
class basic_pizza : public Pizza
{
public :
	string bake_pizza()
	{
		return  "pizza base is prepared";
	}
};
class PizzaDecorator : public Pizza
{
	
public :
	std::unique_ptr<Pizza> p;
	PizzaDecorator(std::unique_ptr<Pizza> &&p1) : p (std::move(p1))
	{
		
	}

};
class ChikenDecorator : public PizzaDecorator
{
public :
	ChikenDecorator(std::unique_ptr<Pizza> &&p1) : PizzaDecorator(std::move(p1))
	{
		
	}
	string bake_pizza()
	{
		return p->bake_pizza() + "chiken is added";
	}
};



class Base
{
public:
	int i = 5;
	virtual void  init(int k)
	{
		i = k;
		cout << "base init called";
	}
	Base(const Base &&t)
	{
		cout << "move construor called \n";
	}
	Base operator=(const Base & t)
	{
		cout << "assignment operator called \n";
	}
	
	Base(const Base & t)
	{
		cout << "copy constructer caleld \n";
		
	}
     Base(int i)
	{
		cout << "conversion operator called \n";
		init(i);
	}
	~Base()
	{
		cout << "destrucer called \n";
	}
	operator double()
	{
		return 10;
	}
	bool operator <(const Base &b) const
	{
		return false;
	}
friend	std::ostream & operator <<(std::ostream & os, const Base &b);
	
};
std::ostream & operator << (std::ostream & os, const Base &b)
{
	return os <<"this is in Base Class";
}
class Drived : public Base
{
public:
	const int c;
	const int & r;
	int t;
	void  init(int i)
	{
		cout << "drived init called";
		i = 50;
	}
	Drived():t(10),c(t), r(i),Base(3)
	{
		

		cout << "drived constructor called";
		init(10);
	}
	Drived(const Drived &d):t(d.t), c(d.c), r(d.r),Base(d)
	{
		cout << "Drived Copy Constructor called";
	}
};
struct WordGreaterComparator
{
	bool operator()(const string &left, const string &right) const
	{
		//return (left > right);
	}
};
vector<int>v;
auto functr = [](std::pair<string, int>ele1, std::pair<string, int> ele2) {return ele1.first > ele2.first; };

template<class T>
class abc
{
	typedef typename abc<T> x;
public:
	abc& operator=(const abc & a);
	
};
template<class T>
abc<T> & abc<T> :: operator=(const abc &a)
{
	return *this;
}
 template <class T> 
 class myarr
 {

 };
 template<class k,class v, template<class> class c = myarr>
 class map
 {
	 c<k> key;
	 c<v> value;
 };
 void mypritf(const char * ch, ...)
 {
	 const char * p;
	 for (p = ch; *p != '\0'; p++)
	 {

	 }
 }


 /* C++ Function to print leaders in an array */
 void printLeaders(int arr[], int size)
 {

 }
 int average(int n, ...)
 {
	 int sum = 0;
	 char * lst;
	 va_start(lst, n);
	 for (int i = 0; i < n; i++)
	 {
		 int x = va_arg(lst, int);
		 cout << x;
	 }
	 return 0;
 }
 template<typename T>
 bool compare(T a,T b)
 {
	 return a==b;
 }
 template<typename T, typename... Args>
 bool compare(T a,T b, Args... arg)
 {
	 return (a==b) && compare(arg...);
 }
 /* Driver program to test above function*/
 /*int main()
 {
	 int arr[] = { 16, 17, 4, 3, 5, 2 };
	 cout << average(5, 2, 3, 4, 5, 6);
	 bool b= compare(2, 2, 3, 4, 5, 6);

	 return 0;
 }*/
