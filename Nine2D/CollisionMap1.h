#pragma once


class CollisionMap1
{
    static const int PARTITIONS = 256;
public:
    int size_x, size_y;
    float start_x, start_y;
    int end_x, end_y;

    bool isEnabled = true;

    std::vector<std::vector<CollisionRect>> grid;
    std::vector<CollisionRect> gridRect;
    std::vector<CollisionEvent> events;

    void Setup(float sx, float sy, int w, int h);
    void Clear_test();
    void Insert(CollisionRect* rc);
    void Insert1(CollisionRect* rc);
    void Insert2(CollisionRect* rc);
    void Collide();
    void DebugPrint();

};

