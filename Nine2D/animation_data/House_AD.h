
#define House_PngWidth (64)
#define House_PngWidthF (64.f)

#define House_PngHeight (80)
#define House_PngHeightF (80.f)

#define House_FrameWidth 64
#define House_FrameWidthF 64.f

#define House_FrameHeight 80
#define House_FrameHeightF 80.f

#define House_FrameAnimationTime 2.0f

#define House_Rect(u,v) { (u)/House_PngWidthF, (v)/House_PngHeightF, (u+House_FrameWidthF)/House_PngWidthF, (v+House_FrameHeightF)/House_PngHeightF }


UltraRect House_up[] = {
	House_Rect(0.f, 0.f),
	House_Rect(0.f, 0.f)
};

UltraAnchor House_A_up[] = {
	{-31.f,77.f, House_FrameWidthF,House_FrameHeightF, -27.f,65.f, 27.f,0.f},
	{-31.f,77.f, House_FrameWidthF,House_FrameHeightF, -27.f,65.f, 27.f,0.f},
};


AnimRectTime House_Time = { House_FrameAnimationTime, ARRAYSIZE(House_up) };



void GetActorVertexUV_House(Dx2DRenderable2* rd, VERTEX* vt)
{
	UltraRect* frames = House_up;
	UltraRect& uv = frames[0];
	UltraAnchor& anchor = House_A_up[rd->img->frameNo];
	float left = rd->pos->x+anchor.a_x;
	float top = rd->pos->y+anchor.a_y;

	vt[0] = { left,                   top-House_FrameHeightF, 0.f, uv.U1, uv.V2  };
	vt[1] = { left, top, 0.f, uv.U1, uv.V1  };
	vt[2] = { left+House_FrameWidthF, top-House_FrameHeightF, 0.f, uv.U2, uv.V2  };
	vt[3] = { left+House_FrameWidthF,                   top, 0.f, uv.U2, uv.V1  };

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
