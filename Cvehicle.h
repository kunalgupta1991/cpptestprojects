#ifndef CVE
#define CVE




#include<iostream>
#include<list>
#include<vector>
#include <map>
#include "Vehicle.h"
#include "Ityre.h"
#include <memory>
using namespace std;


class Cvehicle : public Ivehicle
{
	
protected :
	string NuberId;
	unique_ptr<Ityre> tyre;
	 enum class vcType  : char
	{
		 bus = 1,
	};
public:
	void GetNumberPlate() {};
	/*virtual string GetVechicleType() {};
	
	virtual  string GetSpec() {};*/
	Cvehicle(Ityre * tyre);
   virtual ~Cvehicle() {};
};


#endif // !CVE