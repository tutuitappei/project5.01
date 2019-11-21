#pragma once
#include <vector>
#include "BaseScene.h"
#include "Obj.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();

	

	unique_Base Update(unique_Base own) override;			//シーンを、更新する。
	
	~GameScene();

private:
	std::vector<shardObj> _objList;
};

