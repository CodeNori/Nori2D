

CollisionMap1 col_Map1;


void Process_Overlapped(ecs_id_t id1, ecs_id_t id2)
{
        UnitState_t* flags1 = (UnitState_t*)ecs_get(ecs1, id1, UnitCompID);
        UnitState_t* flags2 = (UnitState_t*)ecs_get(ecs1, id2, UnitCompID);
        CollisionEvent1* ev1 = (CollisionEvent1*)ecs_get(ecs1, id1, CollisionEvent1CompID);
        CollisionEvent1* ev2 = (CollisionEvent1*)ecs_get(ecs1, id2, CollisionEvent1CompID);

        flags1->isCollision = 1;
        flags2->isCollision = 1;
        
        if(ev1->l == id1) ev1->l = id2; else  ev1->r = id2;
        if(ev2->l == id2) ev1->l = id1; else  ev1->r = id1;
}


inline
void Start_Collision(ecs_id_t id, 
                     Pos_t* pos, 
                     CollisionRect* rect, 
                     UnitState_t* flags, 
                     CollisionEvent1* ev )
{
    //
    //  Rectangle °è»ê.....
    //
    CollisionRect rc1;
    rc1.left = pos->x + rect->left;
    rc1.right = pos->x + rect->right;
    rc1.top = pos->y + rect->top;
    rc1.bottom = pos->y + rect->bottom;
    rc1.id = id;
    //
    //  Physics ....
    //
    if (col_Map1.isEnabled) {
        col_Map1.Insert2(&rc1);
        flags->isCollision = 0;
        ev->l = id;
        ev->r = id;
    }


}


void End_Collision_CheckAll()
{
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

}



