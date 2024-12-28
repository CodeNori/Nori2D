#include"pch.h"
#include "base/Vec2.h"
#include "renderer\Dx2DRenderable.h"
#include "renderer\Dx2DRenderer.h"
#include "CollisionMap1.h"
#include "renderer\DxWindow.h"

#define PICO_ECS_IMPLEMENTATION
#include "pico\pico_ecs.h"


ecs_t* ecs1 = NULL;
Vec2 g_CameraPos = {1280/2,720/2};
Dx2DRenderer* g_ECS_Renderer = nullptr;

// component IDs
ecs_id_t PositionCompID;
ecs_id_t VelocityCompID;
ecs_id_t TextureCompID;
ecs_id_t HouseCompID;
ecs_id_t UnitCompID;
ecs_id_t RectCompID;
ecs_id_t AnchorCompID;

// System IDs
ecs_id_t MovementSysID;
ecs_id_t RenderSysID1;
ecs_id_t RenderSysID2;

/*
const WCHAR* g_Tex_Name[] = {
    L"Image\\TownHall.png",
    L"Image\\Ultralisk.png",
};
*/

CollisionMap1 col_Map1;




//----------------------------------------------------------------------
Vec2 ScreenToWorld(Vec2 a)
{
    float dx = (a.x - g_Dx11.half_width);
    float dy = (g_Dx11.half_height - a.y);
    
    
    return {dx+ g_CameraPos.x,dy+g_CameraPos.y};
    
}


int GetCollisionEventCount() {
    return col_Map1.events.size();

}



void register_components()
{
    PositionCompID  = ecs_register_component(ecs1, sizeof(Pos_t),  NULL, NULL);
    VelocityCompID  = ecs_register_component(ecs1, sizeof(Velocity_t),  NULL, NULL);
    TextureCompID  = ecs_register_component(ecs1, sizeof(Img_t),  NULL, NULL);
    AnchorCompID = ecs_register_component(ecs1, sizeof(Anchor_t), NULL, NULL);
    RectCompID = ecs_register_component(ecs1, sizeof(CollisionRect), NULL, NULL);
    HouseCompID  = ecs_register_component(ecs1, sizeof(char),  NULL, NULL);
    UnitCompID = ecs_register_component(ecs1, sizeof(char), NULL, NULL);

    col_Map1.Setup(-256.f, -256.f, g_Dx11.width+512.f, g_Dx11.height+512.f );

}

#include "Sys_Movement.h"
#include "Sys_Render.h"




void register_systems()
{
    MovementSysID = ecs_register_system(ecs1, Movement_System, NULL, NULL, NULL);
    ecs_require_component(ecs1, MovementSysID, PositionCompID);
    ecs_require_component(ecs1, MovementSysID, VelocityCompID);
    ecs_require_component(ecs1, MovementSysID, AnchorCompID);
    ecs_require_component(ecs1, MovementSysID, RectCompID);
    ecs_require_component(ecs1, MovementSysID, UnitCompID);

    RenderSysID1 = ecs_register_system(ecs1, Render_System_House, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID1, PositionCompID);
    ecs_require_component(ecs1, RenderSysID1, TextureCompID);
    ecs_require_component(ecs1, RenderSysID1, HouseCompID);

    RenderSysID2 = ecs_register_system(ecs1, Render_System_Unit, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID2, PositionCompID);
    ecs_require_component(ecs1, RenderSysID2, TextureCompID);
    ecs_require_component(ecs1, RenderSysID2, UnitCompID);
    ecs_require_component(ecs1, RenderSysID2, VelocityCompID);
}

void Render_system_all(float dt)
{
    ecs_update_system(ecs1, RenderSysID1, dt);
    ecs_update_system(ecs1, RenderSysID2, dt);

}

void Update_system_all(float dt)
{
    static float collisionTestTime = 0.f;
    collisionTestTime += dt;
    if (collisionTestTime >= 0.09f) {
        col_Map1.isEnabled = true;
        collisionTestTime = 0.f;
    }
    else 
        col_Map1.isEnabled = false;

    double dtt = dt;
    ecs_update_system(ecs1, MovementSysID, dtt);
}


#include "CreateEntity.h"


