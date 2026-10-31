// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva00403927@@PAV1@@_STL@@YAPAVRva00403927@@PAV1@00ABU__false_type@0@@Z @0x00403B87 38B
// _STL::__uninitialized_copy<Rva00403927>, retail 38 bytes, the header's loop;
// _Construct is the rowed 0x00403B5A. Called twice by 0x00404457.
#include <vector>
#include "ascii_string.h"

// _STL::__uninitialized_copy<Rva00403927>, retail 38 bytes. Dedicated TU so
// Rva00403927Construct.cpp cannot inline _Construct into this loop. Element
// stride is 0x14 via the dummy body below; _Construct is declared only and
// resolves through the rowed 0x00403B5A. Called twice by 0x00404457.
class Rva00403927
{
public:
	Rva00403927(const Rva00403927 &other);
	Rva00403927 &operator=(const Rva00403927 &other);
private:
	int m_00;
	int m_04;
	_STL::vector<AsciiString> m_names;
};

template Rva00403927 *_STL::__uninitialized_copy(Rva00403927 *, Rva00403927 *, Rva00403927 *, const _STL::__false_type &);
