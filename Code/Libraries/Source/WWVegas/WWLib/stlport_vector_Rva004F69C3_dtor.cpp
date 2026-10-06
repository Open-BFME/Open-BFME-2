// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva004F69C3@@V?$allocator@URva004F69C3@@@_STL@@@_STL@@QAE@XZ, retail 0x004F8832, 63 bytes.
// Vector<Rva004F69C3> dtor via rowed _Destroy 0x0040DCF1 and _free 0x00030830.
// Same 63B Destroy-plus-free shape as Rva005F8F96 dtor; /EHs gives or-state.
// Caller at 0x004FA33D plus Unwind funclets.
#include <vector>
struct Rva004F69C3
{
	~Rva004F69C3();
	int m_00;
	void *m_04;
};

template void _STL::_Destroy<Rva004F69C3 *>(Rva004F69C3 *, Rva004F69C3 *);
template _STL::vector<Rva004F69C3>::~vector();
template void _STL::vector<Rva004F69C3>::_M_clear();
