#include <algorithm>

#include <DxLib.h>

#include "KeyState.h"
#include <InputID.h>
#include <_debug\_DubugConOut.h>

//# fopen

//コンストラクターで、dataフォルダーのkey.datを開く。fopen_s();
//開けた場合はアドレスが、開けなかった場合NULLが返ってくる。
//開けた場合：アドレスー＞freed()->_keycon
//開けなかった場合::nullptr->_keyConに_keyConDefをコピー

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
	//初期化
	for (int i = 0; i < sizeof(_buf); i++)
	{
		_buf[0]={ 0 };
	}
	_confId = INPUT_ID::LEFT;

	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));	//一個一個増やすたびにメモリ取り直すのは嫌だから、先にメモリを予約して、取り直しを防ぐ。
	//DEFAULTを設定
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
	//キー設定
	if (fileptr == NULL)
	{		//もし、からであればDEFAULTにして、ファイルを作る。
		_keyCon = _keyConDef;

		fopen_s(&fileptr, "data/key.dat", "wb");

		if (fileptr != NULL)
		{
			fwrite(_keyCon.data(), sizeof(_keyCon[0]), _keyCon.size(), fileptr);
			fclose(fileptr);
		}

	}
	else
	{	//中身があるのであれば、読み込む
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
	//上に入ってるのうちインプットIDのキー分の情報をステートのセットを通じて設定範囲FOR分
	//キーCONの中を見れば、どのキーなのかをチェックする。
	//F1キーを押したら、ファンクをセットキーコンフィグに切り替える。

	for (auto id : INPUT_ID())
	{
		InputState::state(id,_buf[_keyCon[static_cast<size_t>(id)]]);
	}

	if (_buf[KEY_INPUT_F1]&&!modekeyOld)
	{
		_confId=INPUT_ID::LEFT;
		func = &KeyState::SetKeyConfig;
		TRACE("キーコンフィグ開始\n");
		for (auto id : INPUT_ID())
		{
			InputState::state(id, 0);
			/*keys[static_cast<int>(id)] = 0;*/
		}

	}

	
}

void KeyState::SetKeyConfig(void)
{
	//トレースで、始めること、終わったことを流す。
	//F1キーを押した瞬間ファンクを、REFキーデータに戻す。
	//ひとつごとに設定。

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
		TRACE("キーコンフィグ中断\n");
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
			TRACE("%d個中%dこめ\n", _keyCon.size(),_confId);
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
				TRACE("キーコンフィグ終了\n");
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
			TRACE("キーコンフィグ終了\n");
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


