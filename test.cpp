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
#include<queue>

using namespace std;

mutex mu;
class stack
{
	int * _data;
	std::mutex _mu;
public:
	void pop();
	int & top();
};
class Logfile
{
	mutex mu;
	fstream f;
public:
	Logfile()
	{
		f.open("c:\\log.txt");
	}
	void share_print(string id, int val)
	{
		lock_guard<mutex> locker(mu);
		f << id.c_str() << val << endl;
	}

}l;

ostream & operator<< (ostream & os, string str)
{
	return os<<str.c_str();
}
template <class... Ts> struct tuple {};

//template <class T, class... Ts>
//struct tuple<T, Ts...> : tuple<Ts...> {
//	tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {
//	}
//
//	T tail;
//};
////
//template<class A>
//class test1
//{
//
//};
//template<class B>
//class test2 : public test1<B>
//{
//
//};


void fun(const int &p)
{
	cout << "const fun";
}

class Dog
{
public:
	virtual ~ Dog()
	{
		cout << "Dog destroyed";
	}
	//virtual void bark() {}
};
class yellowdog : public Dog
{
public:
	int i;
	virtual ~yellowdog()
	{
		cout << "yellow dog destroyed";
	}
};
class Lock13
{
	public :
	Lock13()
	{
		
	}
	static void unlock(Lock13 * l)
	{
		
		cout << "lock unlocke";
	}
};
template <typename T>
class base
{
public: 
	void sendMessage()
{
	cout << " its from base class";
}
};
mutex m;
void printmsg(string str)
{
	
	m.lock();
	
	cout << str.c_str() << endl;
	
	m.unlock();
	
}
void function1234()
{
	for (int i = 0; i < 100; i++)
	{
		printmsg("from Thread ");
		for (int i = 0; i < 1000; i++);
	}
}
template<class T>
class Rational
{
public :
	T numi;
	T Deno;
	Rational(T numit = 0, T denot = 1)
	{
		numi = numit;
		Deno = denot;
	}
	friend Rational<T> operator *(const Rational<T> lhs, const Rational<T> rhs)
	{
		Rational<T> temp;
		temp.numi = lhs.numi * rhs.numi;
		return temp;
	}
};
//template <class T>
//Rational<T> operator *(const Rational<T> lhs, const Rational<T> rhs)
//{
//	Rational<T> temp;
//	temp.numi = lhs.numi * rhs.numi;
//	return temp;
//}
template<class fun1impl>
class b
{
public :
	void fun()
	{
	static_cast<fun1impl&>(*this).fun1();
		//fun1();
	}
void fun1()
	{
		cout << "in base class ";
	}
};
class d : public b<d>
{
public:
	void fun1()
	{
		cout << "in derived class";
	}
};
class newhandlerHolder
{
public:
	newhandlerHolder(new_handler classnewhandler_temp):classnewhandler(classnewhandler_temp)
	{

	}
	~newhandlerHolder()
	{
		set_new_handler(classnewhandler);
	}
private:
	new_handler classnewhandler;
};
class ydog
{
public:
	static void outofmemory()
	{
		cout << "ydog out of memory";
	}
	static void * operator new (size_t n) throw(std::bad_alloc);
	static std::new_handler set_new_handler(new_handler t);
private:
	static std::new_handler currenthandler;
};
new_handler ydog::set_new_handler(new_handler p)
{
	new_handler old = currenthandler;
	currenthandler = p;
	return old;
}
void * ydog::operator new(size_t n) throw(std::bad_alloc)
{
	newhandlerHolder h(std::set_new_handler(currenthandler));
	cout << "class opertor new called";
	return :: operator new(n);
}
 new_handler ydog::currenthandler = 0;
 template <int n>
 void add(int x)
 {
	 cout<<  n + x << endl;
 }
template<class t1,class t2>
void foreach1(t1 itr1,t1 itr2,t2 fn)
{
	while (itr1 != itr2)
	{
		fn(*itr1++);

	}
}
template<class T>
class multiply1
{
public :
	T operator() (T x, T y)
	{
		return x*y;
	}
};
class lessa
{
public:
void	operator ()()
	{
	for(int i=0;i<100;i++)
		cout << this_thread::get_id()<<endl;
	}
};
//ostream & operator<<(ostream &cout , string msg)
//{
//	return cout << msg << endl;
//}
condition_variable cond4;
int factorial(future<int> &f)
{
	int x = f.get();
	this_thread::sleep_for(chrono::seconds(1));
	for (int i = x - 1; i > 0; i--)
		x *= i;
	return x;
}
int fac(int x)
{
	cout << "fac called";
	return x;
}
template<class T>
class SumBill
{
public :
	virtual void sumbill(T a , T b)
	{
		cout << "in sumbill class";
	}
};
//template<class T>

class A 
{
	
public:
	virtual void callsum(int a , int b)
	{
		sumbill(a, b);
	}
	 template<class obj>
	 void sumbill(obj a, obj b)
	{
		obj c= a + b;
		cout << "in Class A"<<endl ;
	}
};
//template<class T>
class B : public A
{

public :
	
	virtual void  callsum(int a, int b)
	{
		sumbill(a, b);
	}
	template<class obj>
	void sumbill(obj a, obj b)
	{
		obj c = a + b;
		cout << "in Class B" << endl;
	}
};
//
//int main()
//{
//
//	A * a  = new B();
//	a->callsum(7, 8);
//
//
////	packaged_task<int()>  t(bind(fac, 6));
//////	t();
////
//
//	cout << "main" << endl;
//	//cout<< t.get_future().get()<<endl;
//	//cout << t.get_future().get()<<endl;
//	
//	//promise<int>p;
//	//future<int> fp = p.get_future();
//	//function<int(future<int > &)> f(bind(factorial,ref(fp)));
//	//future<int> fu = async(std::launch::async,factorial, ref(fp));
//	//cout << "hello";
//	//p.set_value(4);
//	//cout << "main " << fu.get();
//
//	
//
//	
//
//}
