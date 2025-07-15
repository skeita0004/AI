#pragma once

inline const float ToDegree(float& _radian)
{
	return _radian * 180.f / DX_PI_F;
}

inline const float ToRadian(float& _degree)
{
	return _degree * DX_PI_F / 180.f;
}

// 整数型2次元ベクトル
struct Point
{
	int x;
	int y;

	Point() : Point(0, 0){}
	Point(int _x, int _y) : x(_x), y(_y){}
	
	Point Rotate(float _angle)
	{
		return Point(x * (int)cosf(_angle) - y * (int)sinf(_angle),
					 x * (int)sinf(_angle) + y * (int)cosf(_angle));
	}
};

inline Point operator *(Point a, int b)
{
	Point c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

inline Point operator +(Point a, Point b)
{
	Point c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

// 浮動小数点型2次元ベクトル
struct Pointf
{
	float x;
	float y;

	Pointf() : Pointf(0, 0) {}
	Pointf(int _x, int _y) : x(_x), y(_y) {}

	Pointf Rotate(float _angle)
	{
		return Pointf(x * cosf(_angle) - y * sinf(_angle),
					  x * sinf(_angle) + y * cosf(_angle));
	}
};

// 矩形
template <typename TYPE>
struct Rect
{
	TYPE x;
	TYPE y;
	TYPE w;
	TYPE h;
};

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_DIR
};

const Point NEXT_POSITION[] =
{
	{0, -1},
	{0, 1},
	{-1, 0},
	{1, 0}
};


const int CHARA_SIZE = 32;
const int STAGE_WIDTH = 39;
const int STAGE_HEIGHT = 21;
