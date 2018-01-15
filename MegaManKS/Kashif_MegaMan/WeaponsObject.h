#pragma once
#include "graphicsobject.h"
#include "BulletObject.h"
class WeaponsObject :
	public GraphicsObject
{
public:
	WeaponsObject(int i, int m, int posX, int posY);
	int numBullets;
	BulletObject *bullets[50];
	void fireBullet(int x, int y, int xspeed, int yspeed);
	void drawBullets(HDC offscreenDC);
	void moveBullets();
	void checkBulletCollsionWithBlock(GraphicsObject *block);
	void checkBulletCollisionWithObject(WeaponsObject *object);
	virtual void onHit(BulletObject *b){};
	~WeaponsObject(void);
};

