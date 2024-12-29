#include"pch.h"
#include "base/Vec2.h"
#include "renderer\Dx2DRenderable.h"
#include "renderer\Dx2DRenderer.h"
#include "CollisionMap1.h"
#include "renderer\DxWindow.h"

#define PICO_ECS_IMPLEMENTATION
#include "pico\pico_ecs.h"


ecs_t* ecs1 = NULL;

// component IDs
ecs_id_t PositionCompID;
ecs_id_t VelocityCompID;
ecs_id_t TextureCompID;
ecs_id_t HouseCompID;
ecs_id_t UnitCompID;
ecs_id_t RectCompID;
ecs_id_t AnchorCompID;
ecs_id_t CollisionEvent1CompID;



//------------------------------------------------------



void register_components()
{
    PositionCompID  = ecs_register_component(ecs1, sizeof(Pos_t),  NULL, NULL);
    VelocityCompID  = ecs_register_component(ecs1, sizeof(Velocity_t),  NULL, NULL);
    TextureCompID  = ecs_register_component(ecs1, sizeof(Img_t),  NULL, NULL);
    AnchorCompID = ecs_register_component(ecs1, sizeof(Anchor_t), NULL, NULL);
    RectCompID = ecs_register_component(ecs1, sizeof(CollisionRect), NULL, NULL);
    HouseCompID  = ecs_register_component(ecs1, sizeof(UnitState_t),  NULL, NULL);
    UnitCompID = ecs_register_component(ecs1, sizeof(UnitState_t), NULL, NULL);
    CollisionEvent1CompID = ecs_register_component(ecs1, sizeof(CollisionEvent1), NULL, NULL);

}
