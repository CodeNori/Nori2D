#pragma once
#include "renderer/Dx2DRenderable.h"

struct UltraRect
{
	float U1, V1;
	float U2, V2;
};
struct UltraAnchor
{
	float a_x, a_y;
	float physics_x1, physics_y1;
	float physics_x2, physics_y2;
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


void GetActorVertexUV(Dx2DRenderable2* rd, VERTEX* vt)
{
	if (rd->tex.mName == ULTRA_FILE_NAME)
	{
		UltraRect* frames = UltraFrameAni_Dir[rd->dir];
		UltraRect& uv = frames[rd->frameNo];
		float a_x = -Farmer_FrameSizeF/2.f;
		float a_y = (Farmer_FrameSizeF/2.f);
		vt[1] = { rd->position.x+a_x,             rd->position.y+a_y, 0.f, uv.U1, uv.V1  };
		vt[0] = { vt[1].X,                  vt[1].Y-Ultra_FrameSizeF, 0.f, uv.U1, uv.V2  };
		vt[2] = { vt[1].X+Ultra_FrameSizeF, vt[1].Y-Ultra_FrameSizeF, 0.f, uv.U2, uv.V2  };
		vt[3] = { vt[1].X+Ultra_FrameSizeF,                  vt[1].Y, 0.f, uv.U2, uv.V1  };
	}
	if (rd->tex.mName == FARMER_FILE_NAME)
	{
		UltraRect* frames = Farmer_CalcAniDir(rd->vel);
		UltraRect& uv = frames[rd->frameNo];
		UltraAnchor& anchor = Farmer_A_up[rd->frameNo];
		vt[1] = { rd->position.x+anchor.a_x, rd->position.y+anchor.a_y, 0.f, uv.U1, uv.V1  };
		vt[0] = { vt[1].X,                   vt[1].Y-Farmer_FrameSizeF, 0.f, uv.U1, uv.V2  };
		vt[2] = { vt[1].X+Farmer_FrameSizeF, vt[1].Y-Farmer_FrameSizeF, 0.f, uv.U2, uv.V2  };
		vt[3] = { vt[1].X+Farmer_FrameSizeF,                   vt[1].Y, 0.f, uv.U2, uv.V1  };

		rd->colRect->left = anchor.physics_x1;
		rd->colRect->right = anchor.physics_x2;
		rd->colRect->top = anchor.physics_y1;
		rd->colRect->bottom = anchor.physics_y2;
	}

	vt[0].X = (vt[0].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[0].Y = (vt[0].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[1].X = (vt[1].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[1].Y = (vt[1].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[2].X = (vt[2].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[2].Y = (vt[2].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[3].X = (vt[3].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[3].Y = (vt[3].Y - g_CameraPos.y) / g_Dx11.half_height;
}



void GetActorAnimVertexUV(Dx2DRenderable2* rd, VERTEX* Vt)
{
	AnimRectTime animTime;
	if (rd->tex.mName == ULTRA_FILE_NAME) animTime = Ultra_Time;
	if (rd->tex.mName == FARMER_FILE_NAME) animTime = Farmer_Time;

	float FrameTime = animTime.totalTime / animTime.totalFrame;

	rd->AnimTime += g_Time.deltaTime;

	if (rd->AnimTime >= FrameTime)
	{
		rd->frameNo++;
		rd->AnimTime -= FrameTime;
		if (rd->frameNo >= animTime.totalFrame)
			rd->frameNo = 0;
	}

	GetActorVertexUV(rd,Vt);

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




