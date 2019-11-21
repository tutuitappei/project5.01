#include <algorithm>
#include <time.h>

#include <DxLib.h>

#include <GameScene.h>
#include <_DubugConOut.h>
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h> 


GameScene::GameScene()
{
	srand(unsigned int(time));


	TRACE("ｹﾞｰﾑｼｰﾝの生成\n");

	lpImageMng.GetId("ｷｬﾗ", "image/char.png", { 30,32 }, { 10,10 });
	lpImageMng.GetId("弾", "image/Shot.png", {8,3 }, { 1,2 });
	lpImageMng.GetId("敵爆", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetId("自爆", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 400.0,578.0 }, { 0.0,0.0 })
	);


	for (double y = 0; y < 5; y++)
	{

		for (double x = 0; x < 5; x++)
		{
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(MOVE_TYPE::WAIT, Vector2db{180.0,0.0});
			tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2db{ 400.0,400.0 });

			EnemyState state={
				(ENEMY_TYPE)(/*y%3*/0),
			{ x*50.0+300.0,y*50.0+50.0 },
			{ 0.0,0.0 },
			tmpMoveState};

			_objList.emplace_back(
				new Enemy(state)
			);
		}
	}



	//EnemyState data{ ENEMY_TYPE::A,{ 400,500 },{ 0,0 } };
	//obj[0] = new Enemy(data);
	////obj[0]->State(STATE::NORMAL);
	////obj0] = new Obj("image/char.png", {0, 0},10,10, 30,32);
	////obj[1] = new Obj("image/char.png", { 0, 0 }, 10, 10, 30, 32);
}


GameScene::~GameScene()
{
	
}

unique_Base GameScene::Update(unique_Base own)
{

	for (auto data : _objList)
	{
		(*data).Updata();
	}

	for (auto data : _objList)
	{
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			//(*data).SetAlive(false);
		};

		(*data).Draw();
	}

	_objList.erase(std::remove_if(
					_objList.begin(),	//チェックをこれから始める チェック範囲前
					_objList.end(),	//チェックをこれで終わる	チェック範囲後
					[](shardObj&obj) {return (*obj).isDead(); })
					, _objList.end()
		);

	return std::move(own);
}

