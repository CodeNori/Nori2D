


ecs_id_t create_entity_Unit()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
            Pos_t* pos =         (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
      Velocity_t*  dir =    (Velocity_t*)ecs_add(ecs1, id, VelocityCompID, NULL);
           Img_t*  img =         (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
    UnitState_t* flags =   (UnitState_t*)ecs_add(ecs1, id, UnitCompID, NULL);
      Anchor_t* anchor =      (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    CollisionRect*  rc =  (CollisionRect*)ecs_add(ecs1, id, RectCompID, NULL);
    CollisionEvent1*ce = (CollisionEvent1*)ecs_add(ecs1, id, CollisionEvent1CompID, NULL);

    flags->isCollision = 0;
    flags->isDead = 0;
    
    ce->l = id;
    ce->r = id;

    float x = (float)(rand() % g_Dx11.width);
    float y = (float)(rand() % g_Dx11.height);
    Vec2 p = ScreenToWorld({x,y});
    *pos = { p.x,p.y,0.f };
    
    dir->dir = GetRandomDir();
    dir->speed = 50.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 16;
    anchor->h = 16;

    img->texName = FARMER_FILE_NAME;
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;

    return id;
}


ecs_id_t create_entity_House()
{
    // Create entity
    ecs_id_t id = ecs_create(ecs1);

    // Add components
           Pos_t* pos = (Pos_t*)ecs_add(ecs1, id, PositionCompID, NULL);
          Img_t*  img = (Img_t*)ecs_add(ecs1, id, TextureCompID, NULL);
   UnitState_t* flags = (UnitState_t*)ecs_add(ecs1, id, HouseCompID, NULL);
     Anchor_t* anchor = (Anchor_t*)ecs_add(ecs1, id, AnchorCompID, NULL);
    CollisionRect* rc = (CollisionRect*)ecs_add(ecs1, id, RectCompID, NULL);

    flags->isCollision = 0;
    flags->isDead = 0;

    pos->x = (float)( rand() % g_Dx11.width );
    pos->y = (float)( rand() % g_Dx11.height );
    pos->angle = 0.f;

    anchor->anchorX = 0.5f;
    anchor->anchorY = 0.5f;
    anchor->w = 100;
    anchor->h = 100;
    img->texName = TOWNHALL_FILE_NAME;
    img->tex = nullptr;

	img->frameNo = 0;
	img->AnimTime = 0;
    img->dir = 0;

    return id;

}


