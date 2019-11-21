#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <Vector2.h>

enum class STATE
{
	NORMAL,	//通常
	EX,		//特殊
	DETH,	//爆発（死亡）
	MAX		
};

class Obj;

using AnimVector = std::vector<std::pair<int, unsigned int>>;	//画像ID　秒（FLMCNT）
using shardObj = std::shared_ptr<Obj>;

class Obj
{
public:
	Obj();
	virtual void Updata(void)=0;
	void Draw(void);				//描画したいものをキューに入れる。
	void Draw(int id);				//描画したいものをキューに入れる。
	virtual ~Obj();

	bool State(const STATE state);	//set
	const STATE State(void)const;	//get

	bool SetAnim(STATE state,AnimVector& data);	//動きセット

	bool SetAlive(bool alive);	//生死設定

	bool isAlive(void) { return _alive; }	//生存しているか調べる
	bool isDead(void) { return _dead; }		//死亡しているか調べる

	bool isAnimEnd(void);
private:
	std::map<STATE, AnimVector> _animMap;		//アニメーションを設定するための
	STATE _state;								//状態
	unsigned int _animFrame;					//何番目のフレーム
	unsigned int _animCount;					//カウンター
	
protected:
	bool DestroyProck(void);	//爆破アニメーションが、終わっているか。
	bool _alive;	//生存しているか
	bool _dead;		//死亡しているか
	Vector2db _Pos;	//座標
	Vector2db _Size;	//サイズ
	double _rad;	//角度
};	

