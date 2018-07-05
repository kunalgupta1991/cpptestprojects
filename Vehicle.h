#ifndef VEHICLE
#define VEHICLE



#include<iostream>
#include<list>
#include<vector>
#include <map>
#include <utility>
using namespace std;


class Ivehicle
{

public:
     virtual	void GetNumberPlate() = 0;
	//virtual string GetVechicleType() = 0;
	//virtual string GetSpec() = 0;
	virtual ~Ivehicle() =0;
};


#endif // !VECHICLE