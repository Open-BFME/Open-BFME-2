// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
//
// STLport 4.5.3 ios_base::_M_throw_failure. The retail library is built
// without exceptions, so the failure is reported rather than thrown: one fputs
// of "ios failure" - the literal is at 0x00BBCC94 - to stderr, reached as
// _iob[2] through the dllimport array slot, which is what the
// `mov eax,[...]` / `add eax,0x40` pair is.

#include <stdio.h>

namespace _STL
{

class ios_base
{
protected:
	void _M_throw_failure();
};

void ios_base::_M_throw_failure()
{
	fputs("ios failure", &_iob[2]);
}

}
