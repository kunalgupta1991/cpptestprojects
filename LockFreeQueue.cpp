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
#include<atomic>
using namespace std;

namespace pandocode
{
	template<typename T>
	class LockFreeQueue
	{
		unique_ptr<mutex> mu;
		unique_lock<mutex> queue_lock;
		queue<T> q;
		atomic<int> vbihari;
	public:
		LockFreeQueue()
		{

			mu = make_unique<mutex>();
			queue_lock = unique_lock<mutex>(*mu.get());
		}
		void push(T &t)
		{
			queue_lock.lock();
			q.push(t);
			queue_lock.unlock();
		}
		void push(T &&t)
		{
			queue_lock.lock();
			q.push(std::move(t));
			queue_lock.unlock();
		}
		T& pop()
		{
			queue_lock.lock();
			T t = q.front();
			q.pop();
			queue_lock.unlock();
			return t;
		}
		T& top()
		{
			queue_lock.lock();
			T t = q.front();
			queue_lock.unlock();
			return t;

		}
	};
};