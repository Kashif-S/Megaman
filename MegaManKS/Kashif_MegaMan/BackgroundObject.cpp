#include "StdAfx.h"
#include "BackgroundObject.h"
#include "resource.h"


BackgroundObject::BackgroundObject(int i,int posX, int posY, int h, int w, double ss) : GraphicsObject(i,0, posX, posY)
{
	height = h;
	width = w;
	 scrollSpeed = ss;
}
void BackgroundObject::draw(HDC offscreenDC)
{ 

	

	int relativeX = (int)((x - mapPosition)*scrollSpeed) % width;
	BitBlt(offscreenDC,relativeX,y,width,height,image,0,0,SRCCOPY);
	BitBlt(offscreenDC,relativeX - width,y,width,height,image,0,0,SRCCOPY);
	BitBlt(offscreenDC,relativeX + width,y,width,height,image,0,0,SRCCOPY);
}
BackgroundObject::~BackgroundObject(void)
{
}
