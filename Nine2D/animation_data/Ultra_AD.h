
#define Ultra_PngWidth (2048)
#define Ultra_FrameSize 128
#define Ultra_FrameSizeF 128.f
#define Ultra_FrameAnimationTime 1.5f

#define Ultra_UV(x) ( ((float)((x)*Ultra_FrameSize)) / ((float)Ultra_PngWidth) )
#define Ultra_UV_Rect(u,v) { Ultra_UV(u), Ultra_UV(v), Ultra_UV(u+1), Ultra_UV(v+1) }
#define Ultra_UV_FrameAni(x) {					\
					Ultra_UV_Rect(x,0),		\
					Ultra_UV_Rect(x,1),		\
					Ultra_UV_Rect(x,2),		\
					Ultra_UV_Rect(x,3),		\
					Ultra_UV_Rect(x,4),		\
					Ultra_UV_Rect(x,5),		\
					Ultra_UV_Rect(x,6),		\
					Ultra_UV_Rect(x,7),		\
					Ultra_UV_Rect(x,8),		\
					Ultra_UV_Rect(x,9),		\
					Ultra_UV_Rect(x,10),		\
					Ultra_UV_Rect(x,11),		\
					Ultra_UV_Rect(x,12),		\
					Ultra_UV_Rect(x,13),		\
					Ultra_UV_Rect(x,14)		\
				}

UltraRect Ultra_0[] = Ultra_UV_FrameAni(0);
UltraRect Ultra_1[] = Ultra_UV_FrameAni(1);
UltraRect Ultra_2[] = Ultra_UV_FrameAni(2);
UltraRect Ultra_3[] = Ultra_UV_FrameAni(3);
UltraRect Ultra_4[] = Ultra_UV_FrameAni(4);
UltraRect Ultra_5[] = Ultra_UV_FrameAni(5);
UltraRect Ultra_6[] = Ultra_UV_FrameAni(6);
UltraRect Ultra_7[] = Ultra_UV_FrameAni(7);
UltraRect Ultra_8[] = Ultra_UV_FrameAni(8);
UltraRect Ultra_9[] = Ultra_UV_FrameAni(9);
UltraRect Ultra_10[] = Ultra_UV_FrameAni(10);
UltraRect Ultra_11[] = Ultra_UV_FrameAni(11);
UltraRect Ultra_12[] = Ultra_UV_FrameAni(12);
UltraRect Ultra_13[] = Ultra_UV_FrameAni(13);
UltraRect Ultra_14[] = Ultra_UV_FrameAni(14);
UltraRect Ultra_15[] = Ultra_UV_FrameAni(15);


// 방향배열에 animation을 저장한다.
UltraRect* UltraFrameAni_Dir[16] = {
	Ultra_0,
	Ultra_1,
	Ultra_2,
	Ultra_3,
	Ultra_4,
	Ultra_5,
	Ultra_6,
	Ultra_7,
	Ultra_8,
	Ultra_9,
	Ultra_10,
	Ultra_11,
	Ultra_12,
	Ultra_13,
	Ultra_14,
	Ultra_15
};


AnimRectTime Ultra_Time = { Ultra_FrameAnimationTime, ARRAYSIZE(Ultra_0) };

