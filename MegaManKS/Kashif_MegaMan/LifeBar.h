#pragma once
#include"GraphicsObject.h"
#include"MegamanObject.h"
#include"Resource.h"

class LifeBar
{
public:
	LifeBar(MegamanObject *m);
	MegamanObject *megaman;
	void draw(HDC screen);
	~LifeBar(void);
};

