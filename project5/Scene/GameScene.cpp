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


	TRACE("�ްѼ�݂̐���\n");

	lpImageMng.GetId("���", "image/char.png", { 30,32 }, { 10,10 });
	lpImageMng.GetId("�e", "image/Shot.png", {8,3 }, { 1,2 });
	lpImageMng.GetId("�G��", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetId("����", "image/pl_blast.png", { 64,64 }, { 4,1 });

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
					_objList.begin(),	//�`�F�b�N�����ꂩ��n�߂� �`�F�b�N�͈͑O
					_objList.end(),	//�`�F�b�N������ŏI���	�`�F�b�N�͈͌�
					[](shardObj&obj) {return (*obj).isDead(); })
					, _objList.end()
		);

	return std::move(own);
}

