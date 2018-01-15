#include "StdAfx.h"
#include "GroundEnemy.h"
#include"Resource.h"
#include "RedBullet.h"

GroundEnemy::GroundEnemy(void) : EnemyObject(IDB_ENEMYPIC, IDB_ENEMYMASK, 200, 200)
{
	width = 26;
	xspeed = -5;
	height = 35;
	currcell = 0;
	startcell = 0;
	endcell = 10;
	hitHeight = 39;
	loopcell = true;
	numBullets = 5;
	isDead = false;
	health = 2;
	for(int i = 0; i < numBullets; i++){
		bullets[i]= new RedBullet();
	}
}

void GroundEnemy::move()
{
	prevX = x;
	prevY = y;

	y += yspeed;


	yspeed += GRAVITY;

	if(y> GROUND - height) {
		y = GROUND - height;
		yspeed = 0;
	}
	if(!isDead)
	{
		x += xspeed;

	int rum = rand()%30;

	if(rum == 1){

		if(xspeed < 0){
			fireBullet(x + 10, y + 20, -10, 0);
		}else if(xspeed > 0){
			fireBullet(x + 10, y + 20, 10, 0);
		}
	}
	}

	animate();
}
void GroundEnemy::onHit(BulletObject *b)
{
	x+= b->xspeed;

	
	
	if (health == 0){
	isDead = true;
	currcell = 0;
	endcell = 0;

	if (xspeed < 0){
		picY = 70;
	}else{
		picY = 105;
	}
	}else{
	health -= 1;
	}
	
	
}
void GroundEnemy::checkCollisionWithBlock(GraphicsObject *block)
	{
		if (hitTest(*block)){
			if(prevX +  hitWidth <= block ->x){ 
				xspeed *= -1;
				x = block->x - hitWidth;
				picY = 0;
			}else if(prevX >= block->x + block->hitWidth){
				xspeed *= -1;
				x = block->x + block->hitWidth;
				picY = 36;
			}else if(prevY +  hitHeight <= block ->y){
				yspeed = 0;
				y = block->y - hitHeight;
			}else if(prevY >= block->y + block->hitHeight){
				yspeed *= -1;
				y = block->y + block->hitHeight;
			}
		}
	}
GroundEnemy::~GroundEnemy(void)
{
}
