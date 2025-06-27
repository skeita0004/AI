﻿#include "Player.h"
#include "../Library/Input.h"
#include <cassert>

namespace
{
	int animFrame[4] {0, 1, 2, 1}; // 3秒で向きが変わるため、アニメーションが回らない。
	const float ANIM_INTERVAL = 0.2f;
	const DIR PLAYER_INIT_DIR = { DOWN };
	const int PLAYER_IMAGE_SIZE{ 32 };
	const int PLAYER_DRAW_SIZE{ 32 };
}

Player::Player() :
	Player({0, 0})
{
}

Player::Player(Point _position) :
	GameObject(),
	position_(_position),
	currDir_(RIGHT),
	hImage_(-1),
	isNotWall_(true)
{
	hImage_ = LoadGraph("data/white_cat.png"); // ここpngに
	assert(hImage_ > 0);
}


Player::~Player()
{
}

void Player::Update()
{

	if (Input::IsKeyDown(KEY_INPUT_W))
	{
		if (position_.y - 1 > 0)
		{
			currDir_ = UP;
			position_.y -= 1;
		}
	}
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		if (position_.y + 1 < STAGE_HEIGHT - 1)
		{
			currDir_ = DOWN;
			position_.y += 1;
		}
	}
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		if (position_.x - 1 > 0)
		{
			currDir_ = LEFT;
			position_.x -= 1;
		}
	}
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		currDir_ = RIGHT;
		if (position_.x + 1 < STAGE_WIDTH - 1)
		{
			position_.x += 1;
		}
	}
}

void Player::Draw()
{
	static float animTimer = ANIM_INTERVAL;
	static int frame = 0;
	int nowFrame = animFrame[frame];

	Rect imageRect[MAX_DIR] =
	{
		{nowFrame * PLAYER_IMAGE_SIZE, 3 * PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE},
		{nowFrame * PLAYER_IMAGE_SIZE, 0 * PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE},
		{nowFrame * PLAYER_IMAGE_SIZE, 1 * PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE},
		{nowFrame * PLAYER_IMAGE_SIZE, 2 * PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE, PLAYER_IMAGE_SIZE},
	};

	//DrawBox(position_.x, position_.y,
	//	position_.x + CHARA_SIZE, position_.y + CHARA_SIZE,
	//	0xffffff, FALSE);
	DrawRectExtendGraph(position_.x * PLAYER_DRAW_SIZE, position_.y * PLAYER_DRAW_SIZE,
		(position_.x + 1) * PLAYER_DRAW_SIZE, (position_.y + 1) * PLAYER_DRAW_SIZE,
		imageRect[currDir_].x, imageRect[currDir_].y, 
		imageRect[currDir_].w, imageRect[currDir_].h,
		hImage_, TRUE);

	if (animTimer < 0)
	{
		frame = (++frame) % 4;
		animTimer = ANIM_INTERVAL + animTimer;
	}
	animTimer -= Time::DeltaTime();
}
