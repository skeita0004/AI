#pragma once

#include "../Library/GameObject.h"
#include <vector>
#include "global.h"

class Stage;
class Maze;

class Explorer : public GameObject
{
public:
	Explorer(Point _position);
	~Explorer();

	void Update() override;
	void Draw() override;

	void FindPathDFS();
	void FindPathBFS();
	void FindPathDijkstra();
	void FindPathAStar();

	/// @brief BFSで探索した経路から、ゴールまでの道を可視化する
	void EtchingBFSPath(int _stepCount);

	void EtchingDijkstra();

	void SetPosition(Point _position)
	{
		position_ = _position;
	}
	Point GetPosition()
	{
		return position_;
	}
	DIR   GetDir()
	{
		return currDir_;
	}
	void  IsWall(bool _isWall)
	{
		isWall_ = _isWall;
	}

private:

	struct NodeData
	{
		NodeData(Point _pos, int _stepCount) :
			pos(_pos),
			stepCount(_stepCount)
		{}
		Point pos;
		int   stepCount;
	};

	struct DijkstraND
	{
		DijkstraND(Point _pos, int _cost) :
			pos(_pos),
			cost(_cost)
		{}

		Point pos;
		int cost;

		bool operator<(const DijkstraND& other) const
		{
			return cost > other.cost;
		}
	};

	int hImage_;
	Point position_;

	Stage* pStage_;
	Maze* pMaze_;

	DIR currDir_;
	DIR nextDir_;

	std::string dir_;

	float dirTimer_;
	float moveTimer_;

	int* anim;

	bool isWall_;
	bool enabledSearch_;

	std::vector<int> minCosts_;
	std::vector<Point> preNodes_;
};