#include "Cvehicle.h"
Cvehicle::Cvehicle(Ityre  * ctyre)
{
	tyre = unique_ptr<Ityre>(ctyre);
}