#include "StdAfx.h"
#include "WeaponsObject.h"



WeaponsObject::WeaponsObject(int i, int m, int posX, int posY): GraphicsObject(i, m, posX, posY)
{

}
	void WeaponsObject::fireBullet(int x, int y, int xspeed, int yspeed){
				for(int i = 0; i < numBullets; i++){
				if(bullets[i]->fired == false){
					bullets[i]->xspeed = xspeed;
					bullets[i]->yspeed = yspeed;
					bullets[i]->fired = true;
					bullets[i]->x = x;
					bullets[i]->y = y;
					bullets[i]->distanceTravelled = 0;
					break;
			}
		}
	}
	void WeaponsObject::drawBullets(HDC offscreenDC){
		
		for(int i = 0; i < numBullets; i++){
			if(bullets[i]->fired == true){
		bullets[i]->draw(offscreenDC);
			}
		}
	}
	void WeaponsObject::moveBullets(){
				for(int i = 0; i < numBullets; i++){
			if(bullets[i]->fired == true){
		bullets[i]->move();
			}
		}
	}
void WeaponsObject::checkBulletCollsionWithBlock(GraphicsObject *block)
{
	for (int i = 0; i < numBullets; i++){
		if (bullets[i]->fired == true && bullets[i]->exploding == false){
			if(bullets[i]->hitTest(*block) == true){
				bullets[i]->setExplode();
			}
		}
	}
}
void WeaponsObject::checkBulletCollisionWithObject(WeaponsObject *object)
{
	for (int i = 0; i < numBullets; i++){
		if (bullets[i]->fired == true && bullets[i]->exploding == false){
			if(bullets[i]->hitTest(*object) == true){
				object->onHit(bullets[i]);
				bullets[i]->setExplode();
			}
		}
	}
}
WeaponsObject::~WeaponsObject(void)
{
}
