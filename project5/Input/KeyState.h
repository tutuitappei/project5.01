#pragma once
#include <vector>
#include "InputState.h"

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();

	void Update(void) override;	
private:
	void RefKeyData(void);
	void SetKeyConfig(void);
	void (KeyState::*func)(void);

	char _buf[256];	//�S�L�[�f�[�^�i�[
	std::vector<int> _keyCon;		//����p�̃L�[���i�[
	std::vector<int> _keyConDef;	//����̑���L�[���i�[
	int modekeyOld;					//f11

	//void kmset(void);				//�L�[�ݒ���A�t�@�C���Ɋi�[
	//void kmload(void);				//�L�[�ݒ�����[�h


	INPUT_ID _confId;
	//int keys[static_cast<int>(INPUT_ID::MAX)];
};

