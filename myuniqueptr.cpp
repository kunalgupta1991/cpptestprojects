#include <iostream>

struct zero_then_vardiadic_args
{

};
struct one_then_vardiadic_args
{

};


template <class _val, class Ty>
class myUniquePtr_base
{

};


template<class Tx>
class myUniquePtr
{
	Tx * data;
public :
	myUniquePtr(const myUniquePtr & uptr) = delete;
	myUniquePtr(myUniquePtr && uptr)
	{
		data = uptr.data;
		uptr.data = NULL;
	}
	Tx&  operator* ()
	{
		return *data;
	}

	Tx * get()
	{
		return data;
	}
	~myUniquePtr()
	{
		delete data;
	}
};