#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
using namespace std;
class singleton
{
	static unique_ptr< singleton> instance;
	static std::once_flag onceflat;
	singleton()
	{
		cout << "singleton instance is created";
	}
public:
	static singleton *Instance()
	{
		std::call_once(onceflat, []() {instance.reset(new singleton()); });
		
		return instance.get();
	}
};
unique_ptr<singleton> singleton::instance = NULL;
std::once_flag singleton::onceflat;


///////////////////////////////////////////////////////observer/////////////////////////////////////////////
class observer;
class subject
{
	vector<shared_ptr<observer>> v;
public:
	void attach(shared_ptr<observer> ob);
	void update();
};
class observer
{
	virtual void update_observer() = 0;


	class subject* _s;
public:
	
	observer(class subject* s):_s(s)
	{
		
		_s->attach(shared_ptr<observer>(this));
	}
	void	update()
	{
		update_observer();
	}
	~observer()
	{

	}

};

void subject::update()
{
	for (auto itr = v.begin(); itr != v.end(); itr++)
	{
		(*itr)->update();
	}
	/*
	/*for each (auto var in v)
	{
	var->update();
	}*/
}
class observer1 :public observer
{
	
	void update_observer()
	{
		cout << "updated obeserver1";
	}
public:
	observer1(subject* s) : observer(s)
	{

	}
};
class observer2 :public observer
{
	void update_observer()
	{
		cout << "updated obeserver2";
	}
public:
	observer2(subject *s) : observer(s)
	{

	}
};
void subject :: attach(shared_ptr<observer> ob)
{
	v.push_back(ob);
}


//subject * s = new subject();
//shared_ptr<observer> o1 = make_shared<observer1>(s);
//shared_ptr<observer> o2 = make_shared<observer2>(s);
//s->update();
////////////////////////////////////////////////////chain of responsibility//////////////////////////////////////////

class chain
{
public:
	virtual void setnext( chain * c1) = 0;
	virtual void print( int i) = 0;

};
class positivehandler : public chain
{
	chain *c;
public:
	void setnext(chain * ck)
	{
		c = ck;
	}
	void print(int number)
	{
		if (number > 0)
			cout << "Its a positie no" << endl;
		else
			c->print(number);
	}

};
class negativehandler : public chain
{
public:
	void setnext(chain * ck)
	{
		c = ck;
	}
	void print(int number)
	{
		if (number < 0)
			cout << "Its a negative no" << endl;
		else
			c->print(number);
	}
	chain *c;
};
class zerohandler : public chain
{
	chain * c;
public:
	void setnext(chain * ck)
	{
		c = ck;
	}
	void print(int number)
	{
		if (number == 0)
			cout << "Its a zero no" << endl;
		else
			c->print(number);
	}
};

//chain * c1 = new positivehandler();
//chain * pn = new negativehandler();
//chain * ze = new zerohandler();
//c1->setnext(pn);
//pn->setnext(ze);
//c1->print(1);
/////////////////////////////////// Command Pattern///////////////////////////////////////////
class command
{
public :
	virtual void execute() = 0;
};
class tv
{
public:
	void pressTvButton()
	{
		cout << " I am making tv on";
	}
};
class TvCommaind : public command
{
	tv *Tv;
public:
	TvCommaind(tv * tele)
	{
		Tv = tele;
	}
	void execute()
	{
		Tv->pressTvButton();
	}
};
class Remote
{
	command * c;
public:
	void pressbutton()
	{
		c->execute();
	}
	void setCommand(command * c1)
	{
		c = c1;
	}
	
};
//int main()
//{
//	chain * c1 = new positivehandler();
//	chain * pn = new negativehandler();
//	chain * ze = new zerohandler();
//	c1->setnext(pn);
//	pn->setnext(ze);
//	c1->print(1);
//}
//int main()
//{
//	shared_ptr<subject> s;
//	shared_ptr<observer> o1= std::make_shared<observer1>(s.get());
//	shared_ptr<observer> o2 = std::make_shared<observer1>(s.get());
//	//singleton * t = singleton::Instance();
//	//singleton * s = singleton::Instance();
//	////singleton s1;
//
//}
