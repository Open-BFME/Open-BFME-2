// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00154058Holder@@QAE@PAX@Z, retail 0x00154058, 73 bytes.
// Constructor of the holder whose destructor is rowed at 0x00153D16
// (Rva00153D16Dtor.cpp): it zeroes the COM pointer at +0, builds a
// vector<BfmeE16> at +4 through the rowed _Vector_base ctor 0x00211E58, zeroes
// the pointer at +0x10 and then hands the argument to the holder's set-surface
// method at 0x00153F08 (336B, unpinned; address-derived pin). The class name is
// address-derived and no original identity is claimed. The 0x00154370 SSE
// sibling needs /G7 /arch:SSE and lives in its own TU (Rva00154370Cluster.cpp)
// because /O1 changes that body by one byte.

#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00154058Holder
{
public:
	Rva00154058Holder(void *surface);

	// 0x00153F08: set-surface worker, declared only.
	void rva00153f08(void *surface);

private:
	void *m_ptr;                 // +0
	_STL::vector<BfmeE16> m_vec; // +4
	void *m_extra;               // +0x10
};

Rva00154058Holder::Rva00154058Holder(void *surface)
	: m_ptr(0), m_vec(_STL::allocator<BfmeE16>()), m_extra(0)
{
	if (surface)
		rva00153f08(surface);
}
