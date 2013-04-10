/*
=================
cHealth.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cHealth.h"
/*
=================
- Data constructor initializes the cHealth
=================
*/
cHealth::cHealth() 			// Default constructor
{
	cHealth::health = 0;	
}


cHealth::cHealth(int Health) // Constructor
{
	cHealth::setHealth(Health);
}


/*
=================
- Destructor 
=================
*/
cHealth::~cHealth()			// Destructor
{
}

void cHealth::setHealth(int Health)  // set the health value
{
	cHealth::health = Health;
}

int cHealth::getHealth()  // Return the health value
{
	return cHealth::health;
}

void cHealth::damageHealth(int damage)
{
	cHealth::health -=damage;

}
void cHealth::increaseHealth(int heal)
{
	cHealth::health += heal;
}

bool cHealth::deathCheck()
{
	if(cHealth::health <=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
