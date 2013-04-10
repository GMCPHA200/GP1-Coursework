/*
=================
cGooEnemy.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cGooEnemy.h"
/*
=================
- Data constructor initializes the cGooEnemy to the data passed to 
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cGooEnemy::cGooEnemy() 			// Default constructor
{

	
}
cGooEnemy::cGooEnemy(cSprite csprite, cHealth chealth, bool isActive) // Constructor
{
	cGooEnemy::setSprite(csprite);
	cGooEnemy::setHealth(chealth);
	cGooEnemy::setActive(isActive);
}
/*
=================
- Destructor 
=================
*/
cGooEnemy::~cGooEnemy()			// Destructor
{
}

void cGooEnemy::setSprite(cSprite csprite)
{
	cGooEnemy::sprite = csprite;
}

cSprite cGooEnemy::getSprite()
{
	return cGooEnemy::sprite;
}

void cGooEnemy::setHealth(cHealth chealth)
{
	cGooEnemy::health = chealth;
}

cHealth cGooEnemy::getHealth()
{
	return cGooEnemy::health;
}

void cGooEnemy::setActive(bool isActive)
{
	cGooEnemy::active = isActive;
}

bool cGooEnemy::getActive()
{
	return cGooEnemy::active;
}