#include <_DubugConOut.h>
#include "EnemyMove.h"



EnemyMove::EnemyMove(Vector2db& pos): _pos( pos )
{
	_move = nullptr;
	_aimCnt = -1;
}
  
   
EnemyMove::~EnemyMove()
{
}

void EnemyMove::Updata(void)
{
	if (_move!=nullptr)
	{
		(this->*_move)();
	}

	//_pos.x++;
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		_aim.clear();
	}

	_aim=std::move(state);

	if (newFlag)
	{
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;
	if (static_cast<unsigned>(_aimCnt)>=_aim.size())	//aimCntが、範囲外の時にreturnする
	{
		return;
	}

	//スタート座標を保存する。
	_startPos = _pos;		//開始地点は、敵キャラが現在いる場所。
	_endPos = _aim[_aimCnt].second;		//secondにある、ゴール地点座標を使う。

	//メンバー関数ポインターの設定をスイッチかIFでやる
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;	//playerに、そんなにデメリットがなく、メリットもそんなにないのを選ぶ。ので、何もしないものにする。
		break;
	}

}

void EnemyMove::MoveSigmoid(void)
{	

}

void EnemyMove::MoveSpiral(void)
{
}

void EnemyMove::PitIn(void)
{
}

void EnemyMove::Wait(void)
{

	if (count >= _aim[_aimCnt].second.x)	//０から数えて指定フレームに達したら、次の処理に移動したい。
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{
	_pos.x++;
}

