#pragma once

template <typename T>
struct Vector {
    T x;
    T y;
    Vector<T> operator+(const Vector<T>& rhs) const
    {
        return Vector{ x + rhs.x, y + rhs.y };
    }
};

