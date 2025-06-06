#include "Stage.h"
#include "../Library/Input.h"
#include "../ImGui/imgui.h"

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
	for (int y = 0; y < STAGE_HEIGHT; y++)
	{
		for (int x = 0; x < STAGE_WIDTH; x++)
		{
			if (y == 0 || y == STAGE_HEIGHT - 1 || x == 0 || x == STAGE_WIDTH - 1)
			{
				/*
				* �G�ƕǂ̓����蔻����s��
				* �ǂ̍��W��Enemy�����Ɉړ����悤�Ƃ��Ă�����W�������Ƃ������Ƃ́A���̒���if���ɓK������Ƃ������Ƃł���
				* �G�����Ɉړ�����n�_���ǂ̒��������ꍇ�AEnemy��IsNotWall(����͕ǂł͂Ȃ�)��false�i�ǂł���j�ɂ���
				*/

				Point NextEnemyPos = enemy->GetPosition() + NEXT_POSITION[enemy->GetDir()];

				if ((NextEnemyPos.x == x) || (NextEnemyPos.y == y))
				{
					enemy->IsNotWall(false);	// ����ŁAEnemy����not��p���Ȃ��Ă��悭�Ȃ�B
				}
				else
				{
					enemy->IsNotWall(true);
				}
			}
		}
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
			DrawLine(x + CHARA_SIZE, y * CHARA_SIZE, STAGE_WIDTH * CHARA_SIZE - CHARA_SIZE, y * CHARA_SIZE, 0xffffff); // ������
			DrawLine(x * CHARA_SIZE, y + CHARA_SIZE, x * CHARA_SIZE, STAGE_HEIGHT * CHARA_SIZE - CHARA_SIZE, 0xffffff); // �c����
		}
	}		

}
