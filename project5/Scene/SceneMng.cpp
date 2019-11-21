#include <DxLib.h>
#include <SceneMng.h>
#include <TitleScene.h>
#include <GameScene.h>

SceneMng* SceneMng :: sInstance = nullptr;		//���I�p
//SceneMng SceneMng::sInstance;					//�ÓI�p

SceneMng::SceneMng() : ScreenSize{ 800,600 }
{
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	//�����ɂ��܂��Ă���Que��`�悷��
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

	//for (std::vector<DrawQueT>::iterator dListite = _drawList.begin();dListite != _drawList.end(); dListite++)		//�C�e���[�^�[
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
		//������ID ���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}
	//Que��ǉ�
	_drawList.emplace_back(dQue);

	return true;
}

void SceneMng::Run(void)
{
	SysInit();			//�V�X�e���̏�����
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
	//���я���
	SetWindowText("05");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				//��ڲ��ʂ�600*320�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										//���windowӰ��
	if (DxLib_Init() == -1)										//DXײ���؂̏���������
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);								//�`�����ޯ��ޯ̧�ɐݒ�

	return false;
}

