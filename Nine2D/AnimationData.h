#pragma once
#include "renderer/Dx2DRenderable.h"

struct UltraRect
{
	float U1, V1;
	float U2, V2;
};

struct UltraAnchor
{
	float a_x, a_y;   // 이미지 안에서 중점 (Pixel)
	float a_w, a_h;   // Width, Height

	float physics_x1, physics_y1;  // 중점을 기준으로 Left, Top 의 상대위치
	float physics_x2, physics_y2;	// 중점을 기준으로 Right, Bottom 의 상대위치
};



struct AnimRectTime
{
	float totalTime;
	float totalFrame;
};

#define AX_DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f)  // PI / 180

#include "animation_data/Ultra_AD.h"
#include "animation_data/Farmer_AD.h"
#include "animation_data/House_AD.h"




void GetActorVertexUV_Ultra(Dx2DRenderable2* rd, VERTEX* vt)
{
	//if (rd->tex.mName == ULTRA_FILE_NAME)
	//{
		UltraRect* frames = UltraFrameAni_Dir[rd->img->dir];
		UltraRect& uv = frames[rd->img->frameNo];
		float a_x = -Ultra_FrameSizeF/2.f;
		float a_y = (Ultra_FrameSizeF/2.f);
		vt[1] = { rd->pos->x+a_x,             rd->pos->y+a_y, 0.f, uv.U1, uv.V1  };
		vt[0] = { vt[1].X,                  vt[1].Y-Ultra_FrameSizeF, 0.f, uv.U1, uv.V2  };
		vt[2] = { vt[1].X+Ultra_FrameSizeF, vt[1].Y-Ultra_FrameSizeF, 0.f, uv.U2, uv.V2  };
		vt[3] = { vt[1].X+Ultra_FrameSizeF,                  vt[1].Y, 0.f, uv.U2, uv.V1  };
	//}

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
	if (rd->tex.mName == TOWNHALL_FILE_NAME) animTime = House_Time;

	float FrameTime = animTime.totalTime / animTime.totalFrame;

	rd->img->AnimTime += g_Time.deltaTime;

	if (rd->img->AnimTime >= FrameTime)
	{
		rd->img->frameNo++;
		rd->img->AnimTime -= FrameTime;
		if (rd->img->frameNo >= animTime.totalFrame)
			rd->img->frameNo = 0;
	}

	if (rd->tex.mName == ULTRA_FILE_NAME) GetActorVertexUV_Ultra(rd,Vt);
	if (rd->tex.mName == FARMER_FILE_NAME) GetActorVertexUV_Farmer(rd,Vt);
	if (rd->tex.mName == TOWNHALL_FILE_NAME) GetActorVertexUV_House(rd,Vt);

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

void CalcNextAnimFrame(Img_t* img)
{
	AnimRectTime animTime;
	if (img->texName == ULTRA_FILE_NAME) animTime = Ultra_Time;
	if (img->texName == FARMER_FILE_NAME) animTime = Farmer_Time;
	if (img->texName == TOWNHALL_FILE_NAME) animTime = House_Time;

	float FrameTime = animTime.totalTime / animTime.totalFrame;

	img->AnimTime += g_Time.deltaTime;

	if (img->AnimTime >= FrameTime)
	{
		img->frameNo++;
		img->AnimTime -= FrameTime;
		if (img->frameNo >= animTime.totalFrame)
			img->frameNo = 0;
	}

}

CollisionRect FindCollisionRect(Img_t* img)
{
	UltraAnchor* array = nullptr;
	if (img->texName == ULTRA_FILE_NAME) array = Ultra_A_up;
	if (img->texName == FARMER_FILE_NAME) array = Farmer_A_up;
	if (img->texName == TOWNHALL_FILE_NAME) array = House_A_up;

	UltraAnchor& anchor = array[img->frameNo];

	return { anchor.physics_x1, anchor.physics_x2, anchor.physics_y1, anchor.physics_y2, 0 };
}


