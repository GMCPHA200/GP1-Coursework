//Class no longer Required
/*
=================
cRoom.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRoom.h"
/*
=================
- Data constructor initializes the cRoom
=================
*/
cRoom::cRoom() 			// Default constructor
{
	cRoom::posX = 0;
	cRoom::posY = 0;
	cRoom::doorUp = false;
	cRoom::doorDown = false;
	cRoom::doorLeft = false;
	cRoom::doorRight = false;	
}


cRoom::cRoom(int roomPosX, int roomPosY, bool roomUp, bool roomDown, bool roomLeft, bool roomRight, int numEnemies) // Constructor
{
	cRoom::setPos(roomPosX, roomPosY);
	cRoom::setDoors(roomUp, roomDown, roomLeft, roomRight);
	
}


/*
=================
- Destructor 
=================
*/
cRoom::~cRoom()			// Destructor
{
}

void cRoom::setPos(int roomPosX, int roomPosY)
{
	cRoom::posX = roomPosX;
	cRoom::posY = roomPosY;
}

int cRoom:: getPosX()
{
	return cRoom::posX;
}
int cRoom:: getPosY()
{
	return cRoom::posY;
}

void cRoom::setDoors(bool roomUp, bool roomDown, bool roomLeft, bool roomRight)  // set the door values to true or false
{
	cRoom::doorUp = roomUp;
	cRoom::doorDown = roomDown;
	cRoom::doorLeft = roomLeft;
	cRoom::doorRight = roomRight;
	
}

bool cRoom::getDoorUp()  // Return the health value
{
	return cRoom::doorUp;
}

bool cRoom::getDoorDown()  // Return the health value
{
	return cRoom::doorDown;
}

bool cRoom::getDoorLeft()  // Return the health value
{
	return cRoom::doorLeft;
}

bool cRoom::getDoorRight()  // Return the health value
{
	return cRoom::doorRight;
}

void cRoom::setEnemies(int numEnemies)
{
	cRoom::enemies = numEnemies;
}

int cRoom::getEnemies()
{
	return cRoom::enemies;
}