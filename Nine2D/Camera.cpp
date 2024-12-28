#include "pch.h"
#include "Camera.h"

Vec2 g_CameraPos = {1280.f/2.f,720.f/2.f};

//----------------------------------------------------------------------
Vec2 ScreenToWorld(Vec2 a)
{
    float dx = (a.x - g_Dx11.half_width);
    float dy = (g_Dx11.half_height - a.y);
    
    
    return {dx+ g_CameraPos.x,dy+g_CameraPos.y};
    
}

Vec2 WorldToScreen(Vec2 dd)
{
    Vec2 a;
    a.x = (dd.x - g_CameraPos.x) + g_Dx11.half_width;
    a.y = g_Dx11.half_height - (dd.y - g_CameraPos.y);
    return a;
}


void MoveCameraX(float val)
{
    g_CameraPos.x += val;
}

void MoveCameraY(float val)
{
    g_CameraPos.y += val;
}
