#include "Enemy.h"
#include <cassert>
#include <ctime>
#include <cstdlib>

namespace
{
	const int ENEMY_SIZE = 32;
	const int ENEMY_DRAW_SIZE = 32;
	int timer = 0;
	// 三秒で向きかわる
	// 半秒で移動
	// タイマーの補正
	const float DIR_CHANGE_TIME = 3.0f;
	const float MOVE_TIME = 0.5f;

	float moveInclease = 0.00f;
	int animIndex = 0;
}

Enemy::Enemy(Pointf _position) :
	position_(_position),
	hImage_(-1),
	currDir(DOWN),
	nextDir(UP),
	dirTimer_(0.f),
	moveTimer_(0.f),
	animTimer_(0.f)
{
	hImage_ = LoadGraph("data/QueueCat_half.png");
	assert(hImage_ > -1);
	srand(uint32_t(time(nullptr)));
	anim = new int[4] {0, 1, 2, 1}; // 3秒で向きが変わるため、アニメーションが回らない。
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	dirTimer_ += Time::DeltaTime();
	moveTimer_ += Time::DeltaTime();
	animTimer_ += Time::DeltaTime();
	if (animTimer_ > 0.5f)
	{
		if (animIndex <= 4)
		{
			animIndex += 1;
		}
		else
		{
			animIndex = 0;
		}
		animTimer_ = 0.0f;
	}

	if (dirTimer_ > DIR_CHANGE_TIME)
	{

		// 次の方向をあらかじめ計算
		nextDir = DIR(rand() % MAX_DIR);

		// 次の方向が今の方向と同じであれば、再度計算
		while (nextDir == currDir)	// 同じでなくなるまで繰り返す
		{
			nextDir = DIR(rand() % MAX_DIR);
		}
		currDir = nextDir;

		dirTimer_ = 0.0f;
	}

	if (moveTimer_ > MOVE_TIME)
	{
		moveInclease = ENEMY_DRAW_SIZE;
		moveTimer_ = 0.0f;
	}

	switch (currDir)
	{
	case UP:
		dir = "UP";
		if (position_.y - ENEMY_DRAW_SIZE >= ENEMY_DRAW_SIZE)
		{
			position_.y -= moveInclease;
		}
		break;
	case DOWN:
		dir = "DOWN";
		if (position_.y + ENEMY_DRAW_SIZE < STAGE_HEIGHT * ENEMY_DRAW_SIZE - ENEMY_DRAW_SIZE)
		{
			position_.y += moveInclease;
		}
		break;
	case LEFT:
		dir = "LEFT";
		if (position_.x - ENEMY_DRAW_SIZE >= ENEMY_DRAW_SIZE)
		{
			position_.x -= moveInclease;
		}
		break;
	case RIGHT:
		dir = "RIGHT";
		if (position_.x + ENEMY_DRAW_SIZE < STAGE_WIDTH * ENEMY_DRAW_SIZE - ENEMY_DRAW_SIZE)
		{
			position_.x += moveInclease;
		}
		break;
	default:
		break;
	}
	moveInclease = 0.0f;
}

void Enemy::Draw()
{
	//int animIndex = int(animTimer_) % 4;
	Rect imageRect[MAX_DIR] = // 変換用配列
	{
		{anim[animIndex] * ENEMY_SIZE, 3 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 上
		{anim[animIndex] * ENEMY_SIZE, 0 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 下
		{anim[animIndex] * ENEMY_SIZE, 1 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 左
		{anim[animIndex] * ENEMY_SIZE, 2 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}  // 右
	};

	DrawRectExtendGraph(position_.x, position_.y,
						position_.x + CHARA_SIZE, position_.y + CHARA_SIZE,
						imageRect[currDir].x, imageRect[currDir].y,
						imageRect[currDir].w, imageRect[currDir].h,
						hImage_, TRUE);

	DrawString(0, 0, dir.c_str(), 0xffffff);
	DrawFormatString(100, 0, 0xffffff, "NextDirChange:%f", dirTimer_);
	DrawFormatString(500, 0, 0xffffff, "NextMove:%f", moveTimer_);
}
