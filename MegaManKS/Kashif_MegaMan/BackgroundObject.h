#pragma once
#include "GraphicsObject.h"

class BackgroundObject : public GraphicsObject
{
public:
	BackgroundObject(int i, int posX, int posY, int h, int w, double ss);
	 void draw(HDC offscreenDC);
	double scrollSpeed;
	~BackgroundObject(void);
};

