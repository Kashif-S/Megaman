#include "stdafx.h"
#include "Resource.h"
#include "FlyingEnemy.h"
#include "RedBullet.h"
#include <math.h>

FlyingEnemy::FlyingEnemy(MegamanObject *m, int cx, int cy) : EnemyObject(IDB_FlyingEnemy2, IDB_FlyingEnemy2Mask, cx + radius, cy)
{
	height = 39;
	width = 28;
	hitHeight = 39;
	hitWidth = 28;
	currcell = 0;
	endcell = 4;
	startcell = 0;
	loopcell = true;
	xspeed = -5;
	yspeed = 0;
	radius = 20;
	centerx = 200;
	centery = 200;
	angle = 0;
	numBullets =20; 

	for (int i = 0; i < numBullets; i++)
	{
		bullets[i] = new RedBullet();
	}
}
void FlyingEnemy::move()
{
	
	double radians = (double)angle/180 * 3.14159265;

	x = centerx + radius *cos(radians);
	y = centery + radius *sin(radians);

	angle += 10;

	fire();
	animate();
}
void FlyingEnemy::onHit(BulletObject *b)
{
	startcell = 0;
	width = 32;
	height = 32;
	endcell = 6;
	currcell = 0;
	picX = 0;
	picY = 156;
	loopcell = false;
	isDead = true;
}
void FlyingEnemy::checkCollisionWithBlock(GraphicsObject *block)
{
}
void FlyingEnemy::fire()
{
	//double xDistance = abs((x + width/2) - (megaman->x + megaman->width/2));
	//double yDistance = abs((y + height) - (megaman->y + megaman->height/2));

	//int xside = 1;
	//int yside = 1;

	//if (megaman->x < x)
		//xside = -1;

	//if (megaman->y < y)
		//yside = -1;

	//if (xDistance > yDistance){
		//fireBullet(x + width/2, y + height, 10*xside, 10*yDistance/xDistance * yside);
	//}else{
		//fireBullet(x + width/2, y + height, 10*xDistance/yDistance * xside, 10 *yside);
	//}
}
FlyingEnemy::~FlyingEnemy(void)
{
}
