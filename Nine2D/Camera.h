#pragma once
#include "base/Vec2.h"


extern ax::Vec2 g_CameraPos;

Vec2 ScreenToWorld(Vec2 a);
Vec2 WorldToScreen(Vec2 dd);


void MoveCameraX(float val);
void MoveCameraY(float val);

