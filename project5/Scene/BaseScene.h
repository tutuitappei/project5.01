#pragma once
#include <memory>

class BaseScene;	//�N���X���A�錾����B

using unique_Base = std::unique_ptr<BaseScene>;		//unique_Base�ƁA���ƁAstd::uni�`�`�ɁA�Ԋ҂���Ďg����
	
class BaseScene
{
public:
	
	BaseScene();	//�R���X�g���N�g

	virtual unique_Base Update(unique_Base own) = 0;	//�V�[�����A�X�V����B

	virtual ~BaseScene();	//�f�R���X�g���N�g���A���z������
};

