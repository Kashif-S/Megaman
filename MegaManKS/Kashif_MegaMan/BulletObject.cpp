#include "StdAfx.h"
#include "BulletObject.h"
#include "resource.h"
#include <Math.h>


BulletObject::BulletObject(int i, int m) : GraphicsObject(i, m, 0, 0)
{
	fired = false;
	exploding = false;
	height = 12;
	width = 12;
	hitHeight = 12;
	hitWidth = 12;
	distanceTravelled = 0;
	maxDistance = 460;
	xspeed = 0;
	yspeed = 0;
	damage = 10;
}

void BulletObject::setExplode()
{

}
void BulletObject::reset()
{

}
 void BulletObject::move(){
	 animate();
	 if(exploding){
		 if(currcell == endcell){
			 reset();
		 }
	 }else{
	x += xspeed;
	y += yspeed;
	distanceTravelled += abs(xspeed) + abs(yspeed);
	if(distanceTravelled > maxDistance){
		fired = false;
		distanceTravelled = 0;
	}
	 }

 }

BulletObject::~BulletObject(void)
{
}
