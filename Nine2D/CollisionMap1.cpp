#include "pch.h"
#include "CollisionMap1.h"

void CollisionMap1::Setup(float sx, float sy, int w, int h)
{
    start_x = sx;
    start_y = sy;

    size_x = w / PARTITIONS + 1;
    size_y = h / PARTITIONS + 1;

    end_x = size_x*PARTITIONS;
    end_y = size_y*PARTITIONS;

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
        }

    events.clear();

    //DebugPrint();
}

void CollisionMap1::Clear_test()
{
    events.clear();

    for(auto it : grid) {        
        it.clear();
    }
}

void CollisionMap1::Insert(CollisionRect* rc)
{
    int sl = (int)(rc->left - start_x );
    int sr = (int)(rc->right - start_x );
    int st = (int)(rc->top - start_y );
    int sb = (int)(rc->bottom - start_y );

    int left = (sl/PARTITIONS);
    int right = (sr/PARTITIONS);
    int top = (st/PARTITIONS);
    int bottom = (sb/PARTITIONS);

    if (left < 0) left = 0;
    if (right < 0) right = 0;
    if (top < 0) top = 0;
    if (bottom < 0) bottom = 0;

    if (left>=size_x) left = size_x-1;
    if (right>=size_x) right = size_x-1;
    if (top>=size_y) top = size_y-1;
    if (bottom>=size_y) bottom = size_y-1;


    unsigned int slots[4] = {
        left+top*size_x,
        right+top*size_x,
        left+bottom*size_x,
        right+bottom*size_x,
    };
    grid[slots[0]].push_back(*rc);
    if (slots[0]!=slots[1]) grid[slots[1]].push_back(*rc);
    if (slots[1]!=slots[2]) grid[slots[2]].push_back(*rc);
    if (slots[2]!=slots[3]) grid[slots[3]].push_back(*rc);
}


void CollisionMap1::Insert1(CollisionRect* rc)
{
    int sl = (int)(rc->left - start_x );
    int sr = (int)(rc->right - start_x );
    int st = (int)(rc->top - start_y );
    int sb = (int)(rc->bottom - start_y );

    if(sr <= 0) return;
    if(sl >= end_x) return;

    if(st <= 0) return;
    if(sb >= end_y) return;

    int left = (sl/PARTITIONS);
    int right = (sr/PARTITIONS);
    int top = (st/PARTITIONS);
    int bottom = (sb/PARTITIONS);


    unsigned int slots[4] = {
        top*size_x + left,
        top*size_x + right,
        bottom*size_x + left,
        bottom*size_x + right,
    };
    grid[slots[0]].push_back(*rc);
    if (slots[0]!=slots[1]) grid[slots[1]].push_back(*rc);
    if (slots[0]!=slots[2]) grid[slots[2]].push_back(*rc);
    if (slots[1]!=slots[3]) grid[slots[3]].push_back(*rc);
}

void CollisionMap1::Insert2(CollisionRect* rc)
{
    int count = 0;

    for(int i=0; i<grid.size(); ++i) {
        if(isOverlapped(gridRect[i],*rc)) {
            grid[i].push_back(*rc);
            if(++count == 4) break;
        }
    }
}


void CollisionMap1::Collide() 
{
    for (const std::vector<CollisionRect>& candidates : grid) {
        for (const CollisionRect& left : candidates) {
            for (const CollisionRect& right : candidates) {
                if (left.id == right.id) continue;
                if (isOverlapped(left, right))
                    events.push_back({ left.id, right.id });
            }
        }
    }
}

void CollisionMap1::DebugPrint()
{
    for(auto it : grid) {        
        int sz = it.capacity();
        char str[128];
        sprintf_s(str,128, "capacity: %d\n", sz);
        OutputDebugStringA(str);
    }

    OutputDebugStringA("--------- end --------");
}
