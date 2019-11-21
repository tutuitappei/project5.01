#pragma once
#include <map>
#include <InputID.h>


using KeyPir = std::pair<int, int>;		//キーNEWとOLD
using KeyMap = std::map<INPUT_ID, KeyPir>;		//種類,｛NEW、OLD｝

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void Update(void)=0;

	const KeyMap& state(void)const;		//キーマップを丸ごと返す。
	const KeyPir& state(INPUT_ID id)const;	//IDに対応するものを返す
	bool state(INPUT_ID id,int kf);		//キーデータをセット
	void SetOld(void);
private:
	KeyMap _state;						//キーデータを入れるやつ。


};

