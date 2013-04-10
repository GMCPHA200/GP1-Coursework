//No longer Required
/*
=================
cRoom.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CROOM_H
#define _CROOM_H
#include "cD3DXTexture.h"

class cRoom
{
private:
	int posX;
	int posY;
	bool doorUp;
	bool doorDown;
	bool doorLeft;
	bool doorRight;
	int enemies;
public:
	cRoom();			// Default constructor
	cRoom(int roomPosX, int roomPosY, bool roomUp, bool roomDown, bool roomLeft, bool roomRight, int numEnemies); // Constructor
	~cRoom();// Destructor	
	void setPos(int roomPosX, int roomPosY);
	int getPosX();
	int getPosY();
	void setDoors(bool roomUp, bool roomDown, bool roomLeft, bool roomRight);
	bool getDoorUp();
	bool getDoorDown();
	bool getDoorLeft();
	bool getDoorRight();	
	void setEnemies(int numEnemies);
	int getEnemies();
};
#endif