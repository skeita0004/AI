#ifndef GLOBAL_H
#define GLOBAL_H

// �����^2�����x�N�g��
struct Point
{
	int x;
	int y;
};

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
	NONE,
	MAX_DIR
};

const int CHARA_SIZE = 32;

#endif