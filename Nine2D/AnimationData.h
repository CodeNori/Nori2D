#pragma once
#include "renderer/Dx2DRenderable.h"

struct UltraRect
{
	float U1, V1;
	float U2, V2;
};

struct AnimRectTime
{
	float totalTime;
	float totalFrame;
};

#include "animation_data/Ultra_AD.h"

UltraRect& GetActorUV(Dx2DRenderable* rd)
{
	if (rd->tex.mName == ULTRA_FILE_NAME)
	{
		rd->ancherX = 0.5f;
		rd->ancherY = 0.5f;
		rd->h = UltraFrameSizeF;
		rd->w = UltraFrameSizeF;

		UltraRect* frames = UltraFrameAni_Dir[rd->dir];
		return frames[rd->frameNo];

	}
	return Ultra_0[0];
}

AnimRectTime& GetActorTime(Dx2DRenderable* rd)
{
	if (rd->tex.mName == ULTRA_FILE_NAME)
	{
		return Ultra_Time;
	}

	return Ultra_Time;
}

int GetRadianToAnimIndex(float rad) 
{
	float angle;
	angle = MATH_RAD_TO_DEG(rad);
	
	int dir;
	
	if (angle > 0)
	{
		angle += 11.25f;
		dir = angle / 22.5;
	}
	else
	{
		angle -= 11.25f;
		dir = angle / 22.5;
		dir = dir + 16;
		if (dir == 16)
			dir = 0;
	}

	return dir;
}

