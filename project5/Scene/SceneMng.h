#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Common\Vector2.h>
#include "BaseScene.h"

using 	DrawQueT = std::tuple<int, double, double, double>;	//タプルを使って、3つのINTを使う。
#define lpSceneMng SceneMng::GetInstance()

enum class DRAW_QUE	
{
	IMAGE,
	X,
	Y,
	RAD
};

class SceneMng
{
public:
	static SceneMng &GetInstance(void)	//実体を、呼び出す？処理
	{
		Create();						//動的に作るときに使う
		return *sInstance;
	}
	static void Create()			//動的に、実体を作るための処理
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;	//削除する	
		}
		sInstance = nullptr;	//アドレスが、ごみとして残っているのできれいにする
	}

	bool AddDrawQue(DrawQueT dQue);
	
	void Run(void);					//実行処理
	const Vector2in ScreenSize;		//スクリーンサイズ
private:
	static SceneMng* sInstance;		//動的に作るために、ポインターで、実体が入るものを作る
	//static SceneMng sInstance;		//静的に作るために、実体が入るものを作る。
	//BaseScene* _activeScene;	//今アクティブになってるシーンを示す。
	unique_Base _activeScene;	//<BaseScene>を、使っているのがいなくなったら消える。

	void Draw(void);

	std::vector<DrawQueT> _drawList;	//びょうがしたいものがたまっていくところ。


	~SceneMng();
	SceneMng();
	bool SysInit(void);
};

