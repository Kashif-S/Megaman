#pragma once
#include "bulletobject.h"
class RedBullet :
	public BulletObject
{
public:
	RedBullet(void);
	void setExplode();
	void reset();
	~RedBullet(void);
};

