#pragma once
#include "weaponsobject.h"
class EnemyObject :
	public WeaponsObject
{
public:

	EnemyObject(int i, int m, int posx, int posy) : WeaponsObject(i, m, posx, posy)
	{
		xspeed = 0;
		yspeed = 0;
		isDead = false;
	}
	int xspeed;
	int yspeed;
	bool isDead;
	virtual void move() = 0;
	virtual void onHit(BulletObject *b) = 0;
	virtual void checkCollisionWithBlock(GraphicsObject *block) = 0;
	~EnemyObject(void)
	{
	}
};

