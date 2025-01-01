#pragma once
#include <iostream>
#include "AnimationLoader.h"






bool Test_JSON()
{
	AnimFrameFile affile;

	JsonAnimFileLoader(affile, "Image\\Farmer11.json");

	OutputDebugString2("%s\n", affile.imgFileName);

	return false;
}
