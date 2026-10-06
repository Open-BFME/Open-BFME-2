// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva00585B16@@PAV1@@_STL@@YAPAVRva00585B16@@PAV1@00ABU__false_type@0@@Z @0x00585CE0 38B
// Evidence: retail (first, last, result) loop calls rowed _Construct at
// 0x005859C6 with stride 0x54 on both ranges; callers at 0x00586C97 0x00586CE2
// 0x00586F1F 0x00586F6B; same family as rowed fill_n @0x005859F3;
// explicit instantiation of the ONE member; declared-only _Construct
// keeps the call external.
#include <vector>

class Rva00585B16
{
public:
	Rva00585B16(const Rva00585B16 &other);
	~Rva00585B16();
private:
	char m_body[0x54];
};

namespace _STL
{
template <> void _Construct<Rva00585B16, Rva00585B16>(
	Rva00585B16 *ptr, const Rva00585B16 &value);
}

template Rva00585B16 *_STL::__uninitialized_copy<Rva00585B16 *,
	Rva00585B16 *>(
	Rva00585B16 *first, Rva00585B16 *last,
	Rva00585B16 *result, const _STL::__false_type &);
