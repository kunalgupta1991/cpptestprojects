#include<iostream>
#include<memory>
#include<vector>
using namespace std;
class dwdm
{
public:
	int a;
	int b;
	dwdm(int x, int y) :a(x), b(y)
	{

	}
	dwdm(const dwdm& d)
	{
		cout << "coppy constructor called";
	}
	~dwdm()
	{
		cout << "destructor called  ";
	}
};
//int main()
//{
//	{
//		dwdm*arr[] = { new dwdm(2,3),new dwdm(3,4) };
//		vector<unique_ptr<dwdm>> v;
//		for (int i = 0; i < 2; i++)
//		{
//			v.push_back(make_unique<dwdm>(i, i + 1));
//		}
//		for (int i = 0; i < 2; i++)
//		{
//			delete arr[i];
//		}
//	}
//
//	
//}