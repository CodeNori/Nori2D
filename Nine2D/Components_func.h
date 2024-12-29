

inline
bool isOverlapped(const CollisionRect& left, const CollisionRect& right) 
{
    return ((left.right > right.left) &&
            (right.right > left.left) &&
            (left.top > right.bottom) &&
            (right.top > left.bottom));
}

