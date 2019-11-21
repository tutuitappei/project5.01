#include <DxLib.h>
#include <SceneMng.h>
#include <TitleScene.h>
#include <GameScene.h>

SceneMng* SceneMng :: sInstance = nullptr;		//動的用
//SceneMng SceneMng::sInstance;					//静的用

SceneMng::SceneMng() : ScreenSize{ 800,600 }
{
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	//ｽﾀｯｸにたまっているQueを描画する
	for (auto dQue : _drawList)
	{
		DrawRotaGraph(
			static_cast<int>(std::get<static_cast<int> (DRAW_QUE::X)>(dQue)),
			static_cast<int>(std::get<static_cast<int> (DRAW_QUE::Y)>(dQue)),
			1.0,
			std::get<static_cast<int> (DRAW_QUE::RAD)>(dQue),
			std::get<static_cast<int> (DRAW_QUE::IMAGE)>(dQue),
			true
		);
	}

	//for (int a = 0; a < _drawList.size();a++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int> (DRAW_QUE::X)>(_drawList[a]),
	//		std::get<static_cast<int> (DRAW_QUE::Y)>(_drawList[a]),
	//		std::get<static_cast<int> (DRAW_QUE::IMAGE)>(_drawList[a]),
	//		true
	//	);
	//}
	//

	//for (std::vector<DrawQueT>::iterator dListite = _drawList.begin();dListite != _drawList.end(); dListite++)		//イテレーター
	//{
	//	DrawGraph(
	//		std::get<static_cast<int> (DRAW_QUE::X)>(*(dListite)),
	//		std::get<static_cast<int> (DRAW_QUE::Y)>(*(dListite)),
	//		std::get<static_cast<int> (DRAW_QUE::IMAGE)>(*(dListite)),
	//		true
	//	);
	//}

	ScreenFlip();

}

SceneMng::~SceneMng()
{
}

bool SceneMng::AddDrawQue(DrawQueT dQue)	//dQue=IMAGE,X,Y
{
	
	if (!std::get<static_cast<int> (DRAW_QUE::IMAGE)>(dQue))
	{
		//がぞうID が不正なので、追加しない
		return false;
	}
	//Queを追加
	_drawList.emplace_back(dQue);

	return true;
}

void SceneMng::Run(void)
{
	SysInit();			//システムの初期化
	_activeScene = std::make_unique<TitleScene>();
	while (ProcessMessage()==0&&CheckHitKey(KEY_INPUT_ESCAPE)==0)
	{
		_drawList.clear();
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();
	}

}

bool SceneMng::SysInit(void)
{
	//ｼｽﾃﾑ処理
	SetWindowText("05");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				//ﾌﾟﾚｲ画面を600*320ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);										//画面windowﾓｰﾄﾞ
	if (DxLib_Init() == -1)										//DXﾗｲﾌﾞﾗﾘの初期化処理
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);								//描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定

	return false;
}

