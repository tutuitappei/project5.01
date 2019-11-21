#include <DxLib.h>
#include "Player.h"
#include <ImageMng.h>
#include "KeyState.h"
#include <InputID.h>
#include <_debug/_DubugConOut.h>


Player::Player()
{
	Init();

}

Player::Player(Vector2db pos, Vector2db size)
{
	_Pos = pos;
	_Size = size;

	Init();
}

void Player::Updata(void)
{
	if (DestroyProck())
	{
		return;
	}

	(*_input).Update();

	auto move = [](std::weak_ptr<InputState> KeyID,const INPUT_ID id,double& pNum , double speed) {
		
		if (!KeyID.expired())
		{
			
			if ((*KeyID.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
		
	};

	//move(_input,INPUT_ID::UP, _Pos.y, -2);
	//move(_input, INPUT_ID::DOWN, _Pos.y, 2);
	move(_input, INPUT_ID::RIGHT, _Pos.x, 2.0);
	move(_input, INPUT_ID::LEFT, _Pos.x, -2.0);

}


Player::~Player()
{
}

void Player::Init(void)
{
	AnimVector data;
	data.emplace_back(IMAGE_ID("∑¨◊")[0], 30);
	data.emplace_back(IMAGE_ID("∑¨◊")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("∑¨◊")[2], 60);
	SetAnim(STATE::EX, data);

	data.emplace_back(IMAGE_ID("é©îö")[0], 20);
	data.emplace_back(IMAGE_ID("é©îö")[1], 25);
	data.emplace_back(IMAGE_ID("é©îö")[2], 30);
	data.emplace_back(IMAGE_ID("é©îö")[3], 35);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	//í èÌ
	_input = std::make_shared<KeyState>();
	//å√Ç¢Ç‚ÇËï˚
	//_input.reset(new KeyState());

	State(STATE::NORMAL);
}
