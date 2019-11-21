#pragma once

#ifdef _DEBUG

#include <Windows.h>
#include <memory>
//デバッグメッセージ用定義
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目\0",__FILE__,__LINE__);\
	MessageBox(0,ast_mes,"アサ-ト表示",MB_OK);\
	}

#define TRACE(fmd, ...) printf(fmd, __VA_ARGS__)

class _DubugConOut
{
public:
	static _DubugConOut& GetInstance(void)	//参照呼び出しを作る。
	{
		return *sInstance;
	}

private:
	struct _DubugConOutDeleter	//デコントラクターを、呼べないのでカスタムデリーターを作る
	{
		void operator()(_DubugConOut* _dubugConOut)const
		{
			delete _dubugConOut;
		}
	};

	static std::unique_ptr<_DubugConOut, _DubugConOutDeleter> sInstance;	//管理を、任せて、カスタムデリーターを指定する
	
	FILE* _debugFp;
	
	_DubugConOut();

	~_DubugConOut();
};

#else	//_DEBUG
#define AST()
#define TRACE(fmd, ...)
#endif //_DEBUG

