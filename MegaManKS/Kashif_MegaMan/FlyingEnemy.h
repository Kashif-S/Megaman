#pragma once
#include "enemyobject.h"
#include "MegamanObject.h"
class FlyingEnemy :
	public EnemyObject
{
public:
	FlyingEnemy(MegamanObject *m, int cx, int cy);
	MegamanObject *megaman;
	int radius;
	int angle;
	int centerx;
	int centery;
	virtual void move();
	virtual void onHit(BulletObject *b);
	virtual void checkCollisionWithBlock(GraphicsObject *block);
	virtual void fire();
	~FlyingEnemy(void);
};

