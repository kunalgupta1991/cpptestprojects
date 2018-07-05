#include<iostream>
#include<thread>
#include<future>
#include<queue>
#include<mutex>
#include<iterator>
using namespace std;
typedef  unsigned long long JOBID;
enum class Jobtype : char
{
	addpathPerNe =0,
	addpathperVpGroup =1,
	cdc_gf
};
template<typename T>
class CJobType
{
	std::tuple<T, T> _jobTypeTuple;
public:
	CJobType(T mjob, T sjob)
	{
		_jobTypeTuple = make_tuple(mjob, sjob);
	}
	std::tuple <T, T> GetType()
	{
		return _jobTypeTuple;
	}
};
class Itask
{
public:
	virtual void execute() = 0;
	void operator()()
	{
		execute();
	}
};
template<typename T>
class Ctask : public Itask
{
	typedef T ctaskfunction;
	unique_ptr<ctaskfunction> function;
public :
	void registerproc(unique_ptr<ctaskfunction> f)  
	{
		function = std::move(f);
	}
	void execute()
	{
		(*function.get())();
	}
};
class AddPathData
{
	int age;
	string name;
	CJobType<Jobtype> sourceJobType;
public :
	AddPathData(CJobType<Jobtype> jobtype, int _age, string _name ):sourceJobType(jobtype),age(_age),name(_name)
	{}
	string Name()
	{
		return name;
	}
};
class CJob: public Itask
{
public :
	CJobType<Jobtype> _jobtype;
	JOBID jobid;
	virtual bool unpackageInput() { return true; };
	virtual bool packagedOutput() { return true; }
	virtual void execute() { }
};
template<class T>
class LockFreeQueue
{
	mutex m;
	queue<T> q;
public :
	void pop()
	{
		lock_guard<mutex> l(m);
		if (!q.empty())
			q.pop();
	}
	T& top()
	{
		lock_guard<mutex> l(m);
		return q.front();
	}
	void push(T &item)
	{
		lock_guard<mutex> l(m);
		q.push(item);
	}
	void push(T && item)
	{
		lock_guard<mutex> l(m);
		q.push(std::move(item));
	}
	bool is_empty()
	{
		lock_guard<mutex> l(m);
		return q.empty();
		
	}
};
class ThreadPool
{
	mutex tpm;
	typedef function<void()> threadPoolType;
	LockFreeQueue<threadPoolType> jobsqueue;
	vector<thread > vt;
public :
	
	void run()
	{
		while (1)
		{
			unique_lock<mutex> ltpm(tpm);
			if (!jobsqueue.is_empty())
			{
				threadPoolType t = jobsqueue.top();
				jobsqueue.pop();
				ltpm.unlock();
				t();
				cout << "this thread Has completed the task  " << this_thread ::get_id() <<endl ;
		  }
			else
			{
				ltpm.unlock();
				this_thread::sleep_for(chrono::milliseconds(10));
			}

		}
	}
	void push(threadPoolType t)
	{
		jobsqueue.push(t);
	}
	ThreadPool()
	{
		thread t1(&ThreadPool::run,this);
		thread t2(&ThreadPool::run,this);
		thread t3(&ThreadPool::run ,this);
		vt.push_back(std::move(t1));
		vt.push_back(std::move(t2));
		vt.push_back(std::move(t3));

	}
    ~	ThreadPool()
	{
		for (auto &t : vt)
			t.join();
	}
};
class pandojobmanager
{
	ThreadPool tp;

	typedef  std::function<void()> JobManagerTaskSignature;
	unique_ptr<Ctask<JobManagerTaskSignature>> _threadT_Task;
	unique_ptr<Ctask<JobManagerTaskSignature>> _threadW_Task;
public:
	void runT()
	{
		workT();
	}
	void runW()
	{
		workW();
	}
	void workT()
	{

	}
	void workW()
	{

	}
	void initialise()
	{
		cout << "initialising job manager"<<endl;
		unique_ptr<JobManagerTaskSignature> runtproc = make_unique<JobManagerTaskSignature>( std::bind(&pandojobmanager:: runT,this));
		unique_ptr<JobManagerTaskSignature> runwproc = make_unique<JobManagerTaskSignature>(std::bind(&pandojobmanager::runW, this));
		_threadT_Task->registerproc(std::move(runtproc));
		_threadW_Task->registerproc(std::move(runwproc));

	}
	void push(Itask *t)
	{
		JobManagerTaskSignature f([&t]() {
			(*t)();
		});
		tp.push(f);
	}
	void run()
	{
		
	     push(_threadT_Task.get());
		 push(_threadW_Task.get());

		 cout << "job manager runT and runW are pushed";
	}
	
};
template<class Tx>
class callback
{
	unique_ptr<Tx> fn;

public:
	callback(unique_ptr<Tx> _fn) : fn(std::move(_fn))
	{

	}
	Tx * getfn()
	{
		return fn.get();
	}
};
class TestCallback
{
	typedef function<void(string, int)> testcbsignature;
public:
	unique_ptr<callback<testcbsignature>> buildcallback()
	{
		unique_ptr<testcbsignature> tb = make_unique<testcbsignature>(bind(&TestCallback::notify,this,placeholders::_1, placeholders :: _2));
		unique_ptr<callback<testcbsignature>> cb(new callback<testcbsignature>(std::move(tb)));
		return std :: move(cb);
	}
	void notify(string s, int a)
	{
		cout << "in test callback";
		cout << s.c_str() << " " << a << endl;
	}
};
class dwdm
{
public:
	int a;
	int b;
	dwdm(int x, int y) :a(x),b(y)
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
//	TestCallback t; 
//	auto  ub = t.buildcallback();
//	auto notify = ub->getfn();
//	(*notify)("kunal", 1);
//	tuple<int, string, int > tq(21, "kunal", 4);
//	int x = get<0>(tq);
//}
//                                            threadpool example
//void fun1()
//{
//	for(int i=0;i<10;i++)
//	cout << "fun1 " << endl;
//
//}
//void fun2()
//{
//	for (int i = 0; i<10; i++)
//		cout << "fun2 " << endl;
//
//}
//void fun3()
//{
//	for (int i = 0; i<10; i++)
//		cout << "fun3 " << endl;
//
//}
//void fun4()
//{
//	for (int i = 0; i<10; i++)
//		cout << "fun4 " << endl;
//
//}
//int main()
//{
//	ThreadPool t;
//	t.push(fun1);
//	t.push(fun2);
//	t.push(fun3);
//	t.push(fun4);
//}

