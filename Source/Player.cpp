#include "Player.h"
#include "../Library/Input.h"

Player::Player() :
	GameObject(),
	position_({64, 64}),
	currDir_(RIGHT)
{
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::IsKeyDown(KEY_INPUT_W))
	{
		position_.y -= CHARA_SIZE;
	}
	if (Input::IsKeyDown(KEY_INPUT_S))
	{
		position_.y += CHARA_SIZE;
	}
	if (Input::IsKeyDown(KEY_INPUT_A))
	{
		position_.x -= CHARA_SIZE;
	}
	if (Input::IsKeyDown(KEY_INPUT_D))
	{
		position_.x += CHARA_SIZE;
	}
	GetMousePoint(&position_.x, &position_.y);
	position_ = position_ * CHARA_SIZE;
}

void Player::Draw()
{
	DrawBox(position_.x, position_.y,
		position_.x + CHARA_SIZE, position_.y + CHARA_SIZE,
		0x0085dc, TRUE);
	DrawBox(position_.x, position_.y,
		position_.x + CHARA_SIZE, position_.y + CHARA_SIZE,
		0xffffff, FALSE);
}
