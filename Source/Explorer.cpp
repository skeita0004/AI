#include "Explorer.h"
#include <../ImGui/imgui.h>

namespace
{
	const int ENEMY_SIZE = 32;
	const int ENEMY_DRAW_SIZE = 32;

	const float DIR_CHANGE_TIME = 3.0f;
	const float MOVE_TIME = 0.2f;
	const float ANIM_INTERVAL_TIME = 0.5f;

	float animTimer_;
	int animIndex_;
	int timer = 0;
}

Explorer::Explorer(Point _position) :
	hImage_(-1),
	position_(-1, -1),
	currDir_(RIGHT),
	nextDir_(RIGHT),
	dir_("RIGHT"),
	dirTimer_(DIR_CHANGE_TIME),
	moveTimer_(MOVE_TIME),
	anim(nullptr),
	isWall_(false)
{
	hImage_ = LoadGraph("data/QueueCat_half.png");
	anim = new int[4]
		{
			0, 1, 2, 1
		};
}

Explorer::~Explorer()
{
}

void Explorer::Update()
{
	// １．
	// 全経路を探索し、ゴールまでの最短経路を求める
	// 求まった経路は、キューに入れられ、
	// 探検者は一定間隔(何秒とか、何フレームとか)で次の場所へ進む
	// 
	// ２．
	// 別の方法としては、経路探索後に、ゴールへと至らない経路をすべて
	// 壁として設定し、壁にぶつかったら壁ではない方向へ向き、
	// そして、現在向いている方向とは逆の方向を向かないようにすれば、
	// 角で曲がるので、進むべき方向は一つに絞れる。
	// 
	// 今回は、２の方法で行くことにする。
	// 
	// 探検者は、迷路の不要な経路を壁に書き換える権限を持つ。
	// 

	// FindPath() <- 1フレームに１マスごとやってほしいのよね。(西麻布のママより)


	dirTimer_ += DeltaTime::GetDeltaTime();

	Move(MOVE_TIME);
}

void Explorer::Draw()
{
	Rect<int> imageRect[MAX_DIR] = // 変換用配列
	{
		{ // 上
			anim[animIndex_] * ENEMY_SIZE,
			3 * ENEMY_SIZE,
			ENEMY_SIZE,
			ENEMY_SIZE
		},
		{ // 下
			anim[animIndex_] * ENEMY_SIZE,
			0 * ENEMY_SIZE,
			ENEMY_SIZE,
			ENEMY_SIZE
		},
		{ // 左
			anim[animIndex_] * ENEMY_SIZE,
			1 * ENEMY_SIZE,
			ENEMY_SIZE,
			ENEMY_SIZE
		},
		{ // 右
			anim[animIndex_] * ENEMY_SIZE,
			2 * ENEMY_SIZE,
			ENEMY_SIZE,
			ENEMY_SIZE
		}
	};

	ImGui::Begin("Enemy Position");

	ImGui::InputInt("position.x", &position_.x);
	ImGui::InputInt("position.y", &position_.y);

	int x = position_.x * ENEMY_DRAW_SIZE;
	int y = position_.y * ENEMY_DRAW_SIZE;

	ImGui::InputInt("drawStartPosition.x", &x);
	ImGui::InputInt("drawStartPosition.y", &y);

	DrawRectExtendGraph(x, y,
						(position_.x + 1) * ENEMY_DRAW_SIZE,
						(position_.y + 1) * ENEMY_DRAW_SIZE,
						imageRect[currDir_].x, imageRect[currDir_].y,
						imageRect[currDir_].w, imageRect[currDir_].h,
						hImage_, TRUE);

#if _DEBUG
	DrawString(0, 0, dir_.c_str(), 0xffffff);
	DrawFormatString(100, 0, 0xffffff, "NextDirChange:%f", dirTimer_);
	DrawFormatString(350, 0, 0xffffff, "NextMove:%f", moveTimer_);
	DrawFormatString(520, 0, 0xffffff, "NextAnim:%05f", animTimer_);
	DrawFormatString(710, 0, 0xffffff, "AnimIndex:%d", animIndex_);
#endif

	ImGui::End();
}

void Explorer::TurnLeft()
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
	}
}

void Explorer::TurnRight()
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
	}
}

void Explorer::TurnBack()
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
	}
}

void Explorer::Move(float _moveInterval)
{
	moveTimer_ += DeltaTime::GetDeltaTime();

	if (animTimer_ < 0)
	{
		animIndex_ = (++animIndex_) % 4;
		animTimer_ = ANIM_INTERVAL_TIME + animTimer_;
	}
	animTimer_ -= DeltaTime::GetDeltaTime();

	int moveIncrease = 0;

	if (moveTimer_ > _moveInterval)
	{
		moveIncrease = 1;
		moveTimer_ = 0.0f;
	}

	if (isWall_)
	{
		// 壁でない方向をむく
		// 現在向いている方向と逆の方向を向かない
		// っていう仕様にしてほしいなぁ。
		//int tmpDir = 0;
		//while (true)
		//{
		//	nextDir_ = (DIR)tmpDir;
		//	tmpDir++;
		//	//if (もし、向いている方向がcurrの逆でなく、壁でない方向なら)
		//	//()
		//	{
		//		break;
		//	}
		//}

		//switch ()
		//{
		//	default:
		//		break;
		//}
		TurnLeft();
	}
	else
	{
		switch (currDir_)
		{
			case UP:
				dir_ = "UP";
				position_.y -= moveIncrease;
				break;

			case DOWN:
				dir_ = "DOWN";
				position_.y += moveIncrease;
				break;

			case LEFT:
				dir_ = "LEFT";
				position_.x -= moveIncrease;
				break;

			case RIGHT:
				dir_ = "RIGHT";
				position_.x += moveIncrease;
				break;
		}
	}
	moveIncrease = 0;
}

void Explorer::FindPathDFS()
{
	// 三方が壁であるとき、そこがゴールの位置と異なる場合、
	// その経路は不要であるので、壁にする。
	// DFSを用いる

	// 2分木を作る

}

void Explorer::FindPathBFS()
{

}

void Explorer::FindPathDijkstra()
{
}

void Explorer::FindPathAStar()
{
}
