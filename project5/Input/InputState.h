#pragma once
#include <map>
#include <InputID.h>


using KeyPir = std::pair<int, int>;		//�L�[NEW��OLD
using KeyMap = std::map<INPUT_ID, KeyPir>;		//���,�oNEW�AOLD�p

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void Update(void)=0;

	const KeyMap& state(void)const;		//�L�[�}�b�v���ۂ��ƕԂ��B
	const KeyPir& state(INPUT_ID id)const;	//ID�ɑΉ�������̂�Ԃ�
	bool state(INPUT_ID id,int kf);		//�L�[�f�[�^���Z�b�g
	void SetOld(void);
private:
	KeyMap _state;						//�L�[�f�[�^�������B


};

