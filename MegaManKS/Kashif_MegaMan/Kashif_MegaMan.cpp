// Kashif_MegaMan.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Kashif_MegaMan.h"
#include "GraphicsObject.h"
#include "MegamanObject.h"
#include "BackgroundObject.h"
#include "GroundEnemy.h"
#include "EnemyObject.h"
#include "FlyingEnemy.h"
#include "LifeBar.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void setScreen();
void drawScreen(HWND hWnd);
void loadMap();

int mapPosition = 0;
HDC offscreenDC;

MegamanObject megaman;
GraphicsObject block(IDB_BigBlock,IDB_BigBlockMask, 400, 400, 64, 64);
GraphicsObject enemy(IDB_FlyingEnemy,IDB_FlyingEnemyMask, 50, 50);
BackgroundObject background(IDB_Background,0,0,800,2560,0.2);
BackgroundObject ground(IDB_groundd,0,GROUND,128,774,1);
GraphicsObject *blockArray[100];
LifeBar lifebar(&megaman);
int numBlocks = 0;
EnemyObject *enemyArray[100];
int numEnemies = 0;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KASHIF_MEGAMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KASHIF_MEGAMAN));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KASHIF_MEGAMAN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_KASHIF_MEGAMAN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 700, 550, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

  
   loadMap();
   enemyArray[numEnemies] = new FlyingEnemy(&megaman, 200, 200);
   numEnemies++;
   setScreen();
   SetTimer(hWnd, 1, 50, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN: 
		switch(wParam)
		{
		case VK_RIGHT:
			if (megaman.isJumping() == true){
				megaman.picY = 82;
				megaman.Xspeed = 10;
				megaman.state =JUMPRIGHT;
		}else{
			megaman.setMoveRight();
		}
			break;
		case VK_LEFT:
			if (megaman.isJumping() == true){
				megaman.picY = 135;
				megaman.Xspeed = -10;
				megaman.state =JUMPLEFT;
		}else{
			megaman.setMoveleft();
			}
			break;
		case VK_UP:
			if(megaman.state == MOVELEFT || megaman.state == STANDLEFT){
				megaman.setJumpleft();
			}else if (megaman.state == MOVERIGHT || megaman.state == STANDRIGHT){
				megaman.setJumpRight();
			}
			break;
	case VK_SPACE:
		if (megaman.state == STANDLEFT){
			megaman.setShootLeft();
		}else if(megaman.state == STANDRIGHT){
			  megaman.setShootRight();
		}
		if(megaman.state == SHOOTLEFT || megaman.state == JUMPLEFT || megaman.state == MOVELEFT ){
		megaman.fireBullet(megaman.x, megaman.y + 10, megaman.Xspeed - 20, 0);
		}else{
		megaman.fireBullet(megaman.x + megaman.width - 15, megaman.y + 10, megaman.Xspeed + 20, 0);
		}
		break;
		}
	break;
	case WM_TIMER:
		megaman.move();
		megaman.checkCollsionWithBlock(&block);
		megaman.checkBulletCollsionWithBlock(&block);
		for(int i = 0; i < numBlocks; i++){
		megaman.checkCollsionWithBlock(blockArray[i]);
		megaman.checkBulletCollsionWithBlock(blockArray[i]);
		}
		for(int i = 0; i < numEnemies; i++){
			if(!enemyArray[i]->isDead)
		megaman.checkBulletCollisionWithObject(enemyArray[i]);
		enemyArray[i]->checkBulletCollisionWithObject(&megaman);
		if(!enemyArray[i]->isDead){
		for(int j = 0; j < numBlocks; j++){
			enemyArray[i]->checkCollisionWithBlock(blockArray[j]);
			enemyArray[i]->checkBulletCollsionWithBlock(blockArray[j]);
		}
		}
		}
		megaman.moveBullets();
		for(int i = 0; i < numEnemies; i++){
		enemyArray[i]->moveBullets();
		enemyArray[i]->move();
		}
		PostMessage(hWnd,WM_PAINT, 0, 0);
		break;
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_RIGHT:
			if(megaman.isJumping() == false){
			megaman.setStandRight();
			}
			break;
		case VK_LEFT:
			if(megaman.isJumping() == false){
			megaman.setStandleft();
			}
			break;

		case VK_SPACE:
		if (megaman.state == SHOOTLEFT){
			megaman.setStandleft();

		}else if(megaman.state == SHOOTRIGHT){
			  megaman.setStandRight();
	}

			break;
		}
		break;
	case WM_PAINT:
		//comment line below for "paint mode"

		hdc = BeginPaint(hWnd, &ps);
		

		background.draw(offscreenDC);
		lifebar.draw(offscreenDC);
		megaman.draw(offscreenDC);
		for (int i = 0; i < numBlocks; i++)
		{
			blockArray[i]->draw(offscreenDC);
		}
		megaman.drawBullets(offscreenDC);
		enemy.draw(offscreenDC);
		ground.draw(offscreenDC);
		for (int i = 0; i < numEnemies; i++)
		{
			enemyArray[i]->draw(offscreenDC);
			enemyArray[i]->drawBullets(offscreenDC);
		}
	
		drawScreen(hWnd);
		ReleaseDC(hWnd,hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		for (int i = 0; i < numEnemies; i++)
			delete enemyArray[i];
		for (int i = 0; i < numBlocks; i++)
			delete blockArray[i];
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void setScreen()
{
	HDC hTempDC;
	HBITMAP offscreenBMP;

	hTempDC = GetDC(0);

	offscreenDC = CreateCompatibleDC(hTempDC);
	offscreenBMP = CreateCompatibleBitmap(hTempDC, 800, 600);
	SelectObject(offscreenDC, offscreenBMP);
	ReleaseDC(0, hTempDC);
}
void drawScreen(HWND hWnd)
{
	HDC ScreenDC;

	ScreenDC = GetDC(hWnd);

	BitBlt(ScreenDC, 0, 0, 700, 550, offscreenDC, 0, 0, SRCCOPY);

	DeleteDC(ScreenDC);
}
void loadMap()
{

	FILE *file;
	file = fopen("../levels/level.ini","r");

	char section[80];
	int index = 0, x = 0, y = 0;

	while (true)
	{
		fscanf(file, "%s", section);
		

		if (strcmp(section, "[Red-Block]") == 0){
			while (true){

				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1){
					break;
				}
				blockArray[numBlocks] = new GraphicsObject(IDB_REDBLOCK, IDB_REDBLOCKMASK, x, y, 32, 32);
					
				numBlocks++;
			}
		}

		if (strcmp(section, "[Big-Block]") == 0){
			while (true){

				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1){
					break;
				}

				blockArray[numBlocks] = new GraphicsObject(IDB_BigBlock, IDB_BigBlockMask, x, y, 64, 64);
					
				numBlocks++;
			}
		}
		

		if (strcmp(section, "[Ground-Enemy]") == 0){
			while (true){

				fscanf(file, "%d %d %d", &index, &x, &y);

				if (index == -1){
					break;
				}
				enemyArray[numEnemies] = new GroundEnemy();
				enemyArray[numEnemies]->x = x;
				enemyArray[numEnemies]->y = y;
				numEnemies++;
			}
		}
		
		
		if (strcmp(section, "[End]") == 0){
			break;
		}
	}
	fclose(file);

}
