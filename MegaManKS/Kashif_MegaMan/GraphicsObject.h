#pragma once
class GraphicsObject
{
public:
	GraphicsObject(int i, int m, int posx, int posy, int w = 50, int h = 50);
	int ID;
	int maskID;
	int width;
	int height;
	int hitHeight;
	int hitWidth;
	int y;
	int x;
    int picX;
	int picY;
	int endcell;
	int currcell;
	int startcell;
	bool loopcell;
	void loadImage();
	HDC image;
	HDC mask;
	void draw(HDC offscreenDC);
	void animate();
	bool hitTest(GraphicsObject object);
	~GraphicsObject(void);
};

