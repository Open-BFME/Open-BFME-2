// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva0042476C@@QAE@ABV0@@Z @0x0042476C 61B
// ??$__uninitialized_fill_n@PAVRva0042476C@@IV1@@_STL@@YAPAVRva0042476C@@PAV1@IABV1@ABU__false_type@0@@Z @0x00424D8C 37B
// Copy ctor of honest two-vector class: vector<Rva00423A4A> at +0 then vector<unsigned int> at +0xC in declaration order with EH state. Evidence: calls rowed vector copy ctors 0x004244EE then 0x002CFAB9; unblocks 0x00424BF4 via caller 0x00424C10; neighbours stlport vector family same dir and flags.
#include <vector>

struct Rva00423A4A
{
	unsigned int m_data[3];
	~Rva00423A4A() {}
};

class Rva0042476C
{
public:
	Rva0042476C(const Rva0042476C &src);
private:
	_STL::vector<Rva00423A4A> m_vec00;
	_STL::vector<unsigned int> m_vec0C;
};

Rva0042476C::Rva0042476C(const Rva0042476C &src)
	: m_vec00(src.m_vec00)
	, m_vec0C(src.m_vec0C)
{
}

// The 24-byte element's fill loop (stride 0x18). Retail reaches it from the
// vector(n, value) ctor 0x0042545A, rowed as the byte-identical CameraMarker
// spelling, whose fill_n wrapper 0x0042536A calls 0x00424D8C; that body calls
// the EH placement-new construct 0x00424BF4 (rowed in Rva0042476CConstruct.cpp),
// which calls this unit's copy ctor. The CameraMarker pin at 0x00424D8C names the wrapper's
// callee, not the element: CameraMarker is 8 bytes.
namespace _STL {
template Rva0042476C *__uninitialized_fill_n<Rva0042476C *, unsigned int, Rva0042476C>(
	Rva0042476C *, unsigned int, const Rva0042476C &, const __false_type &);
}
