#include <algorithm>

#include <DxLib.h>

#include "KeyState.h"
#include <InputID.h>
#include <_debug\_DubugConOut.h>

//# fopen

//�R���X�g���N�^�[�ŁAdata�t�H���_�[��key.dat���J���Bfopen_s();
//�J�����ꍇ�̓A�h���X���A�J���Ȃ������ꍇNULL���Ԃ��Ă���B
//�J�����ꍇ�F�A�h���X�[��freed()->_keycon
//�J���Ȃ������ꍇ::nullptr->_keyCon��_keyConDef���R�s�[

//void KeyState::kmset(void) 
//{
//	FILE* fileptr=0;
//
//	fopen_s(&fileptr, "data/key.dat", "wb");
//
//
//	fwrite(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
//	fclose(fileptr);
//
//}
//
//void KeyState::kmload(void) 
//{
//	FILE* fileptr=0;
//	fopen_s(&fileptr, "data/key.dat", "r");
//	if (fileptr != NULL)
//	{
//		fread(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
//		fclose(fileptr);
//	}
//
//}

KeyState::KeyState()
{
	//������
	for (int i = 0; i < sizeof(_buf); i++)
	{
		_buf[0]={ 0 };
	}
	_confId = INPUT_ID::LEFT;

	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));	//�����₷���тɃ�������蒼���̂͌�������A��Ƀ�������\�񂵂āA��蒼����h���B
	//DEFAULT��ݒ�
	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);



	FILE *fileptr =0;
	fopen_s(&fileptr, "data/key.dat","rb");
	//�L�[�ݒ�
	if (fileptr == NULL)
	{		//�����A����ł����DEFAULT�ɂ��āA�t�@�C�������B
		_keyCon = _keyConDef;

		fopen_s(&fileptr, "data/key.dat", "wb");

		if (fileptr != NULL)
		{
			fwrite(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
			fclose(fileptr);
		}

	}
	else
	{	//���g������̂ł���΁A�ǂݍ���
		_keyCon.resize(static_cast<int>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
		fclose(fileptr);
	}


	func = &KeyState::RefKeyData;

	modekeyOld = true;
}


KeyState::~KeyState()
{
	
}

void KeyState::Update(void)
{
	SetOld();
	modekeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);
	if (func != nullptr)
	{
		(this->*func)();
	}

}

void KeyState::RefKeyData(void)
{
	//��ɓ����Ă�̂����C���v�b�gID�̃L�[���̏����X�e�[�g�̃Z�b�g��ʂ��Đݒ�͈�FOR��
	//�L�[CON�̒�������΁A�ǂ̃L�[�Ȃ̂����`�F�b�N����B
	//F1�L�[����������A�t�@���N���Z�b�g�L�[�R���t�B�O�ɐ؂�ւ���B

	for (auto id : INPUT_ID())
	{
		InputState::state(id,_buf[_keyCon[static_cast<size_t>(id)]]);
	}

	if (_buf[KEY_INPUT_F1]&&!modekeyOld)
	{
		_confId=INPUT_ID::LEFT;
		func = &KeyState::SetKeyConfig;
		TRACE("�L�[�R���t�B�O�J�n\n");
		for (auto id : INPUT_ID())
		{
			InputState::state(id, 0);
			/*keys[static_cast<int>(id)] = 0;*/
		}

	}

	
}

void KeyState::SetKeyConfig(void)
{
	//�g���[�X�ŁA�n�߂邱�ƁA�I��������Ƃ𗬂��B
	//F1�L�[���������u�ԃt�@���N���AREF�L�[�f�[�^�ɖ߂��B
	//�ЂƂ��Ƃɐݒ�B

	if (_buf[KEY_INPUT_F1] && !modekeyOld)
	{
		
		func = &KeyState::RefKeyData;
		FILE* fileptr = 0;
		fopen_s(&fileptr, "data/key.dat", "r");
		if (fileptr != NULL)
		{
			fread(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
			fclose(fileptr);
		}
		TRACE("�L�[�R���t�B�O���f\n");
		return;
	}


	auto checkkey = [&](int id)
	{

		for (auto cid = INPUT_ID::LEFT; cid < _confId; ++cid)
		{
			if (_keyCon[static_cast<int>(cid)] == id)
			{
				return false;
			}

		}
		return true;
	};

	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkkey(id))
		{
			continue;
		}
		if (_buf[id] &&( !_buf[KEY_INPUT_F1]))
		{
			

			_keyCon[static_cast<int>(_confId)] = id;
			++_confId;
			TRACE("%d��%d����\n", _keyCon.size(),_confId);
			TRACE("%d:%d\n", _confId, id);


			if (_confId==end(_confId))
			{
				FILE* fileptr;

				fopen_s(&fileptr, "data/key.dat", "wb");

				if (fileptr != NULL)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
					fclose(fileptr);
				}

				func = &KeyState::RefKeyData;
				TRACE("�L�[�R���t�B�O�I��\n");
				break;
			}
		}
	}

	return;


	//

	/*for (auto key : INPUT_ID())
	{
		if (_confId >= INPUT_ID::MAX)
		{
			func = &KeyState::RefKeyData;
			TRACE("�L�[�R���t�B�O�I��\n");
			return;
		}
		else
		{
			for (int id = 0; id < sizeof(_buf); id++)
			{
				for (auto idol : INPUT_ID())
				{
					if (keys[static_cast<int>(idol)] == id)
					{
						return;
					}
				}

				if (_buf[id])
				{
					if (KEY_INPUT_F1 != id)
					{
						keys[static_cast<int>(_confId)] = id;
						_keyCon[static_cast<int>(_confId)] = id;
						TRACE("%d:%d\n", _confId, id);
						++_confId;
					}
				}
			}
		}
	}*/
}


