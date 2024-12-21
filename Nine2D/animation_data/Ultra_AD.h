
#define UltraPngWidth (2048)
#define UltraFrameSize 128
#define UltraFrameSizeF 128.f

#define UltraUV(x) ( ((float)((x)*UltraFrameSize)) / ((float)UltraPngWidth) )
#define UltraUV_Rect(u,v) { UltraUV(u), UltraUV(v), UltraUV(u+1), UltraUV(v+1) }
#define UltraUV_FrameAni(x) {					\
					UltraUV_Rect(x,0),		\
					UltraUV_Rect(x,1),		\
					UltraUV_Rect(x,2),		\
					UltraUV_Rect(x,3),		\
					UltraUV_Rect(x,4),		\
					UltraUV_Rect(x,5),		\
					UltraUV_Rect(x,6),		\
					UltraUV_Rect(x,7),		\
					UltraUV_Rect(x,8),		\
					UltraUV_Rect(x,9),		\
					UltraUV_Rect(x,10),		\
					UltraUV_Rect(x,11),		\
					UltraUV_Rect(x,12),		\
					UltraUV_Rect(x,13),		\
					UltraUV_Rect(x,14)		\
				}

UltraRect Ultra_0[] = UltraUV_FrameAni(0);
UltraRect Ultra_1[] = UltraUV_FrameAni(1);
UltraRect Ultra_2[] = UltraUV_FrameAni(2);
UltraRect Ultra_3[] = UltraUV_FrameAni(3);
UltraRect Ultra_4[] = UltraUV_FrameAni(4);
UltraRect Ultra_5[] = UltraUV_FrameAni(5);
UltraRect Ultra_6[] = UltraUV_FrameAni(6);
UltraRect Ultra_7[] = UltraUV_FrameAni(7);
UltraRect Ultra_8[] = UltraUV_FrameAni(8);
UltraRect Ultra_9[] = UltraUV_FrameAni(9);
UltraRect Ultra_10[] = UltraUV_FrameAni(10);
UltraRect Ultra_11[] = UltraUV_FrameAni(11);
UltraRect Ultra_12[] = UltraUV_FrameAni(12);
UltraRect Ultra_13[] = UltraUV_FrameAni(13);
UltraRect Ultra_14[] = UltraUV_FrameAni(14);
UltraRect Ultra_15[] = UltraUV_FrameAni(15);


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


AnimRectTime Ultra_Time = { 1.5f, ARRAYSIZE(Ultra_0) };

