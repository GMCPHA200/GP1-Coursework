/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cSprite.h"
#include "cHealth.h"
//#include "cGooEnemy.h"
//#include "cRoom.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

RECT clientBounds;
	
D3DXVECTOR2 playerVeloc = D3DXVECTOR2(0,0);
D3DXVECTOR2 projectileVeloc = D3DXVECTOR2(5,0);

D3DXVECTOR2 playerTrans = D3DXVECTOR2(350,200);
D3DXVECTOR2 playerScale = D3DXVECTOR2(1.0f,1.0f);
cHealth playerHealth(100);

D3DXVECTOR3 playerPos = D3DXVECTOR3(300,300,0);
cSprite thePlayer;

D3DXVECTOR2 healthBarTrans = D3DXVECTOR2(277,490);
D3DXVECTOR2 healthBarScale = D3DXVECTOR2(1.0f,1.0f);

D3DXVECTOR2 upDoorTrans = D3DXVECTOR2(325,125);
D3DXVECTOR2 downDoorTrans = D3DXVECTOR2(325,400);
D3DXVECTOR2 leftDoorTrans = D3DXVECTOR2(-38,215);
D3DXVECTOR2 rightDoorTrans = D3DXVECTOR2(688,215);
D3DXVECTOR2 doorScale = D3DXVECTOR2(1.0f,1.0f);
BOOL controlDiagonalCheckCooldown = false;

BOOL projectileStart = false;

//BOOL roomSpawned = true;
BOOL spawnWave1 =  true;
BOOL spawnWave2 = false;
BOOL spawnWave3 = false;


/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue
	switch (message)
	{
		case WM_KEYDOWN:
			{
				if (playerHealth.deathCheck())
				{
					if(wParam == 'Y')
					{
						playerHealth.setHealth(100);
					}
					if(wParam == 'N')
					{
						PostQuitMessage(0);
						return 0;
					}
				}
				else
				{				
					controlDiagonalCheckCooldown = false;

					if(GetAsyncKeyState('E'))
					{
						projectileStart = true;						
					}

					if(GetAsyncKeyState('W'))
					{
						if(GetAsyncKeyState('S'))
						{
							playerVeloc.y = 0;
							return 0;
						}
						else
						{
							playerVeloc.y = -5.0f;
							projectileVeloc.y = -5.0f;
							return 0;
						}
					}

					if(GetAsyncKeyState('S'))
					{
						if(GetAsyncKeyState('W'))
						{
							playerVeloc.y = 0;
							return 0;
						}
						else
						{
							playerVeloc.y = 5.0f;
							projectileVeloc.y = 5.0f;
							return 0;
						}
					}

					if(GetAsyncKeyState('A'))
					{
						if(GetAsyncKeyState('D'))
						{
							playerVeloc.x = 0;
							return 0;
						}
						else
						{
							playerVeloc.x = -5.0f;
							projectileVeloc.x = -5.0f;
							return 0;
						}
					}

					if(GetAsyncKeyState('D'))
					{
						if(GetAsyncKeyState('A'))
						{
							playerVeloc.x = 0;
							return 0;
						}
						else
						{
							playerVeloc.x = 5.0f;
							projectileVeloc.x = 5.0f;
							return 0;
						}
					}
				
					return 0;
				}
			}

		case WM_KEYUP:
			{
				controlDiagonalCheckCooldown = false;
				playerVeloc.x = 0;
				playerVeloc.y = 0;
				
				if(GetAsyncKeyState('W'))
				{
					if(GetAsyncKeyState('S'))
					{
						playerVeloc.y = 0;
						return 0;
					}
					else
					{
						playerVeloc.y = -5.0f;
						return 0;
					}
				}

				if(GetAsyncKeyState('S'))
				{
					if(GetAsyncKeyState('W'))
					{
						playerVeloc.y = 0;
						return 0;
					}
					else
					{
						playerVeloc.y = 5.0f;
						return 0;
					}
				}

				if(GetAsyncKeyState('A'))
				{
					if(GetAsyncKeyState('D'))
					{
						playerVeloc.y = 0;
						return 0;
					}
					else
					{
						playerVeloc.x = -5.0f;
						return 0;
					}
				}

				if(GetAsyncKeyState('D'))
				{
					if(GetAsyncKeyState('A'))
					{
						playerVeloc.y = 0;
						return 0;
					}
					else
					{
						playerVeloc.x = 5.0f;
						return 0;
					}
				}
				
				return 0;
			}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,"wizard.ico"); // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "WizardArena"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"wizard.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("WizardArena",			// the window class to use
							 "Wizard Arena",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	GetClientRect(wndHandle,&clientBounds);

	float fpsRate = 1.0f/25.0f;

	LPDIRECT3DSURFACE9 roomSurface;				// the Direct3D surface
	LPDIRECT3DSURFACE9 gameOverSurface;	
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	// Create the background surface
	gameOverSurface = d3dMgr->getD3DSurfaceFromFile("Images\\GameOver.png");
	roomSurface = d3dMgr->getD3DSurfaceFromFile("Images\\RoomBackGround.png");

	/*
	bool roomArray[5][5]=
    {
		{0,0,0,0,0},
        {0,0,1,0,0},
        {0,1,1,1,0},
		{0,0,1,0,0},
		{0,0,0,0,0},
    };

	int posX = 3;
	int posY = 3;
	cRoom room1(posX,posY,roomArray[posX][posY-1],roomArray[posX][posY+1],roomArray[posX-1][posY],roomArray[posX+1][posY],0);
	posX = 2;
	posY = 3;
	cRoom room2(posX,posY,roomArray[posX][posY-1],roomArray[posX][posY+1],roomArray[posX-1][posY],roomArray[posX+1][posY],1);
	posX = 3;
	posY = 4;
	cRoom room3(posX,posY,roomArray[posX][posY-1],roomArray[posX][posY+1],roomArray[posX-1][posY],roomArray[posX+1][posY],2);
	posX = 4;
	posY = 3;
	cRoom room4(posX,posY,roomArray[posX][posY-1],roomArray[posX][posY+1],roomArray[posX-1][posY],roomArray[posX+1][posY],3);
	posX = 3;
	posY = 2;
	cRoom room5(posX,posY,roomArray[posX][posY-1],roomArray[posX][posY+1],roomArray[posX-1][posY],roomArray[posX+1][posY],4);
	
	cRoom rooms[4];
	rooms[0]=room1;
	rooms[1]=room2;
	rooms[2]=room3;
	rooms[3]=room4;
	rooms[4]=room5;
	
	
	cRoom currentRoom = room1;
	*/
	D3DXVECTOR3 healthBarPos = D3DXVECTOR3(100,100,0);
	cSprite healthBar(healthBarPos,d3dMgr->getTheD3DDevice(),"Images\\HealthBar.png");

	/*
	D3DXVECTOR3 upDoorPos = D3DXVECTOR3(400,25,0);
	cSprite upDoor(upDoorPos,d3dMgr->getTheD3DDevice(),"Images\\door.png");

	D3DXVECTOR3 downDoorPos = D3DXVECTOR3(400,125,0);
	cSprite downDoor(downDoorPos,d3dMgr->getTheD3DDevice(),"Images\\door.png");

	D3DXVECTOR3 leftDoorPos = D3DXVECTOR3(25,125,0);
	cSprite leftDoor(leftDoorPos,d3dMgr->getTheD3DDevice(),"Images\\door.png");

	D3DXVECTOR3 rightDoorPos = D3DXVECTOR3(400,125,0);
	cSprite rightDoor(rightDoorPos,d3dMgr->getTheD3DDevice(),"Images\\door.png");
	*/
	cSprite thePlayer(playerPos,d3dMgr->getTheD3DDevice(),"Images\\WizardDown.png");


	D3DXVECTOR3 enemyPos1 = D3DXVECTOR3(700,100,0);
	cHealth* gooHealth1 = new cHealth(10);
	cSprite* gooSprite1 = new cSprite(enemyPos1,d3dMgr->getTheD3DDevice(),"Images\\goo.png");	

	D3DXVECTOR3 enemyPos2 = D3DXVECTOR3(100,300,0);
	cHealth* gooHealth2 = new cHealth(10);
	cSprite* gooSprite2 = new cSprite(enemyPos2,d3dMgr->getTheD3DDevice(),"Images\\goo.png");	

	D3DXVECTOR3 enemyPos3 = D3DXVECTOR3(650,300,0);
	cHealth* gooHealth3 = new cHealth(10);
	cSprite* gooSprite3 = new cSprite(enemyPos3,d3dMgr->getTheD3DDevice(),"Images\\goo.png");	

	D3DXVECTOR3 enemyPos4 = D3DXVECTOR3(200,100,0);
	cHealth* gooHealth4 = new cHealth(10);
	cSprite* gooSprite4 = new cSprite(enemyPos4,d3dMgr->getTheD3DDevice(),"Images\\goo.png");	

	/*
	if (projectileStart == true)
	{
		cSprite* projectile = new cSprite(thePlayer.getSpritePos(),d3dMgr->getTheD3DDevice(),"Images\\goo.png");
		projectile->setTranslation(D3DXVECTOR2(projectileVeloc.x,projectileVeloc.y));
		projectileStart = false;
	}
	*/

	// Build our matrix to rotate, scale and position our sprite
	
	D3DXMATRIX playerTransformMatrix;
	
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{			
			// Game code goes here
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			float dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;				
			
			if(timeElapsed > fpsRate)
			{	
				if(playerHealth.deathCheck())
				{					
					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(gameOverSurface, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
			
					d3dxSRMgr->beginDraw();				
					//
					d3dxSRMgr->endDraw();
					d3dMgr->endRender();
				
					previousTime = currentTime;
				}
				else
				{
					/*
					if (roomSpawned == false)
					{
						D3DXVECTOR2 playerPos = D3DXVECTOR2(200,400);
						thePlayer.setSpriteTransformMatrix(playerTransformMatrix, thePlayer.getSpriteCentre(),0.0f,playerScale,thePlayer.getSpriteCentre(),0.0f,playerPos);
						roomSpawned = true;
					}
					*/
					
					if (gooHealth1->deathCheck())
					{
						delete gooSprite1;
						delete gooHealth1;
						Sleep(1000);
						gooHealth1 = new cHealth(10);
						gooSprite1 = new cSprite(enemyPos1,d3dMgr->getTheD3DDevice(),"Images\\goo.png");
										
					}
					if (gooHealth2->deathCheck())
					{
						delete gooSprite2;
						delete gooHealth2;
						Sleep(1000);
						gooHealth2 = new cHealth(10);
						gooSprite2 = new cSprite(enemyPos2,d3dMgr->getTheD3DDevice(),"Images\\goo.png");										
					}
					if (gooHealth3->deathCheck())
					{						
						delete gooSprite3;
						delete gooHealth3;
						Sleep(1000);
						gooHealth3 = new cHealth(10);
						gooSprite3 = new cSprite(enemyPos3,d3dMgr->getTheD3DDevice(),"Images\\goo.png");			
					}
					if (gooHealth4->deathCheck())
					{						
						delete gooSprite4;
						delete gooHealth4;
						Sleep(1000);
						gooHealth4 = new cHealth(10);
						gooSprite4 = new cSprite(enemyPos4,d3dMgr->getTheD3DDevice(),"Images\\goo.png");				
					}


					if(playerVeloc.x != 0 && playerVeloc.y != 0 && controlDiagonalCheckCooldown == false)
					{
						playerVeloc.x *= 0.75f;
						playerVeloc.y *= 0.75f;
						controlDiagonalCheckCooldown = true;
					}

					playerTrans += playerVeloc;

					if (playerTrans.x < (clientBounds.left +25))
					{
						playerTrans.x =	clientBounds.left +26;
					}
					if (playerTrans.y < (clientBounds.top +25))
					{
						playerTrans.y =	clientBounds.top +26;
					}
					if (playerTrans.x > (clientBounds.right - (25 + 75)))
					{
						playerTrans.x =	clientBounds.right -(26 + 75);
					}
					if (playerTrans.y > (clientBounds.bottom -(154 + 75)))
					{
						playerTrans.y =	clientBounds.bottom -(155 +75);
					}
				

					if(playerVeloc.x > 0)
					{
						thePlayer.setTexture(d3dMgr->getTheD3DDevice(),"Images\\WizardRight.png");
						playerScale = D3DXVECTOR2(1.0f,1.0f);
					}
					if(playerVeloc.x < 0)
					{
						thePlayer.setTexture(d3dMgr->getTheD3DDevice(),"Images\\WizardRight.png");
						playerScale = D3DXVECTOR2(-1.0f,1.0f);
					}
					if(playerVeloc.y < 0)
					{
						thePlayer.setTexture(d3dMgr->getTheD3DDevice(),"Images\\WizardUp.png");
					}
					if(playerVeloc.y > 0)
					{
						thePlayer.setTexture(d3dMgr->getTheD3DDevice(),"Images\\WizardDown.png");
					}

					healthBarScale.x = (FLOAT)playerHealth.getHealth()/100;

					
					thePlayer.setSpritePos(D3DXVECTOR3(playerTrans.x,playerTrans.y,0));
					thePlayer.setSpriteScaling(playerScale.x,playerScale.y);
					healthBar.setSpritePos(D3DXVECTOR3(healthBarTrans.x,healthBarTrans.y,0));
					healthBar.setSpriteScaling(healthBarScale.x,healthBarScale.y);
					
					/*
					upDoor.setSpritePos(D3DXVECTOR3(upDoorTrans.x,upDoorTrans.y,0));
					downDoor.setSpritePos(D3DXVECTOR3(downDoorTrans.x,downDoorTrans.y,0));
					leftDoor.setSpritePos(D3DXVECTOR3(leftDoorTrans.x,leftDoorTrans.y,0));
					leftDoor.setSpriteRotation(90.0f);					
					rightDoor.setSpritePos(D3DXVECTOR3(rightDoorTrans.x,rightDoorTrans.y,0));
					rightDoor.setSpriteRotation(90.0f);
					*/

					thePlayer.update();
					healthBar.update();
					/*
					upDoor.update();
					downDoor.update();
					leftDoor.update();
					rightDoor.update();
					*/

					/*					
					if (thePlayer.collidedWith(thePlayer.getBoundingRect(),upDoor.getBoundingRect()))
					{
						//if a collision occurs change the room
						OutputDebugString("Collision!!");	
						for(int i=0; i<=4; i++)
						{
							if(rooms[i].getPosY() == (currentRoom.getPosY())+1)
							{
								currentRoom = rooms[i];
								roomSpawned = false;
							}
						}						
					}
					*/				

					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(roomSurface, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
			
					d3dxSRMgr->beginDraw();				
					d3dxSRMgr->setTheTransform(thePlayer.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(thePlayer.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					d3dxSRMgr->setTheTransform(healthBar.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(healthBar.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					
					d3dxSRMgr->setTheTransform(gooSprite1->getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(gooSprite1->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					
					d3dxSRMgr->setTheTransform(gooSprite2->getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(gooSprite2->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					
					d3dxSRMgr->setTheTransform(gooSprite3->getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(gooSprite3->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					
					d3dxSRMgr->setTheTransform(gooSprite4->getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(gooSprite4->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);

					
					//d3dxSRMgr->setTheTransform(projectile->getSpriteTransformMatrix());
					//d3dxSRMgr->drawSprite(projectile->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					
					
					
					/*
					d3dxSRMgr->setTheTransform(upDoor.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(upDoor.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					d3dxSRMgr->setTheTransform(downDoor.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(downDoor.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					d3dxSRMgr->setTheTransform(leftDoor.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(leftDoor.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					d3dxSRMgr->setTheTransform(rightDoor.getSpriteTransformMatrix());
					d3dxSRMgr->drawSprite(rightDoor.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					*/
					d3dxSRMgr->endDraw();
					d3dMgr->endRender();
				
					previousTime = currentTime;
				}
			}			

		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}