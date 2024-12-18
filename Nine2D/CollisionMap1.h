#pragma once
class CollisionMap1
{
    static const int PARTITIONS = 256;
public:
    int size_x;
    int size_y;
    
    bool isEnabled = true;

    std::vector<std::vector<Rect_t>> grid;
    std::vector<CollisionEvent> events;

    void Setup(int w, int h);

    void Insert(Rect_t* rc);

    void Collide();

    bool collided(const Rect_t& left, const Rect_t& right) 
    {
        return ((left.r > right.l) &&
                (right.r > left.l) &&
                (left.t > right.b) &&
                (right.t > left.b));
    }
};

