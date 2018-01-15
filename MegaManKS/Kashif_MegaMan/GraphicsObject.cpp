#include "StdAfx.h"
#include "GraphicsObject.h"
#include "resource.h"


GraphicsObject::GraphicsObject(int i,int m, int posx, int posy, int w, int h)
{
	ID = i;
	maskID = m;
	width = w;
	height = h;
	hitHeight = height;
	hitWidth = width;
	x = posx;
	y = posy;
	currcell = 0;
	startcell = 0;
	endcell = 0;
	loopcell = true;
	picX = 0;
	picY = 0;
	loadImage();
}
void GraphicsObject::loadImage()
{
	HDC hTempDC;
	BITMAP bmTemp;
	HBITMAP imageBMP;
	HBITMAP imageMask;
	hTempDC = GetDC(0);

	//initialize graphics picture
	imageBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),(LPCWSTR)ID, IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);

	image = CreateCompatibleDC(hTempDC);

	SelectObject(image, imageBMP);//freeing up memory

	imageMask = (HBITMAP)LoadImage(GetModuleHandle(NULL),(LPCWSTR)maskID, IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	
	mask = CreateCompatibleDC(hTempDC);

	SelectObject(mask, imageMask);
	
	ReleaseDC(0,hTempDC);
}
void GraphicsObject::draw(HDC offscreenDC)
{
	BitBlt(offscreenDC,x - mapPosition,y,width,height,mask,picX,picY,SRCAND);
	BitBlt(offscreenDC,x - mapPosition,y,width,height,image,picX,picY,SRCPAINT);
}
void GraphicsObject::animate()
{
	//updates the current cell
	currcell += 1;

	if (currcell>=endcell){
		if (loopcell == true){
		currcell = startcell;
		}else{
		currcell = endcell;
	}
	}

	picX = width * currcell;

}
bool GraphicsObject::hitTest(GraphicsObject object)
{
	if(x+ hitWidth > object.x){
		if(x< object.x + object.hitWidth){
			if(y + hitHeight > object.y){
				if(y < object.y + object.hitHeight){
					return true;
				}
			}
		}
	}
	return false;
}

GraphicsObject::~GraphicsObject(void)
{
}
