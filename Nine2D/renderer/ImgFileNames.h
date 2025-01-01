#pragma once

static const WCHAR* ULTRA_FILE_NAME    = L"Image\\Ultralisk.png";
static const WCHAR* TOWNHALL_FILE_NAME = L"Image\\TownHall.png";
static const WCHAR* FARMER_FILE_NAME   = L"Image\\farmer11.png";


struct GameResImage
{
	const WCHAR* fileName;
	void* dxRes;
};

extern GameResImage UltraImg;
extern GameResImage TownHallImg;
extern GameResImage FarmerImg;


unsigned short GetImageFileIndex(const WCHAR* fileName);
GameResImage* GetGameResImage(USHORT idx);



