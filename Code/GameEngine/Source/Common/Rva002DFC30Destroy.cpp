// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport46
// ??$_Destroy@PAVRva002DFC30@@@_STL@@YAXPAVRva002DFC30@@0@Z @0x00331FF1 25B
// Range destroy over 12-byte Rva002DFC30 elements via ICF twin dtor at 0x29D7C2.
// Element layout int plus AsciiString at +4 plus byte at +8 matches rowed copy
// ctor at 0x331759. Callers are vector assign at 0x332217 and vector dtors.
#include <vector>

#include "ascii_string.h"

class Rva002DFC30
{
	int m_00;
	AsciiString m_04;
	char m_08;

public:
	~Rva002DFC30();
};

namespace _STL
{

template <>
inline void _Destroy<Rva002DFC30 *>(Rva002DFC30 *__first, Rva002DFC30 *__last)
{
	for (; __first != __last; ++__first)
		_Destroy(&*__first);
}

}

template void _STL::_Destroy<Rva002DFC30 *>(Rva002DFC30 *, Rva002DFC30 *);
