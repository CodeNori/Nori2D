#pragma once
#include "DxTexture.h"

struct VERTEX;


struct Renderable
{
	Vec2 position;
	float angle;

	float w,h;
	float ancherX,  ancherY;
	XFloat4 color;

	int dir;
	int frameNo;
	float AnimTime;

};

struct Dx2DRenderable : public Renderable
{
	DxTexture tex;
};

struct Dx2DRenderable2 : public Renderable
{
	STexture tex;

	Vec2 vel;
};


class IRenderer
{
public:
	virtual void Draw(Dx2DRenderable* sprite) = 0;
	virtual void Draw2(Dx2DRenderable2* sprite, CollisionRect* rc) = 0;
	virtual void TogglePS() = 0;
};


