#include "pch.h"
#include "CollisionMap1.h"

void CollisionMap1::Setup(int w, int h)
{
    size_x = w / PARTITIONS + 1;
    size_y = h / PARTITIONS + 1;

    grid.clear();
    grid.resize(size_x * size_y);

    events.clear();
}

void CollisionMap1::Insert(Rect_t* rc)
{
    int left = (((int)rc->l)/PARTITIONS);
    int right = (((int)rc->r)/PARTITIONS);
    int top = (((int)rc->t)/PARTITIONS);
    int bottom = (((int)rc->b)/PARTITIONS);

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

void CollisionMap1::Collide() 
{
    for (const std::vector<Rect_t>& candidates : grid) {
        for (const Rect_t& left : candidates) {
            for (const Rect_t& right : candidates) {
                if (left.id == right.id) continue;
                if (collided(left, right))
                    events.push_back({ left.id, right.id });
            }
        }
    }
}
