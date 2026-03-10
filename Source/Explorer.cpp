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
	isWall_(false),
	enabledSearch_(true)
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
	// FindPath() <- 1フレームに１マスごとやってほしいのよね。(西麻布のママより)
	if (Input::IsKeyHold(KEY_INPUT_RETURN) and enabledSearch_)
	{
		//FindPathBFS();
		FindPathDijkstra();
	}
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
	static NodeData currNodeData({0, 0}, 0);

	// Start地点(1, 1)をQueueに入れる
	static std::queue<NodeData> BFSQueue;

	static bool first = true;

	if (first)
	{
		BFSQueue.push(NodeData(pStage_->IndexToPoint(pMaze_->GetStart()), 0));

		// Queueの先頭をcurrPosに設定
		//currPos = BFSQueue.front();
		//BFSQueue.pop();
		pStage_->SetMazeState(BFSQueue.front().pos, Maze::MazeState::FOUND); // スタート地点を探索済みにする
		pStage_->SetStepCount(BFSQueue.front().pos, BFSQueue.front().stepCount);
		first = false;
	}

	currNodeData = BFSQueue.front();
	BFSQueue.pop();

	int currStepCount = pStage_->GetStepCount(currNodeData.pos);
		
	for (int i = 0; i < MAX_DIR; i++)
	{
		NodeData nextNodeData{ currNodeData.pos + NEXT_POSITION[i], currStepCount + 1 };
		Maze::MazeState state = pStage_->GetMazeState(nextNodeData.pos);
		if (nextNodeData.pos == pStage_->IndexToPoint(pMaze_->GetGoal()))
		{
			currNodeData = nextNodeData;
			pStage_->SetStepCount(currNodeData.pos, currNodeData.stepCount);
			pStage_->SetMazeState(currNodeData.pos, Maze::MazeState::FOUND);
			break;
		}
		if (state == Maze::MazeState::WAY)
		{
			// いける地点をEnqueue
			BFSQueue.push(NodeData(nextNodeData));
			pStage_->SetStepCount(nextNodeData.pos, nextNodeData.stepCount); // ループ中のstep数は同じにしたい
			pStage_->SetMazeState(nextNodeData.pos, Maze::MazeState::FOUND);
		}
	}

	if (currNodeData.pos == pStage_->IndexToPoint(pMaze_->GetGoal()))
	{
		// ここでフラグを下げる
		enabledSearch_ = false;
		EtchingBFSPath(currNodeData.stepCount);
		currNodeData = NodeData(Point(0, 0), 0);
		first = true;
		BFSQueue = std::queue<NodeData>();
		return;
	}
}

void Explorer::FindPathDijkstra()
{
	static DijkstraND currNodeData({0, 0}, 0, 0);

	// Start地点(1, 1)をQueueに入れる
	static std::priority_queue<DijkstraND> BFSQueue;

	static bool first = true;

	if (first)
	{
		BFSQueue.push(DijkstraND(pStage_->IndexToPoint(pMaze_->GetStart()), 0));

		pStage_->SetMazeState(BFSQueue.top().pos, Maze::MazeState::FOUND); // スタート地点を探索済みにする
		pStage_->SetStepCount(BFSQueue.top().pos, BFSQueue.top().stepCount);
		first = false;
	}

	{
		int overStep = 0;

		currNodeData = BFSQueue.top();
		BFSQueue.pop();

		int currStepCount = pStage_->GetStepCount(currNodeData.pos);

		for (int i = 0; i < MAX_DIR; i++)
		{
			DijkstraND nextNodeData{currNodeData.pos + NEXT_POSITION[i], currStepCount + 1, pStage_->GetMazePathCost(currNodeData.pos + NEXT_POSITION[i])};
			Maze::MazeState state = pStage_->GetMazeState(nextNodeData.pos);
			if (nextNodeData.pos == pStage_->IndexToPoint(pMaze_->GetGoal()))
			{
				currNodeData = nextNodeData;
				pStage_->SetStepCount(currNodeData.pos, currNodeData.stepCount);
				pStage_->SetMazeState(currNodeData.pos, Maze::MazeState::FOUND);
				break;
			}
			if (state == Maze::MazeState::WAY)
			{
				// いける地点をEnqueue
				BFSQueue.push(DijkstraND(nextNodeData));
				pStage_->SetStepCount(nextNodeData.pos, nextNodeData.stepCount); // ループ中のstep数は同じにしたい
				pStage_->SetMazeState(nextNodeData.pos, Maze::MazeState::FOUND);
			}
		}

		if (currNodeData.pos == pStage_->IndexToPoint(pMaze_->GetGoal()))
		{
			// ここでフラグを下げる
			enabledSearch_ = false;
			EtchingDijkstra(currNodeData.stepCount, 0);
			currNodeData = DijkstraND(Point(0, 0), 0, 0);
			first = true;
			BFSQueue = std::priority_queue<DijkstraND>();
			return;
		}
	}
}

void Explorer::FindPathAStar()
{
}

void Explorer::EtchingBFSPath(int _stepCount)
{
	Point currPos{pStage_->IndexToPoint(pMaze_->GetGoal())};
	pStage_->SetMazeState(currPos, Maze::MazeState::ETCHING);

	while (true)
	{
		for (int i = 0; i < DIR::MAX_DIR; i++)
		{
			Point nextPos{currPos + NEXT_POSITION[i]};
			if (pStage_->GetStepCount(nextPos) == _stepCount - 1)
			{
				_stepCount--;
				currPos = nextPos;
				pStage_->SetMazeState(currPos, Maze::MazeState::ETCHING);
				break;
			}
		}

		if (_stepCount == 0)
		{
			break;
		}
	}

	for (int i = 0; i < pStage_->GetMazeSize(); i++)
	{
		if (pStage_->GetMazeState(pStage_->IndexToPoint(i)) == Maze::MazeState::FOUND)
		{
			pStage_->SetMazeState(pStage_->IndexToPoint(i), Maze::MazeState::WAY);
		}
	}
}

void Explorer::EtchingDijkstra(int _stepCount, int _cost)
{
	Point currPos{pStage_->IndexToPoint(pMaze_->GetGoal())};
	pStage_->SetMazeState(currPos, Maze::MazeState::ETCHING);

	while (true)
	{
		for (int i = 0; i < DIR::MAX_DIR; i++)
		{
			Point nextPos{currPos + NEXT_POSITION[i]};
			if (pStage_->GetStepCount(nextPos) + pStage_->GetMazePathCost(nextPos) < _stepCount + pStage_->GetStepCount(currPos))
			{
				_stepCount--;
				currPos = nextPos;
				pStage_->SetMazeState(currPos, Maze::MazeState::ETCHING);
				break;
			}
		}

		if (_stepCount == 0)
		{
			break;
		}
	}

	for (int i = 0; i < pStage_->GetMazeSize(); i++)
	{
		if (pStage_->GetMazeState(pStage_->IndexToPoint(i)) == Maze::MazeState::FOUND)
		{
			pStage_->SetMazeState(pStage_->IndexToPoint(i), Maze::MazeState::WAY);
		}
	}
}
