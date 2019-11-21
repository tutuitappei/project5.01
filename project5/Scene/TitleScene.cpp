#include "TitleScene.h"
#include "GameScene.h"
#include <DxLib.h>


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	/*if (CheckHitKey(KEY_INPUT_SPACE))*/
	{
		return std::make_unique<GameScene>();
	}
	return std::move(own);
}

