
#define Farmer_PngWidth (256)
#define Farmer_PngHeight (96)
#define Farmer_PngWidthF (256.f)
#define Farmer_PngHeightF (96.f)
#define Farmer_FrameSize 32
#define Farmer_FrameSizeF 32.f
#define Farmer_FrameAnimationTime 1.0f

#define Farmer_Rect(u,v) { (u)/Farmer_PngWidthF, (v)/Farmer_PngHeightF, (u+Farmer_FrameSizeF)/Farmer_PngWidthF, (v+Farmer_FrameSizeF)/Farmer_PngHeightF }


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
	{-16.f,22.f, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, -8.f,20.f,6.f,0.f},
	{-16.f,22.f, -8.f,20.f,6.f,0.f}
};


AnimRectTime Farmer_Time = { Farmer_FrameAnimationTime, ARRAYSIZE(Farmer_up) };

