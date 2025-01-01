#include "pch.h"
#include "ImgFileNames.h"



GameResImage UltraImg;
GameResImage TownHallImg;
GameResImage FarmerImg;

GameResImage g_GameResImage[] ={
	{ULTRA_FILE_NAME, nullptr},
	{TOWNHALL_FILE_NAME, nullptr},
	{FARMER_FILE_NAME, nullptr},
}; 


unsigned short GetImageFileIndex(const WCHAR* fileName)
{
	unsigned short count = ARRAYSIZE(g_GameResImage);
	for(unsigned short i=0; i<count; ++i){
		if(fileName == g_GameResImage[i].fileName ) return i;
	}

	return 0;
}

GameResImage* GetGameResImage(USHORT idx)
{
	return g_GameResImage+idx;
}



