//#include"myvector.h"
//
////void * myallocator::myallocate(size_t nbytes)
////{
////	return malloc(nbytes);
////}
////void myallocator::mydealloc(void *p)
////{
////	free(p);
////	
////}
//
//
//
//template<class tx>
//myvector<tx > :: myvector(size_t count)
//{
//	
//}
//
//template<class tx>
//myvector<tx > :: myvector(const myvector &my)
//{
//
//	cout << "copy constructor called" << endl;
//	size = my.size;
//	myptr = new tx[size];
//	for (int i = 0; i < size; i++)
//		myptr[i] = my.myptr[i];
//
//}
//
//template<class tx>
//myvector<tx > ::myvector(myvector &&my)
//{
//
//	cout << "move constructor called" << endl;
//	size = my.size;
//	myptr = my.myptr;
//	my.myptr = nullptr;
//}
//
//template<class tx>
//void myvector<tx > ::swap(myvector &other)
//{
//	std::swap(myptr, other.myptr);
//	std::swap(size, other.size);
//}
//template<class tx>
//tx& myvector<tx> :: operator[](int index)
//{
//	return myptr[index];
//}
//template<class tx>
//myvector<tx>&  myvector<tx> ::operator= (myvector other)
//{
//	swap(other);
//}