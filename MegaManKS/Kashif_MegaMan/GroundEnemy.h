#pragma once
#include "BulletObject.h"
#include "EnemyObject.h"

class GroundEnemy :
	public EnemyObject
{
public:
	GroundEnemy(void);
	int prevX;
	int prevY;
	int health;
	void checkCollisionWithBlock(GraphicsObject *block);
	void onHit(BulletObject *b);
	void move();
	~GroundEnemy(void);
};

