#include "Enemy.h"
#include <cassert>
#include "../ImGui/imgui.h"
#include "Player.h"
#include <DirectXMath.h>

// ファイルから読み込めるようにすること。
namespace
{
	const int ENEMY_SIZE = 32;
	const int ENEMY_DRAW_SIZE = 32;
	int timer = 0;
	const float DIR_CHANGE_TIME = 3.0f;
	const float MOVE_TIME = 0.2f;
	const float ANIM_INTERVAL_TIME = 0.5f;

	const float CHASE_TIME = 5.0f;
	const float ESCAPE_TIME = 2.0f;

	const int THRESHOLD_DIST = 5;

	static float animTimer_;
	static int animIndex_;

	const int VIEW_DIST = 5;
	const float VIEW_DEG = 45.f;
}

Enemy::Enemy(Point _position) :
	position_(_position),
	hImage_(-1),
	currDir_(DOWN),
	nextDir(UP),
	dirTimer_(0.f),
	moveTimer_(0.f),
	isWall_(true),
	state_(EState::NORMAL),
	chaseTimer_(0),
	escapeTimer_(0)
{
	hImage_ = LoadGraph("data/QueueCat_half.png");
	//assert(hImage_ > -1);
	Point randPosition = { GetRand(STAGE_WIDTH - 2) + 1, GetRand(STAGE_HEIGHT - 2) + 1 };
	currDir_ = DIR(rand() % MAX_DIR);
	position_ = { randPosition.x, randPosition.y};
	anim = new int[4] {0, 1, 2, 1}; // 3秒で向きが変わるため、アニメーションが回らない。
	animTimer_ = ANIM_INTERVAL_TIME;
	animIndex_ = 0;
	pPlayer_ = FindGameObject<Player>();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	//switch (state_)
	//{
	//case Enemy::EState::NORMAL:
	//	UpdateNormal();
	//	break;

	//case Enemy::EState::CHASE:
	//	UpdateChase();
	//	break;

	//case Enemy::EState::ESCAPE:
	//	UpdateEscape();
	//	break;

	//case Enemy::EState::MAX_ESTATE:
	//	break;
	//default:
	//	break;
	//}
}


void Enemy::UpdateNormal()
{
	Point pPos = pPlayer_->GetPosition();

	dirTimer_ += DeltaTime::GetDeltaTime();
	
	Move(MOVE_TIME);

	// plainBlock
	{
		//Point pos = position_;
		//int dist = (std::abs(pPos.x - pos.x) + std::abs(pPos.y - pos.y));

		if (IsFindPlayer(pPlayer_))
		{
			state_ = EState::CHASE;
			printfDx("千円チャーシュー！");
		}

	}
}

void Enemy::UpdateChase()
{
	float dt = DeltaTime::GetDeltaTime();

	Point pPos = pPlayer_->GetPosition();
	Point pos = position_;

	if (chaseTimer_ > CHASE_TIME)
	{
		chaseTimer_ = 0;
		state_ = EState::NORMAL;
		printfDx("State = NORMAL");
	}
	else if (pPos.x  == 18 && pPos.y == 10)
	{
		state_ = EState::ESCAPE;
	}
	else
	{
		int xDist = std::abs(pPos.x - pos.x);
		int yDist = std::abs(pPos.y - pos.y);

		if (xDist > yDist)
		{
			if (pPos.x > pos.x)
			{
				currDir_ = RIGHT;
			}
			else
			{
				currDir_ = LEFT;
			}
		}
		else if (xDist < yDist)
		{
			if (pPos.y > pos.y)
			{
				currDir_ = DOWN;
			}
			else
			{
				currDir_ = UP;
			}
		}

		Move(0.1f);
	}
	chaseTimer_ += dt;
}

void Enemy::UpdateEscape()
{
	float dt = DeltaTime::GetDeltaTime();

	Point pPos = pPlayer_->GetPosition();
	Point pos = position_;

	if (chaseTimer_ > CHASE_TIME)
	{
		chaseTimer_ = 0;
		state_ = EState::NORMAL;
		printfDx("State = NORMAL");
	}
	else
	{
		int xDist = std::abs(pPos.x - pos.x);
		int yDist = std::abs(pPos.y - pos.y);

		if (xDist > yDist)
		{
			if (pPos.x > pos.x)
			{
				currDir_ = LEFT;
			}
			else
			{
				currDir_ = RIGHT;
			}
		}
		else if (xDist < yDist)
		{
			if (pPos.y > pos.y)
			{
				currDir_ = UP;
			}
			else
			{
				currDir_ = DOWN;
			}
		}

		Move(MOVE_TIME);
	}
	chaseTimer_ += dt;
}

void Enemy::Draw()
{
	//int animIndex = int(animTimer_) % 4;
	Rect<int> imageRect[MAX_DIR] = // 変換用配列
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

	Rect<int> visibility{};
	visibility.x = position_.x;
	visibility.y = position_.y;
	visibility.w = 1;
	visibility.h = 1;

	switch (currDir_)
	{
	case UP:
		visibility.h = -5;
		break;
	case DOWN:
		visibility.h = 6;
		break;
	case LEFT:
		visibility.w = -5;
		break;
	case RIGHT:
		visibility.w = 6;
		break;

	default:
		break;
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	{
		for (int i = 0; i < VIEW_DIST; i++)
		{
			Point view{ position_.x + (i + 1) * NEXT_POSITION[currDir_].x,
					   position_.y + (i + 1) * NEXT_POSITION[currDir_].y};

			DrawBox(view.x * ENEMY_DRAW_SIZE, view.y * ENEMY_DRAW_SIZE,
				view.x * ENEMY_DRAW_SIZE + ENEMY_DRAW_SIZE, view.y * ENEMY_DRAW_SIZE + ENEMY_DRAW_SIZE,
				0xff0000, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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

void Enemy::Move(float _moveInterval)
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
		TurnLeft();
	}
	else
	{
		switch (currDir_)
		{
		case UP:
			dir = "UP";
			position_.y -= moveIncrease;
			break;
		case DOWN:
			dir = "DOWN";
			position_.y += moveIncrease;
			break;
		case LEFT:
			dir = "LEFT";
			position_.x -= moveIncrease;
			break;
		case RIGHT:
			dir = "RIGHT";
			position_.x += moveIncrease;
			break;
		default:
			break;
		}
	}
	moveIncrease = 0;
}

bool Enemy::IsFindPlayer(Player *_pPlayer)
{
	Point playerPos = _pPlayer->GetPosition();
	
	for (int i = 0; i < VIEW_DIST; i++)
	{
		Point view{ position_.x + (i + 1) * NEXT_POSITION[currDir_].x,
				   position_.y + (i + 1) * NEXT_POSITION[currDir_].y };
		
		if (playerPos.x == view.x && playerPos.y == view.y)
		{
			return true;
		}
	}

	return false;
}

std::vector<Point> Enemy::GetVisibility(float _deg, float _dist)
{
	std::vector<Point> visibilities;

	float rad = DirectX::XMConvertToRadians(_deg);

	cosf(rad);

	for (int visY = -_dist; visY <= _dist; visY++)
	{
		for (int visX = -_dist; visX <= _dist; visX++)
		{
			if (visY == 0 && visX == 0)
			{
				continue;
			}

			if ((visX * visX + visY * visY) > _dist * _dist) // ??????????
			{
				continue;
			}

			Point face = NEXT_POSITION[currDir_];
			DirectX::XMVECTOR faceVec = DirectX::XMVectorSet(face.x, face.y, 0.f, 0.f);
			DirectX::XMVECTOR dirVec = DirectX::XMVectorSet(visX, visY, 0.f, 0.f);
			faceVec = DirectX::XMVector2Normalize(faceVec);
			dirVec = DirectX::XMVector2Normalize(dirVec);
			DirectX::XMVector2Dot(faceVec, dirVec);
		}
	}

	return visibilities;
}
