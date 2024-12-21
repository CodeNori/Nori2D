
ecs_ret_t Render_System_House(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dt,
                          void* udata)
{
    Dx2DRenderable2 rd;
    rd.color = {0.f, 0.f, 1.f, 1.f};
    rd.ancherX = 0.5f;
    rd.ancherY = 0.5f;
    rd.h = 100;
    rd.w = 100;
    rd.tex.mName = g_Tex_Name[1];
    rd.tex.mTextureRV = nullptr;

    (void)udata;
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

    return 0;
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
    rd.tex.mName = g_Tex_Name[0];
    rd.tex.mTextureRV = nullptr;

    (void)udata;
    //printf("Render_System = %d \n", entity_count);

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
            rd.color = {0.5f, 0.5f, 0.5f, 1.f};


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


