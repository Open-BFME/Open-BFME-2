// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$_Construct@VRva00403927@@V1@@_STL@@YAXPAVRva00403927@@ABV1@@Z @0x00403B5A 45B
// _STL::_Construct for stride-0x14 Rva00403927 (two ints + vector<AsciiString> at +8).
// Evidence: called by 0x00403BAD (uninitialized_fill_n loop, stride 0x14, count)
// and 0x00403B87 (uninitialized_copy loop, stride 0x14); callee is the rowed copy
// ctor ??0Rva00403927@@QAE@ABV0@@Z at 0x004039BD; null-guarded placement copy
// (stlport_construct_asciistring.cpp 45B precedent); /EHsc gives the EH prolog
// with handler at 0x00784D11 for the non-trivial vector member.
#include <memory>
#include <vector>
#include "ascii_string.h"

class Rva00403927
{
public:
	Rva00403927(const Rva00403927 &other);
private:
	int m_00;
	int m_04;
	_STL::vector<AsciiString> m_names;
};

template void _STL::_Construct<Rva00403927, Rva00403927>(Rva00403927 *, const Rva00403927 &);
