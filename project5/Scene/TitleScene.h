#pragma once
#include "BaseScene.h"

class TitleScene :
	public BaseScene
{
public:
	TitleScene();

	unique_Base Update(unique_Base own) override;			//�V�[�����A�X�V����B

	~TitleScene();
};

