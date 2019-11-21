#pragma once
#include <Vector>
#include <Vector2.h>

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR
};

using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2db>>;

class EnemyMove
{
public:
	EnemyMove(Vector2db& pos);
	~EnemyMove();
	void Updata(void);	//�X�V����
	bool SetMoveState(MoveState& state,bool newFlag);	//�O�ł���Ă��炤�B�V������肽���Ƃ��Ƒ����ɓ����Ƃ��B
private:
	void SetMovePrg(void);	//�s�����@����

	void (EnemyMove::*_move)(void);	//�G�s���p�̃����o�[�֐��|�C���^�[
	void MoveSigmoid(void);		//�V�O���C�h
	void MoveSpiral(void);		//�X�p�C����
	void PitIn(void);			//�s�b�g�C��
	void Wait(void);			//�҂�
	void MoveLR(void);			//�L�������菬�����Ȃ�����

	int count;

	MoveState _aim;		//�ړ��^�C�v�A�S�[���n�_���W
	int _aimCnt;	//aim�̌��ݒn�������B

	Vector2db _startPos;	//�e�ړ��֐��̊J�n�n�_
	Vector2db _endPos;		//�e�ړ��֐��̏I���n�_

	Vector2db & _pos;	//���W

};

