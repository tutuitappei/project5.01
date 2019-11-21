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
	if (static_cast<unsigned>(_aimCnt)>=_aim.size())	//aimCnt���A�͈͊O�̎���return����
	{
		return;
	}

	//�X�^�[�g���W��ۑ�����B
	_startPos = _pos;		//�J�n�n�_�́A�G�L���������݂���ꏊ�B
	_endPos = _aim[_aimCnt].second;		//second�ɂ���A�S�[���n�_���W���g���B

	//�����o�[�֐��|�C���^�[�̐ݒ���X�C�b�`��IF�ł��
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
		_move = &EnemyMove::Wait;	//player�ɁA����ȂɃf�����b�g���Ȃ��A�����b�g������ȂɂȂ��̂�I�ԁB�̂ŁA�������Ȃ����̂ɂ���B
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

	if (count >= _aim[_aimCnt].second.x)	//�O���琔���Ďw��t���[���ɒB������A���̏����Ɉړ��������B
	{
		SetMovePrg();
	}
	count++;
}

void EnemyMove::MoveLR(void)
{
	_pos.x++;
}

