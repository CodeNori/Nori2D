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
#include "animation_data/Farmer_AD.h"

#define AX_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f)  // PI / 180

UltraRect* Farmer_CalcAniDir(Vec2 mVelocity)
{
    float cos45 = cos(AX_DEGREES_TO_RADIANS(45));

    if (mVelocity.x > cos45)
        return Farmer_right;

    if (mVelocity.x < -cos45)
        return Farmer_left;

    if (mVelocity.y > 0)
        return Farmer_up;

    return Farmer_down;
}


UltraRect& GetActorUV(Dx2DRenderable* rd)
{
	if (rd->tex.mName == ULTRA_FILE_NAME)
	{
		rd->ancherX = 0.5f;
		rd->ancherY = 0.5f;
		rd->h = Ultra_FrameSizeF;
		rd->w = Ultra_FrameSizeF;

		UltraRect* frames = UltraFrameAni_Dir[rd->dir];
		return frames[rd->frameNo];

	}
	if (rd->tex.mName == FARMER_FILE_NAME)
	{
		rd->ancherX = 0.5f;
		rd->ancherY = 0.5f;
		rd->h = Farmer_FrameSizeF;
		rd->w = Farmer_FrameSizeF;

		UltraRect* frames = Farmer_down; //UltraFrameAni_Dir[rd->dir];
		return frames[rd->frameNo];

	}


	return Ultra_0[0];
}

UltraRect& GetActorUV2(Dx2DRenderable2* rd)
{
	if (rd->tex.mName == ULTRA_FILE_NAME)
	{
		rd->ancherX = 0.5f;
		rd->ancherY = 0.5f;
		rd->h = Ultra_FrameSizeF;
		rd->w = Ultra_FrameSizeF;

		UltraRect* frames = UltraFrameAni_Dir[rd->dir];
		return frames[rd->frameNo];

	}
	if (rd->tex.mName == FARMER_FILE_NAME)
	{
		rd->ancherX = 0.5f;
		rd->ancherY = 0.5f;
		rd->h = Farmer_FrameSizeF;
		rd->w = Farmer_FrameSizeF;

		UltraRect* frames = Farmer_CalcAniDir(rd->vel);
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
	if (rd->tex.mName == FARMER_FILE_NAME)
	{
		return Farmer_Time;
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




