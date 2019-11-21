#pragma once

#ifdef _DEBUG

#include <Windows.h>
#include <memory>
//�f�o�b�O���b�Z�[�W�p��`
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d�s��\0",__FILE__,__LINE__);\
	MessageBox(0,ast_mes,"�A�T-�g�\��",MB_OK);\
	}

#define TRACE(fmd, ...) printf(fmd, __VA_ARGS__)

class _DubugConOut
{
public:
	static _DubugConOut& GetInstance(void)	//�Q�ƌĂяo�������B
	{
		return *sInstance;
	}

private:
	struct _DubugConOutDeleter	//�f�R���g���N�^�[���A�ĂׂȂ��̂ŃJ�X�^���f���[�^�[�����
	{
		void operator()(_DubugConOut* _dubugConOut)const
		{
			delete _dubugConOut;
		}
	};

	static std::unique_ptr<_DubugConOut, _DubugConOutDeleter> sInstance;	//�Ǘ����A�C���āA�J�X�^���f���[�^�[���w�肷��
	
	FILE* _debugFp;
	
	_DubugConOut();

	~_DubugConOut();
};

#else	//_DEBUG
#define AST()
#define TRACE(fmd, ...)
#endif //_DEBUG

