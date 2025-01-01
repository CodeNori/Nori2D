
#define Farmer_PngWidth (256)
#define Farmer_PngWidthF (256.f)

#define Farmer_PngHeight (96)
#define Farmer_PngHeightF (96.f)

#define Farmer_FrameWidth 32
#define Farmer_FrameWidthF 32.f

#define Farmer_FrameHeight 32
#define Farmer_FrameHeightF 32.f

#define Farmer_FrameAnimationTime 1.0f

#define Farmer_Rect(u,v) { (u)/Farmer_PngWidthF, (v)/Farmer_PngHeightF, (u+Farmer_FrameWidthF)/Farmer_PngWidthF, (v+Farmer_FrameHeightF)/Farmer_PngHeightF }


UltraRect Farmer_up[] = {
	Farmer_Rect(0.f, 0.f),
	Farmer_Rect(32.f, 0.f),
	Farmer_Rect(64.f, 0.f),
	Farmer_Rect(96.f, 0.f),
	Farmer_Rect(128.f, 0.f),
	Farmer_Rect(160.f, 0.f)
};
UltraRect Farmer_down[] = {
	Farmer_Rect(192.f, 0.f),
	Farmer_Rect(224.f, 0.f),

	Farmer_Rect(0.f, 32.f),
	Farmer_Rect(32.f, 32.f),
	Farmer_Rect(64.f, 32.f),
	Farmer_Rect(96.f, 32.f)
};
UltraRect Farmer_left[] = {
	Farmer_Rect(128.f, 32.f),
	Farmer_Rect(160.f, 32.f),
	Farmer_Rect(192.f, 32.f),
	Farmer_Rect(224.f, 32.f),
	
	Farmer_Rect(0.f, 64.f),
	Farmer_Rect(32.f, 64.f),
};
UltraRect Farmer_right[] = {
	Farmer_Rect(64.f, 64.f),
	Farmer_Rect(96.f, 64.f),
	Farmer_Rect(128.f, 64.f),
	Farmer_Rect(160.f, 64.f),
	Farmer_Rect(192.f, 64.f),
	Farmer_Rect(224.f, 64.f)
};

UltraAnchor Farmer_A_up[] = {
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, Farmer_FrameWidthF,Farmer_FrameHeightF, -8.f,20.f,6.f,0.f}
};


AnimRectTime Farmer_Time = { Farmer_FrameAnimationTime, ARRAYSIZE(Farmer_up) };

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



void GetActorVertexUV_Farmer(Dx2DRenderable2* rd, VERTEX* vt)
{
	UltraRect* frames = Farmer_CalcAniDir(rd->vel);
	UltraRect& uv = frames[rd->img->frameNo];
	UltraAnchor anchor = Farmer_A_up[rd->img->frameNo];

	float left = rd->pos->x+anchor.a_x;
	float top = rd->pos->y+anchor.a_y;
	float right = left+anchor.a_w;
	float bottom = top-anchor.a_h;

	vt[0] = { left,  bottom, 0.f, uv.U1, uv.V2  };
	vt[1] = { left,     top, 0.f, uv.U1, uv.V1  };
	vt[2] = { right, bottom, 0.f, uv.U2, uv.V2  };
	vt[3] = { right,    top, 0.f, uv.U2, uv.V1  };

	rd->colRect->left = anchor.physics_x1;
	rd->colRect->right = anchor.physics_x2;
	rd->colRect->top = anchor.physics_y1;
	rd->colRect->bottom = anchor.physics_y2;

	vt[0].X = (vt[0].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[0].Y = (vt[0].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[1].X = (vt[1].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[1].Y = (vt[1].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[2].X = (vt[2].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[2].Y = (vt[2].Y - g_CameraPos.y) / g_Dx11.half_height;
	vt[3].X = (vt[3].X - g_CameraPos.x) / g_Dx11.half_width;
	vt[3].Y = (vt[3].Y - g_CameraPos.y) / g_Dx11.half_height;
}

