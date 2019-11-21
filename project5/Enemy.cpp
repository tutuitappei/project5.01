#include <ImageMng.h>
#include "Enemy.h"



Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(EnemyState& state)
{ 
	
	_Type = std::get<static_cast<int> (ENEMY_STATE::TYPE)>(state);
	_Pos = std::move(std::get<static_cast<int> (ENEMY_STATE::VECTOR)>(state));
	_Size = std::move(std::get<static_cast<int> (ENEMY_STATE::SIZE)>(state));
	_moveCtl.SetMoveState(std::get<static_cast<int> (ENEMY_STATE::AIM)>(state),true);
	Init();
}

void Enemy::Updata(void)
{


	if (DestroyProck())
	{
		return;
	}

	_moveCtl.Updata();
	
	//if (rand() % 300 == 0)
	//{
	//	SetAlive(false);
	//}

}


Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	AnimVector data;
	data.emplace_back(IMAGE_ID("·¬×")[10+(2*static_cast<int>(_Type))], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1 + 10 +(2*static_cast<int>(_Type))], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("“G”š")[0], 10);
	data.emplace_back(IMAGE_ID("“G”š")[1], 15);
	data.emplace_back(IMAGE_ID("“G”š")[2], 20);
	data.emplace_back(IMAGE_ID("“G”š")[3], 25);
	data.emplace_back(IMAGE_ID("“G”š")[4], 35);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	State(STATE::NORMAL);
}
