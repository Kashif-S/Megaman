#include "StdAfx.h"
#include "RedBullet.h"
#include "Resource.h"


RedBullet::RedBullet(void) : BulletObject(IDB_fireballred, IDB_Shot1Mask)
{
	height = 6;
	width = 6;
	hitHeight = 6;
	hitWidth = 6;
}
void RedBullet::setExplode()
{
	picY = 6;
	picX = 0;
	width = 16;
	height = 16;
	x -= 4;
	y -= 4;
	loopcell = false;
	endcell = 2;
	currcell = 0;
	exploding = true;
}
void RedBullet::reset()
{
	exploding = false;
	fired = false;
	picY = 0;
	picX = 0;
	currcell = 0;
	endcell = 0;
	width = 6;
	height = 6;
	distanceTravelled = 0;
}

RedBullet::~RedBullet(void)
{
}
