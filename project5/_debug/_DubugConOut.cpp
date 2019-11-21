#ifdef _DEBUG

#include <Windows.h>
#include "_DubugConOut.h"


std::unique_ptr<_DubugConOut, _DubugConOut::_DubugConOutDeleter> _DubugConOut::sInstance(new _DubugConOut());

_DubugConOut::_DubugConOut()
{
	AllocConsole();
	freopen_s(&_debugFp,"CONOUT$","w",stdout);
	freopen_s(&_debugFp, "CONOUT$", "r", stdin);

}


_DubugConOut::~_DubugConOut()
{
	FreeConsole();
}


#endif // DEBUG