#pragma once
#include <vector>
#include "BaseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();

	

	unique_Base Update(unique_Base own) override;			//�V�[�����A�X�V����B
	
	~GameScene();

private:
	std::vector<shardObj> _objList;
};

