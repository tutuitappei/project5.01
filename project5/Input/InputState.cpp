#include <_DubugConOut.h>
#include "InputState.h"

InputState::InputState()
{

	for (auto key : INPUT_ID())
	{

		_state.try_emplace(key, KeyPir{0,1});

	}





}


InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPir & InputState::state(INPUT_ID id)const
{
	static KeyPir defDate = { 0,0 };		//���ł͎g�������Ȃ�����A�����ɍ��B

	try
	{
		return	_state.at(id);
	}
	catch(...)
	{
		AST();
		return defDate;						//�o0,0�p���A���̂܂܎g���̂͂悭�Ȃ��̂ŁA�Q�Ƃł���,���̂����݂�����̂�p�ӂ���B
	}


}

bool InputState::state(INPUT_ID id, int kf)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = kf;
		return true;
	}


	return false;
}

void InputState::SetOld(void)
{

	for (auto key : INPUT_ID())
	{
		try
		{
			_state[key].second = _state[key].first;
		}
		catch (const std::exception&)
		{
			AST();
			_state.emplace(key, KeyPir{ 0,1 });
		}

	}
}

