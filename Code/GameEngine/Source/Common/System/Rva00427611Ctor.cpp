// cl: /Ireference/shims/bfme2_ascii /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00427611@@QAE@XZ @0x004275D4 47B.
// MI ctor: primary BFME2NativeNetwork via inline ctor calling rowed baseConstruct
// 0x001B4E63, secondary Snapshot storing shared vtable g_00BBB554, derived vtables
// 0x00C3C644/0x00C3C634, vector<BfmeE16> member at +0x10 via rowed _Vector_base
// ctor 0x00211E58. Layout from rowed dtor at 0x00427611 (GameEngineDeletingBase
// size 0xC at +0, Snapshot at +0xC, buffer at +0x10); base pattern from
// Rva001FDB55Ctor/Rva0035CAD6Ctor; Snapshot restore to g_00BBB554 from dtor TU.
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeE16 { float x, y, z, w; };

namespace _STL {
// Declared only so the default construction stays an outlined call that the
// gate resolves to the rowed base at 0x00211E58; with the visible STLport
// definition the build inlines the base and the call vanishes.
template<> _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16> &);
}

extern const void *const g_00BBB554[];

class __declspec(novtable) BFME2NativeNetwork
{
public:
	__forceinline BFME2NativeNetwork() { baseConstruct(); }
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	void baseConstruct();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

class __declspec(novtable) Snapshot
{
public:
	__forceinline Snapshot() { *(const void **)this = g_00BBB554; }
	virtual ~Snapshot();
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

class Rva00427611 : public BFME2NativeNetwork, public Snapshot
{
public:
	Rva00427611();
private:
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m10;
};

Rva00427611::Rva00427611()
{
}
