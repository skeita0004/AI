#ifndef GLOBAL_H
#define GLOBAL_H

// 整数型2次元ベクトル
struct Point
{
	int x;
	int y;
};

// 浮動小数点型2次元ベクトル
struct Pointf
{
	float x;
	float y;
};

// 矩形
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