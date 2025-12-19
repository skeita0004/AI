#include "Maze.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include "DxLib.h"

Maze::Maze(int _width, int _height) :
	width_(_width),
	height_(_height),
	length_(width_ * height_)
{
	maze_ = std::vector<MazeState>(length_, MazeState::WALL);

	// 相互mapの初期化
	mazeLUT_.insert({'W', MazeState::WALL});
	mazeLUT_.insert({'O', MazeState::OUTER_WALL});
	mazeLUT_.insert({' ', MazeState::WAY});
	mazeLUT_.insert({'S', MazeState::START});
	mazeLUT_.insert({'G', MazeState::GOAL});
}

Maze::~Maze()
{
}

std::vector<Maze::MazeState> Maze::Generate()
{
	std::stack<int> intersection{};
	std::mt19937 engine(std::random_device{}());

	SetOuterWall();

	int currPos = SetRandomFirstPos(intersection, engine);

	// 通路を伸ばしていく。
	std::vector<int> dir
	{
		-width_ * 2,
		 width_ * 2,
		-2        ,
		 2
	};
	std::uniform_int_distribution<int> randDirIndex(0, dir.size() - 1);

	while (true)
	{
		// 掘る地点を決め、それが有効かを確認する処理
		// 先にforで4つまわしちゃって、有効な方向を配列に格納する
		// 有効の方向からランダムに選ぶ
		// 4つがだめなら、stackのtopをし、currPosにその値を代入
		// intersection.size()が0になったら終わり;

		int nextDir{};
		int nextPos{};
		// 有効な方向の探索
		std::vector<int> canDugDir{};
		for (int i = 0; i < 4; i++)
		{
			// currPosにdirを足したときに、道か配列の外か、外周でなければその方向は問題ない。
			nextPos = currPos + dir[i];

			bool canDug{
				0 < nextPos and nextPos < length_           // 配列の範囲内
				and maze_[nextPos] not_eq MazeState::WAY        // 道じゃない
				and maze_[nextPos] not_eq MazeState::OUTER_WALL // 外壁じゃない
			};

			if (canDug)
			{
				// 有効な方向を格納する配列に入れる
				canDugDir.push_back(dir[i]);
			}
		}

		// いける方向がなければ、currPosを戻し、やり直し
		if (canDugDir.empty())
		{
			if (intersection.empty())
			{
				break;
			}
			if (not(intersection.empty()))
			{
				currPos = intersection.top();
				intersection.pop();
			}
			continue;
		}
		// 上で求めた配列のサイズが2以上なら、ランダムに選ぶ
		else if (canDugDir.size() >= 2)
		{
			// ランダムな奴選ぶ
			std::uniform_int_distribution<int> randDirIndex(0, static_cast<int>(canDugDir.size()) - 1);
			int index = randDirIndex(engine);
			nextDir = canDugDir[index];
		}
		else
		{
			// ここに来るということは、いける方向は一つしかないということなので、
			// 配列の頭をnextPosにする
			nextDir = canDugDir[0];
		}

		// forを用いて掘る
		for (int i = 2; i > 0; i--)
		{
			// WAYを設定していく
			// currPos + 2か、-2,
			int index = currPos + (nextDir / i);
			maze_[index] = MazeState::WAY;
		}

		// そして、現在の位置を更新し、
		// スタックにプッシュ
		currPos = currPos + nextDir;
		intersection.push(currPos);
	}

	maze_[1 + width_] = MazeState::START;
	maze_[((length_ - 1) - 1) - width_] = MazeState::GOAL;

	return maze_;
}

void Maze::Save()
{
	// 準備
	TCHAR       filePath[255]{};
	OPENFILENAMEA openFile
	{
		.lStructSize{sizeof(openFile)},
		.hwndOwner{GetMainWindowHandle()},
		.lpstrFilter{"mmzファイル (*.mmz)\0*.mmz\0"},
		.lpstrFile{filePath},
		.nMaxFile{255},
		.Flags{OFN_OVERWRITEPROMPT}
	};

	// ダイアログウィンドウ表示
	if (not(GetSaveFileName(&openFile)))
	{
		MessageBox(nullptr, "キャンセルされました", "情報", MB_OK);
	}

	// ファイル書き込み
	std::ofstream file(filePath);
	file << width_ << "," << height_ << "\n";

	for (int i = 0; i < maze_.size(); i++)
	{
		// キーのエラーチェックしないと駄目だよ！
		file << mazeLUT_.right.at(maze_[i]);

		if (i % width_ + 1 == width_)
		{
			file << "\n";
		}
	}

	file.close();

	MessageBox(nullptr, "Saved!", "Information", MB_OK);
}

std::vector<Maze::MazeState>& Maze::Load()
{
	// 準備
	TCHAR       filePath[255]{};
	OPENFILENAMEA openFile
	{
		.lStructSize{sizeof(openFile)},
		.hwndOwner{GetMainWindowHandle()},
		.lpstrFilter{"mmzファイル (*.mmz)\0*.mmz\0"},
		.lpstrFile{filePath},
		.nMaxFile{255},
		.Flags{OFN_OVERWRITEPROMPT}
	};

	// ダイアログウィンドウ表示
	if (not(GetOpenFileName(&openFile)))
	{
		MessageBox(nullptr, "キャンセルされました", "情報", MB_OK);
	}

	if (not(std::filesystem::exists(filePath)))
	{
		MessageBox(nullptr, "File is not exists.", "ERROR!", MB_OK);
	}

	std::string line{};
	std::ifstream file(filePath);
	
	// ヘッダ読み込み
	int cammaPos = 0;
	std::getline(file, line);
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ',')
		{
			cammaPos = i;
		}
	}
	width_  = std::stoi(line.substr(0, cammaPos));
	height_ = std::stoi(line.substr(cammaPos + 1));

	// 迷路データ読み込み
	maze_.clear();
	int lineCount = 0;
	while (std::getline(file, line))
	{
		for (int i = 0; i < line.size(); i++)
		{
			// keyのエラーチェックしなさい。
			maze_.push_back(mazeLUT_.left.at(line[i]));
		}
		lineCount++;
	}

	return maze_;
}

int Maze::GetStart()
{
	return 1 + width_;
}

int Maze::GetGoal()
{
	return ((length_ - 1) - 1) - width_;
}

void Maze::SetOuterWall()
{
	/* 外周部分に破壊できない壁を設定する */
	for (int i = 0; i < length_; i++)
	{
		int x = i % width_;
		int y = i / width_;

		if (x == 0 || x == width_ - 1 || y == 0 || y == height_ - 1)
		{
			maze_[i] = MazeState::OUTER_WALL;
		}
	}
}

int Maze::SetRandomFirstPos(std::stack<int>& _intersection,
							std::mt19937&    _engine)
{
	/* ランダムな一点を選ぶ */
	std::uniform_int_distribution<int> randMazeIndex(0, length_ - 1);

	int initPos = randMazeIndex(_engine);

	// initPosが外周の壁ではなく、さらに、xyが両方とも偶数であれば抜ける
	while (true)
	{
		int x = initPos % width_;
		int y = initPos / width_;

		if (maze_[initPos] != MazeState::OUTER_WALL and
			x % 2 != 0 and y % 2 != 0)
		{
			break;
		}
		initPos = randMazeIndex(_engine);
	}
	maze_[initPos] = MazeState::WAY;
	_intersection.push(initPos);

	return initPos;
}