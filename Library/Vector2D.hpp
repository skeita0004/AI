/******************************************
 *              Vector2.hpp               *
 *         auther : keita saito           *
 ******************************************/

#pragma once

#include <cassert>

template <typename TYPE>
struct Vector2D
{
    TYPE x;
    TYPE y;

    Vector2D() : Vector2D(static_cast<TYPE>(0), static_cast<TYPE>(0)) {}
    Vector2D(TYPE _x, TYPE _y) : x(_x), y(_y){}

    // 変換コンストラクタ
    template <typename OTHER_TYPE>
    Vector2D(const Vector2D<OTHER_TYPE>& other)
        : x(static_cast<TYPE>(other.x)), y(static_cast<TYPE>(other.y)) {}

    Vector2D operator+(const Vector2D& _rValue) const
    {
        Vector2D tmp;
        tmp.x = x + _rValue.x;
        tmp.y = y + _rValue.y;
        return tmp;
    }

    Vector2D operator-(const Vector2D& _rValue) const
    {
        Vector2D tmp;
        tmp.x = x - _rValue.x;
        tmp.y = y - _rValue.y;
        return tmp;
    }

    Vector2D operator*(const TYPE& _rValue) const
    {
        Vector2D tmp;
        tmp.x = x * _rValue;
        tmp.y = y * _rValue;
        return tmp;
    }

    Vector2D operator/(const TYPE& _rValue) const
    {
        assert(_rValue != 0); // ゼロ除算を排除

        Vector2D tmp;
        tmp.x = x / _rValue;
        tmp.y = y / _rValue;
        return tmp;
    }
};