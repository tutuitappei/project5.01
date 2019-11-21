#pragma once
#include "Obj.h"
#include <memory>
#include <InputState.h>


class Player :
	public Obj
{
public:
	Player();
	Player(Vector2db pos, Vector2db size);	//���W�F�T�C�Y
	void Updata(void);					//�X�V����
	~Player();
	std::shared_ptr<InputState> _input;
private:
	void Init(void);					//������
};

