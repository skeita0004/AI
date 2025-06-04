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
					enemy->IsNotWall(false);	// ����ŁAEnemy����not��p���Ȃ��Ă��悭�Ȃ�B
				 }
				 else
				 {
					 enemy->IsNotWall(true);
				 }
				

				/* 
				* �G�ƕǂ̓����蔻����s��
				* �ǂ̍��W��Enemy�̍��W�������Ƃ������Ƃ́A���̒���if���ɓK������Ƃ������Ƃł���
				* �G�����Ɉړ�����n�_���ǂ̒��������ꍇ�AEnemy��IsWall��true�ɂ���
				* 
				*/
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
