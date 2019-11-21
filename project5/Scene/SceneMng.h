#pragma once
#include <memory>
#include <tuple>
#include <vector>
#include <Common\Vector2.h>
#include "BaseScene.h"

using 	DrawQueT = std::tuple<int, double, double, double>;	//�^�v�����g���āA3��INT���g���B
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
	static SceneMng &GetInstance(void)	//���̂��A�Ăяo���H����
	{
		Create();						//���I�ɍ��Ƃ��Ɏg��
		return *sInstance;
	}
	static void Create()			//���I�ɁA���̂���邽�߂̏���
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
			delete sInstance;	//�폜����	
		}
		sInstance = nullptr;	//�A�h���X���A���݂Ƃ��Ďc���Ă���̂ł��ꂢ�ɂ���
	}

	bool AddDrawQue(DrawQueT dQue);
	
	void Run(void);					//���s����
	const Vector2in ScreenSize;		//�X�N���[���T�C�Y
private:
	static SceneMng* sInstance;		//���I�ɍ�邽�߂ɁA�|�C���^�[�ŁA���̂�������̂����
	//static SceneMng sInstance;		//�ÓI�ɍ�邽�߂ɁA���̂�������̂����B
	//BaseScene* _activeScene;	//���A�N�e�B�u�ɂȂ��Ă�V�[���������B
	unique_Base _activeScene;	//<BaseScene>���A�g���Ă���̂����Ȃ��Ȃ����������B

	void Draw(void);

	std::vector<DrawQueT> _drawList;	//�т傤�����������̂����܂��Ă����Ƃ���B


	~SceneMng();
	SceneMng();
	bool SysInit(void);
};

