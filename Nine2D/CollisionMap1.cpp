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
