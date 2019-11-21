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
	void Updata(void);	//更新処理
	bool SetMoveState(MoveState& state,bool newFlag);	//外でやってもらう。新しくやりたいときと続きに入れるとき。
private:
	void SetMovePrg(void);	//行動方法制御

	void (EnemyMove::*_move)(void);	//敵行動用のメンバー関数ポインター
	void MoveSigmoid(void);		//シグモイド
	void MoveSpiral(void);		//スパイラル
	void PitIn(void);			//ピットイン
	void Wait(void);			//待つ
	void MoveLR(void);			//広がったり小さくなったり

	int count;

	MoveState _aim;		//移動タイプ、ゴール地点座標
	int _aimCnt;	//aimの現在地を示す。

	Vector2db _startPos;	//各移動関数の開始地点
	Vector2db _endPos;		//各移動関数の終了地点

	Vector2db & _pos;	//座標

};

