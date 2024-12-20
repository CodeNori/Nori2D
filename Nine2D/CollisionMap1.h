#pragma once


class CollisionMap1
{
    static const int PARTITIONS = 256;
public:
    int size_x;
    int size_y;
    float start_x = 0.f;
    float start_y = 0.f;

    bool isEnabled = true;

    std::vector<std::vector<CollisionRect>> grid;
    std::vector<CollisionEvent> events;

    void Setup(float sx, float sy, int w, int h);

    void Insert(CollisionRect* rc);

    void Collide();

    bool collided(const CollisionRect& left, const CollisionRect& right) 
    {
        return ((left.r > right.l) &&
                (right.r > left.l) &&
                (left.t > right.b) &&
                (right.t > left.b));
    }
};

