#include "Player.h"

Player::Player() :
	GameObject(),
	position_({64, 64})
{
}

Player::~Player()
{
}

void Player::Update()
{
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
