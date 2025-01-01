#pragma once
#include "DxTexture.h"

struct VERTEX;


struct Renderable
{
	Pos_t* pos;

	float w,h;
	float ancherX,  ancherY;
	XFloat4 color;

	Img_t* img;
};


struct Dx2DRenderable2 : public Renderable
{
	STexture tex;

	Vec2 vel;
	CollisionRect* colRect;
};


class IRenderer
{
public:
	virtual void Draw2(Dx2DRenderable2* sprite) = 0;
	virtual void TogglePS() = 0;
};


