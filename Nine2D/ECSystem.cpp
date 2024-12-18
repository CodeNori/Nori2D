#include"pch.h"
#include "base/Vec2.h"
#include "renderer\Dx2DRenderable.h"
#include "CollisionMap1.h"

#define PICO_ECS_IMPLEMENTATION
#include "pico\pico_ecs.h"


ecs_t* ecs1 = NULL;

IRenderer* g_ECS_Renderer = nullptr;

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

const WCHAR* g_Tex_Name[] = {
    L"Image\\Carrot.png",
    L"Image\\TownHall.png",
    L"Image\\Ultralisk.png",
};


CollisionMap1 col_Map1;

int GetCollisionEventCount() {
    return col_Map1.events.size();

}

void register_components()
{
    PositionCompID  = ecs_register_component(ecs1, sizeof(Pos_t),  NULL, NULL);
    VelocityCompID  = ecs_register_component(ecs1, sizeof(Velocity_t),  NULL, NULL);
    TextureCompID  = ecs_register_component(ecs1, sizeof(Img_t),  NULL, NULL);
    AnchorCompID = ecs_register_component(ecs1, sizeof(Anchor_t), NULL, NULL);
    RectCompID = ecs_register_component(ecs1, sizeof(Rect_t), NULL, NULL);
    HouseCompID  = ecs_register_component(ecs1, sizeof(char),  NULL, NULL);
    UnitCompID = ecs_register_component(ecs1, sizeof(char), NULL, NULL);


}



ecs_ret_t Movement_System(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dtt,
                          void* udata)
{
    (void)udata;

    if (col_Map1.isEnabled)
        col_Map1.Setup(g_Dx11.width, g_Dx11.height);

    printf("Movement_System = %d \n", entity_count);
    float dt = dtt;

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Vec2* dir = (Vec2*)ecs_get(ecs, id, VelocityCompID);
        Anchor_t* anchor = (Anchor_t*)ecs_get(ecs, id, AnchorCompID);
        Rect_t* rect = (Rect_t*)ecs_get(ecs, id, RectCompID);

        pos->x += dir->x * dt;
        pos->y += dir->y * dt;

        {
            rect->l = pos->x - (anchor->w * anchor->anchorX);
            rect->t = pos->y + (anchor->h * anchor->anchorY);
            rect->r = rect->l + anchor->w;
            rect->b = rect->t - anchor->h;
            rect->id = id;

            if (col_Map1.isEnabled)
                col_Map1.Collect(rect);
        }



        float right =  (float)(g_Dx11.width-50);
        float bottom =  (float)(g_Dx11.height-50);
        if (pos->x > right ||
            pos->x < 100.f ||
            pos->y > bottom ||
            pos->y < 100.f ) 
        { 
            int x = rand() % g_Dx11.width;
            int y = rand() % g_Dx11.height;
    
            dir->x = ((float)x) - pos->x;
            dir->y = ((float)y) - pos->y;
            dir->normalize();
            dir->x *= 100.f;
            dir->y *= 100.f;
        }

    }

    return 0;
}


ecs_ret_t Render_System(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dt,
                          void* udata)
{
    Dx2DRenderable2 rd;
    rd.color = {1.f, 1.f, 1.f, 1.f};
    rd.ancherX = 0.5f;
    rd.ancherY = 0.5f;
    rd.h = 100;
    rd.w = 100;
    rd.tex.mName = g_Tex_Name[0];
    rd.tex.mTextureRV = nullptr;

    (void)udata;
    printf("Render_System = %d \n", entity_count);

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Img_t* img = (Img_t*)ecs_get(ecs, id, TextureCompID);
        Rect_t* rect = (Rect_t*)ecs_get(ecs, id, RectCompID);

        rd.position.x = pos->x;
        rd.position.y = pos->y;
        rd.angle = pos->angle; 
        //rd.w = img->w;
        //rd.h = img->h;
        //rd.ancherX = img->ancherX; 
        //rd.ancherY = img->ancherY;
        // 
        rd.tex.mName = img->texName;
        rd.tex.mTextureRV = (ID3D11ShaderResourceView*)img->tex;
        rd.dir = img->dir;
        rd.AnimTime = img->AnimTime;
        rd.frameNo = img->frameNo;
        
        g_ECS_Renderer->Draw2(&rd, rect);

        img->tex = rd.tex.mTextureRV;   // ����..
        img->AnimTime = rd.AnimTime;    // ����..
        img->frameNo = rd.frameNo;      // ����..
        img->dir = rd.dir;
    }   

    return 0;
}




void register_systems()
{
    MovementSysID = ecs_register_system(ecs1, Movement_System, NULL, NULL, NULL);
    ecs_require_component(ecs1, MovementSysID, PositionCompID);
    ecs_require_component(ecs1, MovementSysID, VelocityCompID);
    ecs_require_component(ecs1, MovementSysID, AnchorCompID);
    ecs_require_component(ecs1, MovementSysID, RectCompID);

    RenderSysID1 = ecs_register_system(ecs1, Render_System, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID1, PositionCompID);
    ecs_require_component(ecs1, RenderSysID1, TextureCompID);
    ecs_require_component(ecs1, RenderSysID1, HouseCompID);

    RenderSysID2 = ecs_register_system(ecs1, Render_System, NULL, NULL, NULL);
    ecs_require_component(ecs1, RenderSysID2, PositionCompID);
    ecs_require_component(ecs1, RenderSysID2, TextureCompID);
    ecs_require_component(ecs1, RenderSysID2, UnitCompID);
}

void Render_system_all(float dt)
{
    ecs_update_system(ecs1, RenderSysID1, dt);
    ecs_update_system(ecs1, RenderSysID2, dt);


}

void Update_system_all(float dt)
{
    static UINT64 cnt = 0;
    if (++cnt % 10 == 0) col_Map1.isEnabled = true;
    else col_Map1.isEnabled = false;

    double dtt = dt;
    ecs_update_system(ecs1, MovementSysID, dtt);

    if(col_Map1.isEnabled)
        col_Map1.Collide();
}


void create_entity1()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
    Pos_t* pos = (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
    Vec2*  dir = (Vec2*)ecs_add(ecs1, id, VelocityCompID, NULL);
    Img_t*  img = (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
    char* type = (char*)ecs_add(ecs1, id, UnitCompID, NULL);
    Anchor_t* anchor = (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    Rect_t*  rc = (Rect_t*)ecs_add(ecs1, id, RectCompID, NULL);

    *type  = 2;
    *pos    = { 600, 400, 0.f };

    int x = rand() % g_Dx11.width;
    int y = rand() % g_Dx11.height;

    dir->x = ((float)x) - pos->x;
    dir->y = ((float)y) - pos->y;
    dir->normalize();
    *dir *= 100.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 128;
    anchor->h = 128;

    img->texName = g_Tex_Name[2];
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;
}

void create_entity2()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
    Pos_t* pos = (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
    Img_t*  img = (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
    char*  type = (char*)ecs_add(ecs1, id, HouseCompID, NULL);
    Anchor_t* anchor = (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    Rect_t* rc = (Rect_t*)ecs_add(ecs1, id, RectCompID, NULL);

    *type = 1;

    pos->x = (float)( rand() % g_Dx11.width );
    pos->y = (float)( rand() % g_Dx11.height );
    pos->angle = 0.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 100;
    anchor->h = 100;
    img->texName = g_Tex_Name[1];
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;

}


