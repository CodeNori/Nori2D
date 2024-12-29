


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

                 Pos_t* pos =         (Pos_t*)ecs_get(ecs, id, PositionCompID);
            Velocity_t* vel =    (Velocity_t*)ecs_get(ecs, id, VelocityCompID);
           Anchor_t* anchor =      (Anchor_t*)ecs_get(ecs, id, AnchorCompID);
        CollisionRect* rect = (CollisionRect*)ecs_get(ecs, id, RectCompID);
         UnitState_t* flags =   (UnitState_t*)ecs_get(ecs, id, UnitCompID);
        CollisionEvent1* ev = (CollisionEvent1*)ecs_get(ecs, id, CollisionEvent1CompID);

        //
        //  위치 이동.....
        //
        pos->x += (vel->dir.x * vel->speed) * dt;
        pos->y += (vel->dir.y * vel->speed) * dt;

        //
        //  Collision 계산.....
        //
        Start_Collision(id, pos, rect, flags, ev);

        //
        //  
        //
        영역밖이면_안쪽으로_속도변경(pos, vel);
    }


    //
    //  Physics ....
    //
    End_Collision_CheckAll();

    return 0;
}



