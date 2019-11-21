#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>


class Player :
	public Obj
{
public:
	Player();
	Player(Vector2db pos, Vector2db size);	//座標：サイズ
	void Updata(void);					//更新処理
	~Player();
	std::shared_ptr<InputState> _input;
private:
	void Init(void);					//初期化
};

