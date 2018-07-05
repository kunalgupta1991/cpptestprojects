
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

queue<int > q;
mutex mu_prod;
std::condition_variable cond;
void producer()
{
	int i = 0;
	unique_lock<mutex> muni(mu_prod, std::defer_lock);
	while (1)
	{

		muni.lock();
		//cout << "producer loop" << endl;
		q.push(i++);
		muni.unlock();
		cond.notify_all();
		this_thread::sleep_for(chrono::seconds(1));
	}
}
void consumer()
{

	while (1)
	{
		unique_lock<mutex> mlck(mu_prod);
		//cout << "consumer loop" << endl;
		cond.wait(mlck);
		while (!q.empty())
		{
			cout << q.front() << endl;
			//cout << q.size() << "size "<<endl;
			q.pop();
		}
		mlck.unlock();
		//	cout << "hahahhahahhaha";
	}
}
mutex p1;
mutex p2;
condition_variable cond1, cond3;
bool turn1 = false, turn2 = true;
unique_lock<mutex>lock1(p1, std::defer_lock);
unique_lock<mutex>lock2(p2, std::defer_lock);
void function1()
{
	for (int i = 0; i > -100; i--) {}
	//	l.share_print("from T1: ", i);
}
void function2(int &i)
{
	while (i<100)
	{
		lock2.lock();
		cond3.wait(lock2, []() {return turn2; });
		turn2 = false;
		cout << i << "from T1" << endl;
		i = i + 1;
		lock2.unlock();
		turn1 = true;
		cond1.notify_one();

	}
}
void function3(int &i)
{
	while (i<100)
	{
		lock1.lock();
		cond1.wait(lock1, []() {return turn1; });
		turn1 = false;
		{
			cout << i << "from T2" << endl;
			i = i + 1;
			lock1.unlock();
			turn2 = true;
			cond3.notify_one();
		}
	}
}
int print_int(future<int> &fs)
{
	cout << "Mr kunal " << endl;

	int id = fs.get();
	cout << "form print_int" << id;
	return id + 1;

}