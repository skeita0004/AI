#pragma once

// �����^2�����x�N�g��
struct Point
{
	int x;
	int y;
};

inline Point operator *(Point a, int b)
{
	Point c;
	c.x = a.x * b;
	c.y = a.y * b;
	return c;
}

// ���������_�^2�����x�N�g��
struct Pointf
{
	float x;
	float y;
};

// ��`
struct Rect
{
	int x;
	int y;
	int w;
	int h;
};

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_DIR
};


const int CHARA_SIZE = 32;
const int STAGE_WIDTH = 39;
const int STAGE_HEIGHT = 21;
