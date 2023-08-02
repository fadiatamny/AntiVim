#ifndef VEC2F_HPP
#define VEC2F_HPP

class Vec2f
{
public:
    Vec2f(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Vec2f(float x)
    {
        this->x = x;
        this->y = x;
    }
    Vec2f()
    {
        this->x = 0;
        this->y = 0;
    }

    Vec2f operator+(const Vec2f &other) const
    {
        return Vec2f(this->x + other.x, this->y + other.y);
    }
    Vec2f operator-(const Vec2f &other) const
    {
        return Vec2f(this->x - other.x, this->y - other.y);
    }
    Vec2f operator*(const Vec2f &other) const
    {
        return Vec2f(this->x * other.x, this->y * other.y);
    }
    Vec2f operator/(const Vec2f &other) const
    {
        return Vec2f(this->x / other.x, this->y / other.y);
    }

    Vec2f add(const Vec2f &other) const
    {
        return *this + other;
    }
    Vec2f sub(const Vec2f &other) const
    {
        return *this - other;
    }
    Vec2f mul(const Vec2f &other) const
    {
        return *this * other;
    }
    Vec2f div(const Vec2f &other) const
    {
        return *this / other;
    }

public:
    float x;
    float y;
};

#endif // VEC2F_HPP