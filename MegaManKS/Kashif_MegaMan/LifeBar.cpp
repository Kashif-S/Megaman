#include "stdafx.h"
#include "LifeBar.h"


LifeBar::LifeBar(MegamanObject *m)
{
	megaman = m;
}
void LifeBar::draw(HDC screen)
{
	int height = 80*(double)megaman->curhealth / megaman->tothealth;

	HBRUSH hbrRed, hbrWhite;

	hbrRed = CreateSolidBrush(RGB(255,0,0));
	hbrWhite = CreateSolidBrush(RGB(255,255,255));

	SelectObject(screen, hbrWhite);
	Rectangle (screen, 10,10,20,90);

	SelectObject(screen, hbrRed);
	Rectangle (screen, 10,90 - height,20,90);

	DeleteObject(hbrRed);
	DeleteObject(hbrWhite);


}
LifeBar::~LifeBar(void)
{
}
