#include "StdAfx.h"
#include "BlueBullet.h"
#include "Resource.h"


BlueBullet::BlueBullet(void) : BulletObject(IDB_fireball, IDB_fireballmask)
{
	height = 12;
	width = 12;
	hitHeight = 12;
	hitWidth = 12;
}
void BlueBullet::setExplode()
{
	picY = 12;
	picX = 0;
	width = 32;
	height = 32;
	x -= 8;
	y -= 8;
	loopcell = false;
	endcell = 2;
	currcell = 0;
	exploding = true;
}
void BlueBullet::reset()
{
	exploding = false;
	fired = false;
	picY = 0;
	picX = 0;
	currcell = 0;
	endcell = 0;
	width = 12;
	height = 12;
	distanceTravelled = 0;
}

BlueBullet::~BlueBullet(void)
{
}
