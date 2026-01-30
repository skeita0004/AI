#include "Explorer.h"
#include <../ImGui/imgui.h>
#include <stack>
#include <queue>
#include <map>
#include "Maze.hpp"
#include "Stage.h"
#include "Input.h"

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
	pStage_ = FindGameObject<Stage>();
	pMaze_  = pStage_->GetMazeP();
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
	if (Input::IsKeyDown(KEY_INPUT_RETURN))
	{
		FindPathBFS();
	}

	//dirTimer_ += DeltaTime::GetDeltaTime();

	//Move(MOVE_TIME);
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
	enum SearchState : int8_t
	{
		NONE,
		NOT_YET,
		DONE,
		TO_GOAL
	};

	struct FinderState
	{
		Point pos;
		std::map<DIR, SearchState> nodeInfo;
	};

	FinderState finderState;
	bool goaled{ false };
	std::stack<FinderState> node;

	// 三方が壁であるとき、そこがゴールの位置と異なる場合、
	// その経路は不要であるので、壁にする。
	// DFSを用いる

	// 2分木を作る

	// 最初に4方向調べ、進める方向を記録し、スタックへとpushする
	for (int i = 0; i < MAX_DIR; i++)
	{
		if (pStage_->GetMazeState(finderState.pos + NEXT_POSITION[i]) == Maze::MazeState::WALL)
		{
			finderState.nodeInfo.emplace((DIR)i, NONE);
		}
	}
	node.push(finderState);

	while (true)
	{
		if (goaled)
		{
			break;
		}
	// 進める方向のうち、ランダムな方向を選び、そちらへ進む
		
		

	// もし壁に突き当たったら、自分の現在位置とゴールの位置を比較し、
	// 一致していればゴールフラグをtrueにする
	
		//if (finderState.pos == )
		{

		}

	// 一致していなければ、左右を確認し、道がある方へ進んでいく
	// 道がなければ行き止まりなので、スタックの先頭を読み、その位置へ戻り、
	// 自身が進んだ方向を壁として設定する
	// 
	// 分岐があった場合、スタックへとpushする
	// 
	// 戻ってきたときに、状態：了の分岐に壁を設定する
	// 
	}

	// ここでは、goaledがtrueになったあとの後処理を行う
	// ゴールへと至らないことが確定している、未探査の分岐の入口をすべて塞いでしまう。
	// wallでもいいが、別の状態を追加するのもあり。(透明な壁として、内部的に扱う)
	// 

}

void Explorer::FindPathBFS()
{
	// 上下左右みる
	// いける方にいく
	// 

	Point currPos{pStage_->IndexToPoint(pMaze_->GetStart())};
	std::queue<Point> BFSQueue;

	BFSQueue.push(currPos);
	pStage_->SetMazeState(currPos, Maze::MazeState::FOUND); // スタート地点を探索済みにする

	while (true)
	{
		static int stepCount = 0;
		
		int wayCount{0};
		// ここで次の一歩で行ける道を探している
		for (int i = 0; i < DIR::MAX_DIR; i++)
		{
			// 現在の位置に、ある方向に向けて一歩先の座標を求める。
			Point tmp = currPos + NEXT_POSITION[i];


			if (pStage_->GetMazeState(tmp) == Maze::MazeState::WAY)
			{
				// 行ける場所をenq
				BFSQueue.push(tmp);

				// 行ける場所を探索済みにする
				pStage_->SetMazeState(tmp, Maze::MazeState::FOUND);
				pStage_->SetStepCount(tmp, stepCount);
				wayCount++;
			}
		}

		// 4方向がふさがっていたら、次のループに進む
		if (wayCount == 0)
		{
			if (BFSQueue.size() > 0)
			{
				stepCount++;
				currPos = BFSQueue.front();
				BFSQueue.pop();
			}
			else
			{
				// キューのサイズが0なら終了 <- 嫌過ぎるけど、ゴールしたと見做すしかない
				break;
			}
			continue;
		}
	}
}

void Explorer::FindPathDijkstra()
{
}

void Explorer::FindPathAStar()
{
}