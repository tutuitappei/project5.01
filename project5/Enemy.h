#pragma once
#include "Obj.h"
#include <EnemyMove.h>


enum class ENEMY_TYPE
{
	A,
	B,
	C,
	MAX
};

enum class ENEMY_STATE
{
	TYPE,
	VECTOR,
	SIZE,
	AIM,
	MAX
};
//const std::string
using EnemyState = std::tuple< ENEMY_TYPE, Vector2db, Vector2db,MoveState&>;	//	TYPE,VECTOR,SIZE,AIM

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);
	void Updata(void);
	~Enemy();
private:
	EnemyMove _moveCtl{_Pos};

	void Init(void);

	ENEMY_TYPE _Type;
};

