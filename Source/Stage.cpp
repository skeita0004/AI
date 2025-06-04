#include "Stage.h"
#include "../Library/Input.h"

Stage::Stage() :
	mousePosition_()
{
	enemy = new Enemy({1 , 1 });
	player = new Player({ 64, 64 });
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	SetBackgroundColor(10, 52, 199);
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
			{
				DrawBox(CHARA_SIZE * x, CHARA_SIZE * y,
					CHARA_SIZE * x + CHARA_SIZE, CHARA_SIZE * y + CHARA_SIZE,
					0x662211, TRUE);
				
				 int NextEnemyX = enemy->GetPosition().x + NEXT_POSITION[enemy->GetDir()].x;
				 int NextEnemyY = enemy->GetPosition().y + NEXT_POSITION[enemy->GetDir()].y;
				 
				 if (NextEnemyX == x || NextEnemyY == y)
				 {
					enemy->IsNotWall(false);	// これで、Enemy側でnotを用いなくてもよくなる。
				 }
				 else
				 {
					 enemy->IsNotWall(true);
				 }
				

				/* 
				* 敵と壁の当たり判定を行う
				* 壁の座標とEnemyの座標が同じということは、この中のif文に適合するということである
				* 敵が次に移動する地点が壁の中だった場合、EnemyのIsWallをtrueにする
				* 
				*/
			}
		}
	}
	for (int y = 1; y < STAGE_HEIGHT; y++)
	{
		for (int x = 1; x < STAGE_WIDTH; x++)
		{
			DrawLine(x + CHARA_SIZE, y * CHARA_SIZE, STAGE_WIDTH * CHARA_SIZE - CHARA_SIZE, y * CHARA_SIZE, 0xffffff); // 横方向
			DrawLine(x * CHARA_SIZE, y + CHARA_SIZE, x * CHARA_SIZE, STAGE_HEIGHT * CHARA_SIZE - CHARA_SIZE, 0xffffff); // 縦方向
		}
	}		
}
