#pragma once

#include "../Library/GameObject.h"
#include <vector>
#include "global.h"

class Explorer : public GameObject
{
public:
	Explorer(Point _position);
	~Explorer();

	void Update() override;
	void Draw() override;

	void TurnLeft();
	void TurnRight();
	void TurnBack();

	void Move(float _moveInterval);

	void FindPathDFS();
	void FindPathBFS();
	void FindPathDijkstra();
	void FindPathAStar();

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

	int hImage_;
	Point position_;

	DIR currDir_;
	DIR nextDir_;

	std::string dir_;

	float dirTimer_;
	float moveTimer_;

	int* anim;

	bool isWall_;
};