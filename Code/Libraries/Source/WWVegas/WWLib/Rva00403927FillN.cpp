// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAVRva00403927@@IV1@@_STL@@YAPAVRva00403927@@PAV1@IABV1@ABU__false_type@0@@Z @0x00403BAD 37B
// _STL::__uninitialized_fill_n<Rva00403927>, retail 37 bytes, the header's loop;
// _Construct is the rowed 0x00403B5A. Called by 0x004044C5 in 0x00404457.
#include <vector>
#include "ascii_string.h"

// _STL::__uninitialized_fill_n<Rva00403927>, retail 37 bytes. Dedicated TU so
// no local _Construct definition can inline into this loop. Element stride is
// 0x14 via the dummy body below; _Construct is declared only and resolves
// through the rowed 0x00403B5A. Called by 0x004044C5 in 0x00404457; unblocks
// 0x00404457. (Rva00564C58FillN.cpp precedent.)
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

template Rva00403927 *_STL::__uninitialized_fill_n(Rva00403927 *, unsigned int, const Rva00403927 &, const _STL::__false_type &);
