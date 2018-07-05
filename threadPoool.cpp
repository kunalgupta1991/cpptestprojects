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





class ITask
{
public:
	virtual bool execute() = 0;
	virtual void UpdateJobInfo()
	{

	}
	bool operator()()
	{
		UpdateJobInfo();
		return execute();
	}
	ITask()
	{

	}
	~ITask()
	{

	}
};
class ICallback
{
public :
	virtual ~ICallback() {};
};
template<class T>
class CTask :public ITask
{
	std::unique_ptr<T> _mainProcedure;
public:
	explicit CTask():ITask()
	{

	}
	~CTask()
	{

	}
	bool registerMainProc(std::unique_ptr<T> mainproc)
	{
		_mainProcedure = std::move(mainproc);
		return true;
	}
	bool execute()
	{
		(*_mainProcedure.get())();
		return true;
	}


};
class CJob : public ITask
{
public :
	CJob(unique_ptr<ICallback> callback):_callback(std::move(callback))
	{

	}
protected:
	unique_ptr<ICallback> _callback;
public:
};
class TpInterface
{
private:

	bool run_thread= true;
	typedef function<bool()>  TaskmanagerSignature;
	typedef CTask<TaskmanagerSignature> CtaskTaskmanagerSignature;
	typedef packaged_task<void()> void_packaged_Task;
	queue<packaged_task<void()> > q;
	queue<packaged_task<void()> > q1;
	queue<packaged_task<void()> > q2;
	condition_variable cond_queue1;
	condition_variable cond_queue2;
	condition_variable cond_queue;
	mutex mu_queue1;
	mutex mu_queue2;
	mutex mu_queue;
	vector<thread > v;
public:
	void  run()
	{
		while (true)
		{
			cout << "here";
			unique_lock<mutex> mu(mu_queue);
			cond_queue.wait(mu, [&]() {return !q.empty(); });
			cout << "RUn Thread Is Calling    " << q.size() << " " << q1.size() << endl;

			while (!q.empty())
			{

				//cout << "start pushing";
				if (q1.size() == 0)
				{
					unique_lock<mutex> mu1(mu_queue1);
					q1.push(move(q.front()));
					q.pop();
					mu1.unlock();

					cond_queue1.notify_one();

				}
				else if (q2.size() == 0)
				{
					unique_lock<mutex>mu2(mu_queue2);
					q2.push(move(q.front()));
					q.pop();
					mu2.unlock();
					cond_queue2.notify_one();

				}
			}
			mu.unlock();
			this_thread::sleep_for(chrono::seconds(1));
		}
	}
	void initialise()
	{ 
	/*	thread t(&TpInterface::run,this);
		thread t1(&TpInterface::fun1, this);
		thread t2(&TpInterface::fun2, this);
		t.detach();
		t1.detach();
		t2.detach();*/
		/*auto f1 = async(std::launch::async,&TpInterface::run, this);
		auto f2 = async(std::launch::async, &TpInterface::fun1, this);
		auto f3 = async(std::launch::async, &TpInterface::fun2, this);*/
		//cout << "initialised properly all the threads"<<endl;
		
	}
public:
	TpInterface()
	{
		initialise(); // creating 3 threads;
	}
	void post(ITask & task)
	{
		packaged_task<void()> t([&]() {task(); });   // lamda expression is used to convert "bool operator() " to void ()
		unique_lock<mutex> mu(mu_queue);
		q.push(move(t));
		mu.unlock();
		cond_queue.notify_one();
		this_thread::sleep_for(chrono::seconds(1));
	}
	public:

void fun1()
{
	while(run_thread)
	{
		unique_lock<mutex> lck1(mu_queue1);
		cond_queue1.wait(lck1, [&]() {return !q1.empty(); });
			q1.front()();
			q1.pop();
			lck1.unlock();
		cout << this_thread::get_id()<<endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}
void fun2()
{
	while (run_thread)
	{
		unique_lock<mutex> lck2(mu_queue2);
		cond_queue2.wait(lck2, [&]() {return !q2.empty(); });
		q2.front()();
		q2.pop();
		lck2.unlock();
		cout << this_thread::get_id() << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}


};
class JobManager
{
#define JobCompletionCallbackSignature std::function<bool()>
#define JobManagerTaskSignature std::function<bool()>
	
	typedef CTask<JobManagerTaskSignature> CTaskJobManager;
	unique_ptr < CTaskJobManager >thread_T_Task= make_unique <CTaskJobManager>();
	unique_ptr < CTaskJobManager>thread_W_Task= make_unique <CTaskJobManager>();
public :
	/*template<class T>
	using CTask<T>::registerMainProc;*/
	void Run(TpInterface &tpinterface)
	{
		cout << "trying to post job manager base functions" << endl;
		tpinterface.post(*(thread_T_Task.get()));
		tpinterface.post(*(thread_W_Task.get()));
		cout << "job Manger Runt RunW pushed"<<endl;
	}
	bool RunT()
	{
		cout << "I am in RunT"<<endl;
		return true;
	}
	bool RunW()
	{
		cout << "I am in RunW"<<endl;
		return true;
	}
	void initialise()
	{
		//function<bool()> f1 = std:: function<bool()>(bind(&RunT,this));
		std::unique_ptr<JobManagerTaskSignature> ThreadT = make_unique<JobManagerTaskSignature>(bind(&JobManager::RunT, this));
		bool t = thread_T_Task->registerMainProc(std::move(ThreadT));
		function<bool()> f(bind(&JobManager::RunT, this));
		std::unique_ptr<JobManagerTaskSignature> ThreadW = make_unique<JobManagerTaskSignature>(bind(&JobManager::RunW, this));
		bool t1 = thread_W_Task->registerMainProc(std::move(ThreadW));
	}
};
void test_fun(future<packaged_task<void()>> &f)
{
	 f.get()();
}
//int main()
//{
//	promise<packaged_task< void()>> p;
//	future<packaged_task< void() >>f1 = p.get_future();
//
//	thread t(test_fun,ref(f1));
//
//	
//
//
//	cout << " in main ";
//
//	//p.set_value(3);
//
//	t.join();
//	//TpInterface tpinterface;
//	//function<void()>f(bind(&TpInterface::run,&tpinterface));
//
//	//thread t(&TpInterface::run, &tpinterface);
//	//thread t1(&TpInterface::fun1, &tpinterface);
//	//thread t2(&TpInterface::fun2, &tpinterface);
//	//
//	//unique_ptr<JobManager> j = make_unique<JobManager>();
//	//j->initialise();
//	//j->Run(tpinterface);
//	//
//
//	//unique_ptr<JobManager> j1 = make_unique<JobManager>();
//	//j1->initialise();
//	//j1->Run(tpinterface);
//
//	//t.join();
//	//t1.join();
//	//t2.join();
//
//	//
//
//	
//}
//
////template<typename _ ret,typename _class,typename _arg1>
////class mem_fun3_t
////{
////	_ret(_class:: *m_ptr)(_arg1);
////public :
////	explicit mem_fun3_t(_ret(_class :: *pm)(_arg1)) :m_ptr(pm)
////	{
////
////	}
////	_ret operator()(_class *p, _arg1 arg1)const
////	{
////		return (p->*m_ptr)(arg);
////	}
////};
////template <class T>
////class Command
////{
////private :
////	T * m_objptr;
////	void (T :: *m_method)();
////public:
////	explicit Command(T *ptr, void (T::*pmethod)())
////	{
////		m_objptr = ptr;
////		m_method = pmethod;
////	}
////	void execute()
////	{
////		(m_objptr->*method)();
////	}
////	~Commaind() {};
////};
////template<class T>
////class  ThreadPool
////{
////public:
////	 ThreadPool();
////	~ ThreadPool();
////
////private:
////
////};
////template<class T>
//// ThreadPool:: ThreadPool()
////{
////}
//// template<class T>
//// ThreadPool::~ ThreadPool()
////{
////}
////