// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@VRva0032E81D@@V1@@_STL@@YAXPAVRva0032E81D@@ABV1@@Z, retail 0x0032E94B, 45 bytes.
// Null-guarded placement copy via rowed 0x0032E800 copy ctor. Evidence: calls
// 0x0032E800; caller _M_create_node at 0x0032EA93; chain from 0x0032E800.
#include <memory>
#include <vector>

struct BfmeE8 { int a[2]; };
typedef _STL::vector<_STL::vector<BfmeE8> > VecVec;

class Rva0032E81D
{
public:
	Rva0032E81D(const Rva0032E81D &o);
private:
	int m_val00;
	VecVec m_vec04;
};

template void _STL::_Construct<Rva0032E81D, Rva0032E81D>(Rva0032E81D *, const Rva0032E81D &);
