#pragma once
#include "bulletobject.h"
class BlueBullet :
	public BulletObject
{
public:
	BlueBullet(void);
	void setExplode();
	void reset();
	~BlueBullet(void);
};

