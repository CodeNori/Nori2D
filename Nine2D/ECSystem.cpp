#include"pch.h"
#include "base/Vec2.h"
#include "renderer\Dx2DRenderable.h"
#include "renderer\Dx2DRenderer.h"
#include "CollisionMap1.h"
#include "renderer\DxWindow.h"



// System IDs
ecs_id_t MovementSysID;
ecs_id_t RenderSysID_House;
ecs_id_t RenderSysID_Unit;



//------------------------------------------------------

#include "Sys_Movement.h"
#include "Sys_Render.h"
#include "CreateEntity.h"




int GetCollisionEventCount() {
    return col_Map1.events.size();

}



void register_systems()
{
    MovementSysID = ecs_register_system(ecs1, Movement_System, NULL, NULL, NULL);
    ecs_require_component(ecs1, MovementSysID, PositionCompID);
    ecs_require_component(ecs1, MovementSysID, VelocityCompID);
    ecs_require_component(ecs1, MovementSysID, AnchorCompID);
    ecs_require_component(ecs1, MovementSysID, RectCompID);
    ecs_require_component(ecs1, MovementSysID, UnitCompID);

    RenderSysID_House = ecs_register_system(ecs1, Render_System_House, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID_House, PositionCompID);
    ecs_require_component(ecs1, RenderSysID_House, TextureCompID);
    ecs_require_component(ecs1, RenderSysID_House, HouseCompID);

    RenderSysID_Unit = ecs_register_system(ecs1, Render_System_Unit, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID_Unit, PositionCompID);
    ecs_require_component(ecs1, RenderSysID_Unit, TextureCompID);
    ecs_require_component(ecs1, RenderSysID_Unit, UnitCompID);
    ecs_require_component(ecs1, RenderSysID_Unit, VelocityCompID);
}

void Render_system_all(float dt)
{
    ecs_update_system(ecs1, RenderSysID_House, dt);
    ecs_update_system(ecs1, RenderSysID_Unit, dt);
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




