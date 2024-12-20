
ecs_ret_t Render_System_House(ecs_t* ecs,
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
    rd.tex.mName = TOWNHALL_FILE_NAME;
    rd.tex.mTextureRV = nullptr;

    (void)udata;

    PsShader* psOld = g_ECS_Renderer->mPS;
    g_ECS_Renderer->mPS = g_ECS_Renderer->mPScolor;

    printf("Render_System = %d \n", entity_count);

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Img_t* img = (Img_t*)ecs_get(ecs, id, TextureCompID);
        CollisionRect* rect = (CollisionRect*)ecs_get(ecs, id, RectCompID);

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
        rd.frameNo = 0;
        
        g_ECS_Renderer->Draw2(&rd, rect);

        img->tex = rd.tex.mTextureRV;   // 历厘..
        img->AnimTime = rd.AnimTime;    // 历厘..
        img->frameNo = rd.frameNo;      // 历厘..
        img->dir = rd.dir;
    }   

    g_ECS_Renderer->mPS = psOld;
    return 0;
}


void Toggle_PShader(ecs_dt_t dt)
{
    if(DxWindow::g->isSpaceKey_coolTime > 0.f)
        DxWindow::g->isSpaceKey_coolTime -= dt;

    if(DxWindow::g->isSpaceKey) {
        if(DxWindow::g->isSpaceKey_coolTime <= 0.f ) {
            g_ECS_Renderer->TogglePS();
            DxWindow::g->isSpaceKey_coolTime = 0.5f;
        }
    }
}

ecs_ret_t Render_System_Unit(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dt,
                          void* udata)
{
    Dx2DRenderable2 rd;
    rd.color = {1.f, 1.f, 1.f, 1.f};
    rd.ancherX = 0.5f;
    rd.ancherY = 0.5f;
    rd.h = 128;
    rd.w = 128;
    rd.tex.mName = ULTRA_FILE_NAME;
    rd.tex.mTextureRV = nullptr;

    (void)udata;
    //printf("Render_System = %d \n", entity_count);
    Toggle_PShader(dt);

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Img_t* img = (Img_t*)ecs_get(ecs, id, TextureCompID);
        CollisionRect* rect = (CollisionRect*)ecs_get(ecs, id, RectCompID);
        BYTE* type = (BYTE*)ecs_get(ecs, id, UnitCompID);

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
        
        if(*type >= 250)
            rd.color = {1.f, 0.f, 0.f, 1.f};
        else
            rd.color = {0.2f, 0.2f, 0.2f, 1.f};


        g_ECS_Renderer->Draw2(&rd, rect);

        // 历厘
        // 历厘
        // 历厘.
        img->tex = rd.tex.mTextureRV;   // 历厘..
        img->AnimTime = rd.AnimTime;    // 历厘..
        img->frameNo = rd.frameNo;      // 历厘..
        img->dir = rd.dir;
    }   

    return 0;
}


