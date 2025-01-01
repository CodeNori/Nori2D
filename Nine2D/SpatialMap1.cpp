#include "pch.h"
#include "SpatialMap1.h"


void SpatialMap1::Setup(float sx, float sy, int w, int h)
{
    start_x = sx;
    start_y = sy;

    size_x = w / PARTITIONS + 1;
    size_y = h / PARTITIONS + 1;

    end_x = (size_x*PARTITIONS);
    end_y = (size_y*PARTITIONS);

    grid.clear();
    grid.resize(size_x * size_y);
    gridRect.resize(size_x * size_y);

    for(int y=0; y<size_y; ++y)
        for(int x=0; x<size_x; ++x){
            CollisionRect& rc = gridRect[(y*size_x)+x];
            rc.left = (float)(x*PARTITIONS) + start_x;
            rc.right = (float)((x+1)*PARTITIONS)  + start_x;
            rc.top = (float)((y+1)*PARTITIONS)  + start_y;
            rc.bottom = (float)(y*PARTITIONS) + start_y;

        // OutputDebugString2("%d,%d = %0.1f,%0.1f,%0.1f,%0.1f,\n", x,y, rc.left, rc.right,rc.top, rc.bottom);
        // OutputDebugString2("(%d,%d) = %0.1f - %0.1f\n", x,y, rc.top, rc.bottom);
        }

    events.clear();

    //DebugPrint();
}

void SpatialMap1::Clear_test()
{
    events.clear();

    for(auto it : grid) {        
        it.clear();
    }
}

int g_sl, g_sr, g_st, g_sb;
int g_left, g_right, g_top, g_bottom;

int SpatialMap1::FindSlot(CollisionRect* rc, int* slot)
{
    float f_l = rc->left - start_x;
    float f_r = rc->right - start_x;
    float f_t = rc->top - start_y;
    float f_b = rc->bottom - start_y;

    if(f_r < 0) return 0;
    if(f_t < 0) return 0;
    if(f_l > end_x) return 0;
    if(f_b > end_y) return 0;

    int sl = (int)f_l;
    int sr = (int)f_r;
    int st = (int)f_t;
    int sb = (int)f_b;

    //g_sl = sl;
    //g_sr = sr;
    //g_st = st;
    //g_sb = sb;

    int left = (sl/PARTITIONS);     if(left<0) left = 0;
    int right = (sr/PARTITIONS);    if(right>=size_x) right = size_x-1;
    int top = (st/PARTITIONS);      if(top>=size_y) top = size_y-1;
    int bottom = (sb/PARTITIONS);   if(bottom<0) bottom = 0;

    //g_left = left;
    //g_right = right;
    //g_top = top;
    //g_bottom = bottom;

    int slots[4] = {
        (bottom*size_x) + left,
        (bottom*size_x) + right,
        (top*size_x) + left,
        (top*size_x) + right
    };

    //slot[0] = slots[0];
    //slot[1] = slots[1];
    //slot[2] = slots[2];
    //slot[3] = slots[3];

    int cnt = 0;
    slot[cnt++] = slots[0];
    if (slots[0]!=slots[1]) slot[cnt++] = slots[1];
    if (slots[0]!=slots[2]) slot[cnt++] = slots[2];
    if (slots[1]!=slots[3] && slots[2]!=slots[3]) slot[cnt++] = slots[3];

    return cnt;
}


void SpatialMap1::Insert(CollisionRect* rc)
{
    int slot[4] = {-1,-1,-1,-1};
    int slotCnt = FindSlot(rc, slot);
    
    for(int i=0; i<slotCnt; ++i) 
        grid[slot[i]].push_back(*rc);

}

void SpatialMap1::Insert1(CollisionRect* rc)
{
    int slot[4] = {-1,-1,-1,-1};
    int slotCnt = FindSlot(rc, slot);
    
    // for(int i=0; i<slotCnt; ++i) 
    //    grid[slot[i]].push_back(*rc);
    
    int count = 0;
    int slot2[4] = {-1,-1,-1,-1};

    for(int i=0; i<grid.size(); ++i) {
        if(isOverlapped(gridRect[i],*rc))
        {
            grid[i].push_back(*rc);
                
            // if(slot[0] != i &&
            //   slot[1] != i &&
            //   slot[2] != i &&
            //   slot[3] != i)
            //    OutputDebugString2("Collision grid가 다르다. (%d) %d, %d, %d, %d\n", i, slot[0],slot[1],slot[2],slot[3]);
            slot2[count] = i;          
            if(++count == 4) break;
        }
    }
    
    if(count != slotCnt)
        { OutputDebugString2("Collision grid가 다르다. %d, %d, %d, %d\n", slot[0],slot[1],slot[2],slot[3]); }
    else {
    for(int i=0; i<count; ++i)
        if(slot[i] != slot2[i])
        { OutputDebugString2("Collision grid가 다르다. %d, %d, %d, %d\n", slot[0],slot[1],slot[2],slot[3]); }
    }

}


void SpatialMap1::Insert2(CollisionRect* rc)
{
    int count = 0;

    for(int i=0; i<grid.size(); ++i) {
        if(isOverlapped(gridRect[i],*rc)) {
            grid[i].push_back(*rc);
            if(++count == 4) break;
        }
    }
}

void Process_Overlapped(ecs_id_t id1, ecs_id_t id2);


void SpatialMap1::Collide() 
{
    collisionCount = 0;

    for (const std::vector<CollisionRect>& candidates : grid) {
        for (const CollisionRect& left : candidates) {
            for (const CollisionRect& right : candidates) {
                if (left.id == right.id) continue;
                if (isOverlapped(left, right)) {
                    //events.push_back({ left.id, right.id });
                    Process_Overlapped(left.id, right.id);
                    ++collisionCount;
                }
            }
        }
    }
}

void SpatialMap1::DebugPrint()
{
    for(auto it : grid) {        
        int sz = it.capacity();
        OutputDebugString2("capacity: %d\n", sz);
    }

    OutputDebugStringA("--------- end --------");
}

int SpatialMap1::Find(CollisionRect* my, std::vector<ecs_id_t>& idList)
{
    int slot[4];
    int count = FindSlot(my, slot);
    int collision_count = 0;

    for (int i=0; i<count; ++i) 
    {
        std::vector<CollisionRect>& candidates = grid[i];
        for (const CollisionRect& left : candidates) {
            if (left.id == my->id) continue;
            if (isOverlapped(left, *my)) {
                idList.push_back(left.id);
                ++collision_count;
            }
        }
    }

    return collision_count;
}



