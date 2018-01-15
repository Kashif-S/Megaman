#pragma once
#include "WeaponsObject.h"
#include "BulletObject.h"
#define MOVERIGHT 1
#define MOVELEFT 2
#define STANDRIGHT 3
#define STANDLEFT 4
#define JUMPRIGHT 5
#define JUMPLEFT 6
#define SHOOTRIGHT 7
#define SHOOTLEFT 8

class MegamanObject : public WeaponsObject
{
public:
	MegamanObject(void);
	int prevX;
	int prevY;
	int Yspeed;
	int Xspeed;
	int state;
	int tothealth;
	int curhealth;
	void move();
	void setMoveRight();
	void setMoveleft();
	void setStandRight();
	void setStandleft();
	void setJumpRight();
	void setJumpleft();
	void setShootRight();
	void setShootLeft();
	bool isJumping();
	void onHit(BulletObject *b);
	void checkCollsionWithBlock(GraphicsObject *block);
	~MegamanObject(void);
};

