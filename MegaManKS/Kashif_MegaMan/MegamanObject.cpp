#include "StdAfx.h"
#include "MegamanObject.h"
#include "Resource.h"
#include "BlueBullet.h"
#include "RedBullet.h"

MegamanObject::MegamanObject(void) : WeaponsObject(IDB_MegamanPic,IDB_MegamanMask, 200, 403)
{
	Xspeed = 0;
	Yspeed = 0;
	setStandRight();
	state = STANDRIGHT;
	numBullets = 10;
	for (int i = 0; i < numBullets; i++){
		bullets[i] = new BlueBullet();
	}
	hitHeight = 40;
	hitWidth = 48;
	curhealth = 100;
	tothealth = 100;
}
void MegamanObject::move()
{	
	prevX = x;
	prevY = y;
	x += Xspeed;
	y += Yspeed;

	Yspeed += GRAVITY;

	if (y > GROUND - height)
	{
		if(state == JUMPLEFT){
			setStandleft();
		}
		if(state == JUMPRIGHT){
			setStandRight();
		}
		y = GROUND - height;
		Yspeed = 0;
	}
	if((x - mapPosition < 100 && Xspeed < 0) || (x - mapPosition > 350 && Xspeed > 0))
	{
	mapPosition += Xspeed;
	}
	animate();
}
	void MegamanObject::setMoveRight()
	{
		width = 53;
		height = 41;
		picY = 0;
		endcell = 9;
		loopcell = true;
		startcell = 1;
		Xspeed = 10;
		state = MOVERIGHT;
	}
	void MegamanObject::setMoveleft()
	{
		width = 53;
		height = 41;
		picY = 41;
		endcell = 9;
		loopcell = true;
		startcell = 1;
		Xspeed = -10;
		state = MOVELEFT;
	}
	void MegamanObject::setStandRight()
	{
		currcell = 0;
		width = 50;
		height = 41;
		picY = 0;
		endcell = 0;
		loopcell = false;
		startcell = 0;
		Xspeed = 0;
		state = STANDRIGHT;
	}
	void MegamanObject::setStandleft()
	{
		currcell = 0;
		width = 50;
		height = 41;
		picY = 41;
		endcell = 0;
		loopcell = false;
		startcell = 0;
		Xspeed = 0;
		state = STANDLEFT;
	}
	void MegamanObject::setJumpRight()
	{
		currcell = 0;
		width = 48;
		height = 53;
		picY = 82;
		endcell = 5;
		loopcell = false;
		Yspeed = -30;
		state = JUMPRIGHT;
	}
	void MegamanObject::setJumpleft()
	{
		currcell = 0;
		width = 48;
		height = 53;
		picY = 135;
		endcell = 5;
		loopcell = false;
		Yspeed = -30;
		state = JUMPLEFT;
	}
	void MegamanObject::setShootRight()
	{
		currcell = 0;
		width = 55;
		height = 38;
		picY = 188;
		endcell = 0;
		loopcell = false;
	//	Xspeed = 10;
		startcell = 0;
		state = SHOOTRIGHT;
	}
	void MegamanObject::setShootLeft()
	{
		currcell = 0;
		width = 55;
		height = 38;
		picY = 227;
		endcell = 0;
		loopcell = false;
		//Xspeed = -10;
		startcell = 0;
		state = SHOOTLEFT;
	}
	bool MegamanObject::isJumping(){
		return (state == JUMPLEFT || state == JUMPRIGHT);
	}
	void MegamanObject::checkCollsionWithBlock(GraphicsObject *block)
	{
		if (hitTest(*block)){
			if(prevX +  hitWidth <= block ->x){ 
				x = block->x - hitWidth;
			}else if(prevX >= block->x + block->hitWidth){
				x = block->x + block->hitWidth;
			}else if(prevY +  hitHeight <= block ->y){
				if (state == JUMPLEFT){
					setStandleft();
				}else if(state == JUMPRIGHT){
					setStandRight();
				}
				y = block->y - hitHeight;
				Yspeed = 0;
			}else if(prevY >= block->y + block->hitHeight){
				y =block->y + block->hitHeight + 1;
				Yspeed = 0;
			}
		}
	}
void MegamanObject::onHit(BulletObject *b)
{
	x += b->xspeed;
	curhealth -= b->damage;

	if(curhealth <= 0){
		x = 20;
		y = 100;
		Yspeed = 0;
		Xspeed = 0;
		setJumpRight();
		curhealth = tothealth;
		mapPosition = 0;
	}

}
MegamanObject::~MegamanObject(void)
{
}
