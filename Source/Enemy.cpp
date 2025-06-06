#include "Enemy.h"
#include <cassert>
#include <ctime>
#include <cstdlib>
#include "../ImGui/imgui.h"

// ファイルから読み込めるようにすること。
namespace
{
	const int ENEMY_SIZE = 32;
	const int ENEMY_DRAW_SIZE = 32;
	int timer = 0;
	// 三秒で向きかわる
	// 半秒で移動
	// タイマーの補正
	const float DIR_CHANGE_TIME = 3.0f;
	const float MOVE_TIME = 0.1f;
	const float ANIM_INTERVAL_TIME = 0.5f;


	static float animTimer_;
	static int animIndex_;
}

Enemy::Enemy(Point _position) :
	position_(_position),
	hImage_(-1),
	currDir_(DOWN),
	nextDir(UP),
	dirTimer_(0.f),
	moveTimer_(0.f),
	isNotWall_(true),
	state_(EState::NORMAL)
{
	srand(uint32_t(time(nullptr)));
	hImage_ = LoadGraph("data/QueueCat_half.png");
	assert(hImage_ > -1);
	Point randPosition = { GetRand(STAGE_WIDTH - 2) + 1, GetRand(STAGE_HEIGHT - 2) + 1 };
	currDir_ = DIR(rand() % MAX_DIR);
	position_ = { randPosition.x, randPosition.y};
	anim = new int[4] {0, 1, 2, 1}; // 3秒で向きが変わるため、アニメーションが回らない。
	animTimer_ = ANIM_INTERVAL_TIME;
	animIndex_ = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	dirTimer_ += Time::DeltaTime();
	moveTimer_ += Time::DeltaTime();

	if (animTimer_ < 0)
	{
		animIndex_ = (++animIndex_) % 4;
		animTimer_ = ANIM_INTERVAL_TIME + animTimer_;
	}
	animTimer_ -= Time::DeltaTime();

	//if (dirTimer_ > DIR_CHANGE_TIME)
	//{

	//	//// 次の方向をあらかじめ計算
	//	//nextDir = DIR(rand() % MAX_DIR);

	//	//// 次の方向が今の方向と同じであれば、再度計算
	//	//while (nextDir == currDir)	// 同じでなくなるまで繰り返す
	//	//{
	//	//	nextDir = DIR(rand() % MAX_DIR);
	//	//}
	//	//currDir = nextDir;

	//	TurnLeft();
	//	
	//	dirTimer_ = 0.0f;
	//}
	int moveInclease = 0;

	if (moveTimer_ > MOVE_TIME)
	{
		moveInclease = 1;
		moveTimer_ = 0.0f;
	}
	
	if (isNotWall_)
	{
		switch (currDir_)
		{
		case UP:
			dir = "UP"; // だめ
			position_.y -= moveInclease;
			break;
		case DOWN:
			dir = "DOWN"; // ここはぶつかる
			position_.y += moveInclease;
			break;
		case LEFT:
			dir = "LEFT"; // だめ
			position_.x -= moveInclease;
			break;
		case RIGHT:
			dir = "RIGHT";// ここもぶつかる
			position_.x += moveInclease;
			break;
		default:
			break;
		}
	}
	//else
	//{
	//	TurnLeft();
	//}
	moveInclease = 0;
	
	/*
	* 壁に当たるまで現在の方向を維持して直進する。
	* 
	* 壁に当たったら、当たった壁に応じて関数を呼ぶ
	* 
	* switchケースで行けるだろう
	*/

	/* 
	* このゲームにおいて座標は、int型であり、0～STAGE_WIDTHおよびSTAGE_HEIGHTまでしか
	* 扱わない。描画するときに足りない分足されるからである。
	* そのため、当たり判定は蛇ゲームのものを持ってこれる。
	* 次に移動する場所を向きごとに持つ、あらかじめ判定する方式を用いる。
	* enum struct NextDir
	* ステージのマス目分のループを行う
	* 次の移動場所が壁であれば、当たり判定を行った後に、向きを変える。
	*/ 

}

void Enemy::Draw()
{
	//int animIndex = int(animTimer_) % 4;
	Rect imageRect[MAX_DIR] = // 変換用配列
	{
		{anim[animIndex_] * ENEMY_SIZE, 3 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 上
		{anim[animIndex_] * ENEMY_SIZE, 0 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 下
		{anim[animIndex_] * ENEMY_SIZE, 1 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}, // 左
		{anim[animIndex_] * ENEMY_SIZE, 2 * ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE}  // 右
	};

	ImGui::Begin("Enemy Position");

	ImGui::InputInt("position.x", &position_.x);
	ImGui::InputInt("position.y", &position_.y);

	int x = position_.x * ENEMY_DRAW_SIZE;
	int y = position_.y * ENEMY_DRAW_SIZE;

	ImGui::InputInt("drawStartPosition.x", &x);
	ImGui::InputInt("drawStartPosition.y", &y);

	DrawRectExtendGraph(x, y,
						(position_.x + 1) * ENEMY_DRAW_SIZE, (position_.y + 1) * ENEMY_DRAW_SIZE,
						imageRect[currDir_].x, imageRect[currDir_].y,
						imageRect[currDir_].w, imageRect[currDir_].h,
						hImage_, TRUE);

#if _DEBUG
	DrawString(0, 0, dir.c_str(), 0xffffff);
	DrawFormatString(100, 0, 0xffffff, "NextDirChange:%f", dirTimer_);
	DrawFormatString(350, 0, 0xffffff, "NextMove:%f", moveTimer_);
	DrawFormatString(520, 0, 0xffffff, "NextAnim:%05f", animTimer_);
	DrawFormatString(710, 0, 0xffffff, "AnimIndex:%d", animIndex_);
#endif

	ImGui::End();
}

void Enemy::TurnLeft()
{
	switch (currDir_)
	{
	case UP:
		currDir_ = LEFT;
		break;
	case DOWN:
		currDir_ = RIGHT;

		break;
	case LEFT:
		currDir_ = DOWN;

		break;
	case RIGHT:
		currDir_ = UP;

		break;
	case MAX_DIR:
		break;
	default:
		break;
	}
}

void Enemy::TurnRight()
{
	switch (currDir_)
	{
	case UP:
		currDir_ = RIGHT;
		break;
	case DOWN:
		currDir_ = LEFT;
		break;
	case LEFT:
		currDir_ = UP;
		break;
	case RIGHT:
		currDir_ = DOWN;
		break;
	case MAX_DIR:
		break;
	default:
		break;
	}
}

void Enemy::TurnBack()
{
	switch (currDir_)
	{
	case UP:
		currDir_ = DOWN;
		break;
	case DOWN:
		currDir_ = UP;
		break;
	case LEFT:
		currDir_ = RIGHT;
		break;
	case RIGHT:
		currDir_ = LEFT;
		break;
	case MAX_DIR:
		break;
	default:
		break;
	}
}
