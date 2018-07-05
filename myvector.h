//#ifndef MYVECTOR_H
//#define MYVECTOR_H
// #include<stdlib.h>
//  #include<iostream>
//  #include <memory>
//#define  random_access_iterator_flag int
//
//
//class myexception 
//{
//
//};
//template<class tx>
//class vector_iterator
//{
//
//};
//
//template<class val_type>
//class myvector_val
//{
//public:
//	typedef myvector_val<val_type> myt;
//	typedef typename val_type::pointer pointer;
//	typedef vector_iterator<myt> iterator;
//	myvector_val():myfirst(),mylast(),myend()
//	{
//
//	}
//	pointer myfirst;
//	pointer mylast;
//	pointer myend;
//
//};
//
//template<class _Alloc_types>
//class myVector_alloc
//{
//private:
//	std::pair<_Alty, myvector_val<_Val_types> > _Mypair;
//public: 
//	typedef myvector_alloc<_Alloc_types> myt;
//	typedef vector_iterator<myvector_val<_Alloc_types> > iterator;
//};
//template <class _Ty>
//class myallocator
//{
//public :
//	typedef myallocator<_Ty> _myt;
//	typedef _Ty value_type;
//	typedef value_type * pointer;
//	typedef value_type& reference;
//	typedef size_t size_type;
//
//	template < class _other>
//	struct rebind
//	{
//		typedef myallocator <_other> other;
//	};
//	pointer address(reference val) const
//	{
//		return 
//	}
//	 pointer allocate(size_type _Count)
//	{	// allocate array of _Count elements
//		return (static_cast<pointer>(_Allocate(_Count, sizeof(_Ty))));
//	}
//
//	pointer allocate(size_type _Count, const void *)
//	{	// allocate array of _Count elements, ignore hint
//		return (allocate(_Count));
//	}
//};
//template<class alloc_type>
//class vector_alloc
//{
//public :
//	typedef vector_alloc<alloc_type> myt;
//
//};
//template<class tx,
//         class Alloc = myallocator<tx>>
//class myvector
//{
//private:
//	tx *myptr;
//	int size;
//	
//	typedef tx value_type;
//
//public:
//	myvector(size_t _count);
//	myvector(const myvector &my);
//	myvector( myvector &&my);
//	tx & operator[](int index);
//	myvector & operator= (myvector other);
//	void swap(myvector &other);
//	myvector(std::initializer_list<value_type> _ilist)
//	{
//
//	}
//
// 
//	
//
//
//};
//
//
//
//
//
//
//#endif // !MYVECTOR.H
//
