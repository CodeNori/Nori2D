
CollisionMap1 col_Map1;



void Push_CollisionFlag(ecs_id_t id1, ecs_id_t id2)
{
        BYTE* type1 = (BYTE*)ecs_get(ecs1, id1, UnitCompID);
        BYTE* type2 = (BYTE*)ecs_get(ecs1, id2, UnitCompID);
        *type1 = 255;
        *type2 = 255;
}


Vec2 GetRandomDir()
{
    int angle = rand() % 360;
    float radian = MATH_DEG_TO_RAD(angle); 

    Vec2 p(1.0f,0.f);
    p = p.rotateByAngle(Vec2::ZERO, radian);

    return p;
}


void 영역밖이면_안쪽으로_속도변경(Pos_t* pos, Velocity_t* vel)
{
    float Scn_left   = g_CameraPos.x - g_Dx11.half_width   - 1024;
    float Scn_right  = g_CameraPos.x + g_Dx11.half_width   + 1024;
    float Scn_top    = g_CameraPos.y + g_Dx11.half_height  + 1024;
    float Scn_bottom = g_CameraPos.y - g_Dx11.half_height  - 1024;
    if (pos->x < Scn_left  ||
        pos->x > Scn_right ||
        pos->y < Scn_bottom||
        pos->y > Scn_top)
    {
        vel->dir = GetRandomDir();
        vel->speed = 50.f;
    }

}


ecs_ret_t Movement_System(ecs_t* ecs,
                          ecs_id_t* entities,
                          int entity_count,
                          ecs_dt_t dtt,
                          void* udata)
{
    (void)udata;

    if (col_Map1.isEnabled) {
        //col_Map1.Clear();
        //col_Map1.DebugPrint();
        col_Map1.Setup(-256.f, -256.f, g_Dx11.width+512.f, g_Dx11.height+512.f );
    }

    float dt = dtt;

    for (int i = 0; i < entity_count; i++)
    {
        // Get entity ID
        ecs_id_t id = entities[i];

        Pos_t* pos = (Pos_t*)ecs_get(ecs, id, PositionCompID);
        Velocity_t* vel = (Velocity_t*)ecs_get(ecs, id, VelocityCompID);
        Anchor_t* anchor = (Anchor_t*)ecs_get(ecs, id, AnchorCompID);
        CollisionRect* rect = (CollisionRect*)ecs_get(ecs, id, RectCompID);
        BYTE* type = (BYTE*)ecs_get(ecs, id, UnitCompID);

        //
        //  위치 이동.....
        //
        pos->x += (vel->dir.x * vel->speed) * dt;
        pos->y += (vel->dir.y * vel->speed) * dt;

        //
        //  Rectangle 계산.....
        //
        rect->left = pos->x - (anchor->w * anchor->anchorX);
        rect->top = pos->y + (anchor->h * anchor->anchorY);
        rect->right = rect->left + anchor->w;
        rect->bottom = rect->top - anchor->h;
        rect->id = id;

        //
        //  Physics ....
        //
        if (col_Map1.isEnabled) {
            col_Map1.Insert2(rect);
            *type = 0;
        }


        영역밖이면_안쪽으로_속도변경(pos, vel);
    }


    //
    //  Physics ....
    //
    if(col_Map1.isEnabled) {
        col_Map1.Collide();
        
        /*
        for(int i=0; i<col_Map1.events.size(); ++i) {
            CollisionEvent& e = col_Map1.events[i];
            BYTE* type = (BYTE*)ecs_get(ecs1, e.l, UnitCompID);
            *type = 255;
            type = (BYTE*)ecs_get(ecs1, e.r, UnitCompID);
            *type = 255;

            
        }
        */
    }

    return 0;
}



