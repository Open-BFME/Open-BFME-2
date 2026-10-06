// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva0040AFF3@@@_STL@@YAXPAURva0040AFF3@@0@Z @ 0x0040B547 (25B). Range destroy stride 0x68 via rowed dtor.
// Evidence: retail loop calls rowed ??1Rva0040AFF3@@QAE@XZ 0x0040AFF3 with add esi 0x68; callers 0x0040B59F 0x0040B5FC vector dtors; same 25B shape as rowed 0x0040B52E.
#include <vector>

struct Rva0040AFF3
{
	~Rva0040AFF3();
	unsigned char m_data[0x68];
};

template void _STL::_Destroy<Rva0040AFF3 *>(Rva0040AFF3 *, Rva0040AFF3 *);
