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


typedef unsigned long lng;

class ref_cout_base
{
private:
	virtual void destroy() = 0;
	virtual void delete_this() = 0;
private:
	lng weak;
	lng use;
	
public :
	ref_cout_base() :weak(1), use(1)
	{

	}
	int use_count()
	{
		return use;
	}
	int weak_count()
	{
		return weak;
	}
	void incrementw() { weak + 1; }
	void incrementu() { use + 1; }
	void decrw()
	{
		weak = weak - 1;
		if (weak_count() == 0)
			delete_this();
	}
	void decru()
	{
		use = use - 1;
		if (use == 0)
		{
			destroy();
			decrw();
		}
	}
	bool expired()
	{
		return use == 0;
	}
};
template<class Ty>
class Ref_Count : public ref_cout_base
{
private:
	Ty * ptr;
	void destroy() = 0
	{
		delete ptr;
	 }
	void delete_this() = 0
	{
		delete this;
	 }
public :
	Ref_Count(Ty * pt) : ptr(pt)
	{

	}

};
template<class T>
class ptr_Base
{
private :
	T* ptr;
	ref_cout_base * ref_count;
public :
	typedef ptr_Base<T> myt;
	typedef T elementType;
	
	ptr_Base() :ptr(0), ref_count(0)
	{

	}
	ptr_Base(myt &&other): ptr(other.ptr),ref_count(other.ref_count)
	{
		other.ptr = 0;
		other.ref_count = 0;
	}
	template<class Ty2>
	ptr_Base(ptr_Base<Ty2> && other ): ptr(other.ptr), ref_count(other.ref_count)
	{
		other.ptr = 0;
		other.ref_count = 0;
	}
	void decrU()
	{
		ref_count->decru();
	}
	void decrW()
	{
		ref_count->decrw();
	}
	int Use_count()
	{
		return ref_count ? ref_count->use_count();
	}
	myt & operator =(myt && right)
	{
		swap(right);
	}
	void swap(ptr_Base & right)  // doubt
	{
		std::swap(ptr, right.ptr);
		std::swap(ref_count, right.ref_count);
	}
	elementType * get()
	{
		return ptr;
	 }
	bool expired()
	{
		ref_count ? ref_count->expired() : true;
	}
};