/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CGOOENEMY_H
#define _CGOOENEMY_H
#include "cSprite.h"
#include "cHealth.h"


class cGooEnemy
{
private:
	cSprite sprite;
	cHealth health;
	bool active;

public:
	cGooEnemy();			// Default constructor
	cGooEnemy(cSprite sprite, cHealth health, bool isActive); // Constructor
	~cGooEnemy();			// Destructor
	void setSprite(cSprite csprite);
	cSprite getSprite();
	void setHealth(cHealth chealth);
	cHealth getHealth();
	void setActive(bool isActive);
	bool getActive();
	
};
#endif