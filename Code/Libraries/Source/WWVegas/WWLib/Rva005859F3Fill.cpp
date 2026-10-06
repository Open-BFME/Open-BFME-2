// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_fill_n@PAVRva00585B16@@IV1@@_STL@@YAPAVRva00585B16@@PAV1@IABV1@ABU__false_type@0@@Z @0x005859F3 37B
// Evidence: loop calls rowed _Construct at 0x005859C6, dst advances by 0x54,
// count in edi, same value each time; returns dst+n. Same shape as rowed
// __uninitialized_fill_n @0x000C245E (37B); explicit instantiation of the ONE
// member; declared-only _Construct keeps the call external.
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

template Rva00585B16 *_STL::__uninitialized_fill_n<Rva00585B16 *,
	unsigned int, Rva00585B16>(
	Rva00585B16 *first, unsigned int n, const Rva00585B16 &x,
	const _STL::__false_type &);

Rva00585B16 *Rva00585D06Fill(Rva00585B16 *first, unsigned int n, const Rva00585B16 &x)
{
	_STL::__false_type tag;
	return _STL::__uninitialized_fill_n(first, n, x, tag);
}
