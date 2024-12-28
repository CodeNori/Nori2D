

ecs_ret_t Sys_Tower_SpawnEnemy(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dtt,
                          void* udata)
{
    (void)udata;

    float dt = dtt;

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Vec2* dir = (Vec2*)ecs_get(ecs, id, VelocityCompID);
        Anchor_t* anchor = (Anchor_t*)ecs_get(ecs, id, AnchorCompID);
        CollisionRect* rect = (CollisionRect*)ecs_get(ecs, id, RectCompID);
        BYTE* type = (BYTE*)ecs_get(ecs, id, UnitCompID);

        pos->x += dir->x * dt;
        pos->y += dir->y * dt;

        {
            rect->left = pos->x - (anchor->w * anchor->anchorX);
            rect->top = pos->y + (anchor->h * anchor->anchorY);
            rect->right = rect->left + anchor->w;
            rect->bottom = rect->top - anchor->h;
            rect->id = id;

            if (col_Map1.isEnabled) {
                col_Map1.Insert2(rect);
                *type = 0;
            }
        }



        float Scn_left =  g_CameraPos.x-g_Dx11.half_width      - 1024;
        float Scn_right = g_CameraPos.x + g_Dx11.half_width    + 1024;
        float Scn_top = g_CameraPos.y + g_Dx11.half_height     + 1024;
        float Scn_bottom = g_CameraPos.y - g_Dx11.half_height  - 1024;
        if (pos->x < Scn_left  ||
            pos->x > Scn_right ||
            pos->y < Scn_bottom||
            pos->y > Scn_top)
        {
            *dir = GetRandomDir()* 100.f;
        }

    }


    return 0;
}



