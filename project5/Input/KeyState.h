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

	char _buf[256];	//全キーデータ格納
	std::vector<int> _keyCon;		//操作用のキーを格納
	std::vector<int> _keyConDef;	//既定の操作キーを格納
	int modekeyOld;					//f11

	//void kmset(void);				//キー設定を、ファイルに格納
	//void kmload(void);				//キー設定をロード


	INPUT_ID _confId;
	//int keys[static_cast<int>(INPUT_ID::MAX)];
};

