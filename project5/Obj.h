#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <Vector2.h>

enum class STATE
{
	NORMAL,	//�ʏ�
	EX,		//����
	DETH,	//�����i���S�j
	MAX		
};

class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	//�摜ID�@�b�iFLMCNT�j
using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Updata(void)=0;
	void Draw(void);				//�`�悵�������̂��L���[�ɓ����B
	void Draw(int id);				//�`�悵�������̂��L���[�ɓ����B
	virtual ~Obj();

	bool State(const STATE state);	//set
	const STATE State(void)const;	//get

	bool SetAnim(STATE state,AnimVector& data);	//�����Z�b�g

	bool SetAlive(bool alive);	//�����ݒ�

	bool isAlive(void) { return _alive; }	//�������Ă��邩���ׂ�
	bool isDead(void) { return _dead; }		//���S���Ă��邩���ׂ�

	bool isAnimEnd(void);
private:
	std::map<STATE, AnimVector> _animMap;		//�A�j���[�V������ݒ肷�邽�߂�
	STATE _state;								//���
	unsigned int _animFrame;					//���Ԗڂ̃t���[��
	unsigned int _animCount;					//�J�E���^�[
	
protected:
	bool DestroyProck(void);	//���j�A�j���[�V�������A�I����Ă��邩�B
	bool _alive;	//�������Ă��邩
	bool _dead;		//���S���Ă��邩
	Vector2db _Pos;	//���W
	Vector2db _Size;	//�T�C�Y
	double _rad;	//�p�x
};	

