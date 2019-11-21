#include<Dxlib.h>
#include "Obj.h"
#include<map>
#include"comon\ImageMng.h"
#include"Scene\SceneMag.h"

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
}

Obj::~Obj()
{
}

void Obj::Draw(void)
{

	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	if ( _animFrame >= _animMap[_state].size()||_animFrame < 0)
	{
		return;
	}
	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{

			_animFrame++;

		}
		if (_animFrame < _animMap[_state].size())
		{
			_animCount++;
		}
		else
		{
			_animFrame = 0;
			_animCount = 0;
		}
	}
	//_animMap[_animKey][_animFrame];
	//lpSceneMng.AddDrawQue( {lpImageMng.GetId("·¬×")[0],0,0 });
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_Pos.x,_Pos.y,_rad});
}

void Obj::Draw(int id)
{

	lpSceneMng.AddDrawQue({ id,_Pos.x,_Pos.y ,_rad});
}


bool Obj::State(const STATE key)
{
	if (_animMap.find(key) == _animMap.end())
	{
		return false;
	}
	if (_state != key)
	{
		_animFrame = 0;
		_animCount = 0;
	}	
	_state = key;
	return true;
	
}

const STATE Obj::State(void) const
{
	return _state;
}

bool Obj::SetAnim(const STATE key, AnimVector& data)
{
	//c++17ˆÈ~
	return (_animMap.try_emplace(key, std::move(data))).second; //second“ñ‚Â–Ú‚Ì—v‘f
	
	//C++17	‚æ‚è‘O
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	_animMap[key]=data;
	//	return true;
	//}
	//return false;
}

bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		State(STATE::DETH);
	}
	return true;
}

bool Obj::isAnimEnd(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}
	if (_animFrame >= _animMap[_state].size() || _animFrame < 0)
	{
		return true;
	}

	if (_animMap[_state][_animFrame].first==-1)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool Obj::DestroyProck(void)
{
	if (_alive==true)
	{
 		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}
	return true;
}

