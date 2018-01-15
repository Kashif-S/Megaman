#pragma once
#include "graphicsobject.h"
#include "resource.h"
class BulletObject :
	public GraphicsObject
{
public:
	BulletObject(int i, int m);
	int xspeed;
	int yspeed;
	int distanceTravelled;
	int maxDistance;
	bool fired;
	bool exploding;
	void move();
	virtual void setExplode();
	virtual void reset();
	int damage;
	~BulletObject(void);
};

