


void create_entity_Unit()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
    Pos_t* pos = (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
    Vec2*  dir = (Vec2*)ecs_add(ecs1, id, VelocityCompID, NULL);
    Img_t*  img = (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
    BYTE* type = (BYTE*)ecs_add(ecs1, id, UnitCompID, NULL);
    Anchor_t* anchor = (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    CollisionRect*  rc = (CollisionRect*)ecs_add(ecs1, id, RectCompID, NULL);

    *type  = 0;

    
    float x = (float)(rand() % g_Dx11.width);
    float y = (float)(rand() % g_Dx11.height);
    Vec2 p = ScreenToWorld({x,y});
    *pos = { p.x,p.y,0.f };
    
    *dir = GetRandomDir()* 100.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 48;
    anchor->h = 48;

    img->texName = g_Tex_Name[1];
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;
}

void create_entity_House()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
    Pos_t* pos = (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
    Img_t*  img = (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
    char*  type = (char*)ecs_add(ecs1, id, HouseCompID, NULL);
    Anchor_t* anchor = (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    CollisionRect* rc = (CollisionRect*)ecs_add(ecs1, id, RectCompID, NULL);

    *type = 1;

    pos->x = (float)( rand() % g_Dx11.width );
    pos->y = (float)( rand() % g_Dx11.height );
    pos->angle = 0.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 100;
    anchor->h = 100;
    img->texName = g_Tex_Name[0];
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;

}


