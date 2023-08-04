#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>

template <typename T = float>
class Vec2
{
public:
    Vec2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    Vec2(float x)
    {
        this->x = x;
        this->y = x;
    }
    Vec2()
    {
        this->x = 0;
        this->y = 0;
    }

    Vec2 operator+(const Vec2 &other) const
    {
        return Vec2(this->x + other.x, this->y + other.y);
    }
    Vec2 operator-(const Vec2 &other) const
    {
        return Vec2(this->x - other.x, this->y - other.y);
    }
    Vec2 operator*(const Vec2 &other) const
    {
        return Vec2(this->x * other.x, this->y * other.y);
    }
    Vec2 operator/(const Vec2 &other) const
    {
        return Vec2(this->x / other.x, this->y / other.y);
    }

    Vec2 add(const Vec2 &other) const
    {
        return *this + other;
    }
    Vec2 sub(const Vec2 &other) const
    {
        return *this - other;
    }
    Vec2 mul(const Vec2 &other) const
    {
        return *this * other;
    }
    Vec2 div(const Vec2 &other) const
    {
        return *this / other;
    }

public:
    T x;
    T y;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vec2<T> &vec)
{
    os << "Vec2(" << vec.x << ", " << vec.y << ")";
    return os;
}

#endif // VEC2_HPP