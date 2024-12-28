
struct Transform_t
{
    Vec2 pos;
    float rot;
    Vec2 scale;
};


struct Target_t 
{
    Target_t() : prev_position(0.f, 0.f), lock(false) {}

    ecs_id_t target;
    Vec2 prev_position;
    Vec2 aim_position;
    float angle;
    float distance;
    bool lock;
};


struct Graphics_t 
{
    
};


struct Physics_t
{
    Vec2 velocity;
    float angularSpeed;

};

struct Geometry_t
{

};

struct Input_t
{

};

struct Gui_t
{

};

