#pragma once

#include "Vector2D.hpp"
#include <vector>
#include <stack>
#include <random>
#include <boost/bimap/bimap.hpp>

class Maze
{
public:
	enum class MazeState : int
	{
		WALL,
		OUTER_WALL,
		WAY,
		START,
		GOAL,
		FOUND,
		MAX_STATE
	};

public:
	Maze(int _width, int _height);
	~Maze();
	
	/// @brief 穴掘り法により、迷路を生成する。
	std::vector<MazeState> Generate();
	
	void Save();
	std::vector<MazeState>& Load();

	int GetStart();
	int GetGoal();

private:
	enum class Dir : int
	{
		UP,
		DOWN,
		LEFT,
		LIGHT
	};

	int width_;
	int height_;
	int length_;

	std::vector<MazeState> maze_;
	
	typedef boost::bimaps::bimap<char, MazeState> bimap;
	bimap mazeLUT_;

	/// @brief 迷路の外周部分に、破壊できない壁を設定
	void SetOuterWall();

	/// @brief  迷路を掘り始める始点を、ランダムに設定
	/// @return 始点
	int  SetRandomFirstPos(std::stack<int>& _intersection, std::mt19937& _engine);
};
