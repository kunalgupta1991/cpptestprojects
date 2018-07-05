#include<iostream>
#include<thread>
#include <mutex>
using namespace std;
class EndtoEndSimulation
{
public :
	static  EndtoEndSimulation * Instance()
	{
		call_once(once, []() {instance = new EndtoEndSimulation(); });
		return instance;

	}
	
private:
	EndtoEndSimulation()
	{
		cout << "consructor called" << endl;
	}
	static EndtoEndSimulation * instance;
	static once_flag once;

};
once_flag EndtoEndSimulation::once;
EndtoEndSimulation * EndtoEndSimulation::instance = NULL;
class pnadosimulator
{
	void run();
};

