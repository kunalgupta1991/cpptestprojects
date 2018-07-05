#include<iostream>
#include<list>
#include<memory>
using namespace std;
enum class ExecutionState :char
{
	ftv,
	dv
};
enum class VerificationState : char
{
	pre,
	post
};
class RuleCondition
{
private:
	
public:
	ExecutionState state;
	VerificationState vfstate;
	bool operator==(RuleCondition & rc)
	{
		if ((state == rc.state) && (vfstate == rc.vfstate))
			return true;
			
	}



};
class IRule
{
	
public:
	virtual void validate(int a)
	{
		

	}
	
	virtual void validate(int a, int b)
	{

	}
	
	virtual ~IRule()
	{
		cout << "base destructor called" << endl;;
	}
};
class Rule1 : public IRule
{
public:
	void validate(int a)
	{
		cout << "Rule 1 called";
	}
	
};
class Rule2 : public IRule
{
public :
	void validate(int a,int b)
	{
		cout << "Rule 2 called";
	}

	
};

class RuleChecker
{
	list<unique_ptr<IRule>> l1;
	list<unique_ptr<IRule>> l2;
	RuleCondition rc;
    
public:
	//RuleChecker() = default;
	RuleChecker()
	{
		rc.state = ExecutionState::dv;
		rc.vfstate = VerificationState::post;
	
	}
	void addtol1(unique_ptr<IRule > i)
	{
		l1.push_back(move(i));
	}
	void addtol2(unique_ptr<IRule > i)
	{
		l2.push_back(move(i));
	}
	void Run()
	{
		for (auto &itr : l1)
		{
			
			itr->validate(1);
		}
		for (auto &itr : l2)
		{
			itr->validate(1,2);
		}
	}

};
void kmp1(const char * i, const  char *i2)
{

}
void kmp(string i,  string i2)
{

}
void setage(const int &i)
{
	cout << "const function called" << endl;
}
void setage( int &i)
{
	cout << "Non const function called" << endl;
}
class test1
{
public:
	virtual ~ test1()
	{
		cout << " base is called" << endl;
	}
};
class test2 :public test1
{
public:
	~test2()
	{
		cout << "derived one called" << endl;
	}
};
int main()
{
	{
		shared_ptr<test1> t = shared_ptr<test2>(new test2());
		unique_ptr<test1> t1 = unique_ptr<test2>(new test2());
	}
	//const_cast<int&>(i) = 6;
	{
		RuleChecker rc;
		//unique_ptr<IRule> r1 = make_unique<Rule1>();
		unique_ptr<IRule> r2 = make_unique<Rule2>();
		rc.addtol1(make_unique<Rule1>());
		rc.addtol2(move(r2));
		rc.Run();
	}
}