#include "Stage.h"
#include "../Library/Input.h"
#include "../ImGui/imgui.h"

Stage::Stage() :
	mousePosition_()
{
	player = new Player({ 3, 3 });
	enemy = new Enemy({1 , 1 });
}

Stage::~Stage()
{
}

void Stage::Update()
{
	Point NextEnemyPos = enemy->GetPosition() + NEXT_POSITION[enemy->GetDir()];

	int x = NextEnemyPos.x;
	int y = NextEnemyPos.y;

	if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
	{
		enemy->IsWall(true);	// ‚±‚ê‚ÅAEnemy‘¤‚Ånot‚ð—p‚¢‚È‚­‚Ä‚à‚æ‚­‚È‚éB
	}
	else
	{
		enemy->IsWall(false);
	}
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
			}
		}
	}

	for (int y = 1; y < STAGE_HEIGHT; y++)
	{
		for (int x = 1; x < STAGE_WIDTH; x++)
		{
			DrawLine(x + CHARA_SIZE, y * CHARA_SIZE, STAGE_WIDTH * CHARA_SIZE - CHARA_SIZE, y * CHARA_SIZE, 0xffffff); // ‰¡•ûŒü
			DrawLine(x * CHARA_SIZE, y + CHARA_SIZE, x * CHARA_SIZE, STAGE_HEIGHT * CHARA_SIZE - CHARA_SIZE, 0xffffff); // c•ûŒü
		}
	}		


	int x = 18 * CHARA_SIZE;
	int y = 10 * CHARA_SIZE;
	DrawBox(x, y, x + CHARA_SIZE, y + CHARA_SIZE, 0xffff00, TRUE);
}
