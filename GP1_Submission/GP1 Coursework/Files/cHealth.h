/*
=================
cHealth.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CHEALTH_H
#define _CHEALTH_H

class cHealth
{
private:
	int health;	
public:
	cHealth();			// Default constructor
	cHealth(int Health); // Constructor
	~cHealth();			// Destructor	
	void setHealth(int Health);
	int getHealth();
	void damageHealth(int damage);
	void increaseHealth(int damage);
	bool deathCheck();
};
#endif