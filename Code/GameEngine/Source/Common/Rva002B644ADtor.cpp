// ??1RegionAwardDispute@@UAE@XZ
// cl: /MD /EHs /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// 0x004FC05C 81B RegionAwardDispute virtual dtor; caller ??_G at 0x002B647F.
// Derived vtable 0x007FE280 then host release of +0x18 via rowed 0x00212655
// then vector +0x8 frees via _free 0x00030830 then Snapshot base restores BBB554.
// Layout from rowed ctor 0x002B644A (vtable 0x7FE280, BfmeE16 vector +8,
// ints +4/-1 +0x14/0 +0x18/-1 +0x1C/0). Evidence: vtable stores, pin, caller,
// callees all rowed or pinned.
#include <stdlib.h>
#include <vector>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

#include "../../../Libraries/Include/Lib/BfmeE16.h"

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

#include "../../Include/Common/Rva00DFE1C8Host.h"

// The Snapshot base (vftable 0x00BBB554, restored at the end).
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// The living-world region award dispute (both constructors, 0x002B644A and
// 0x004FC002, store vftable 0x00BFE280).
class RegionAwardDispute : public Snapshot
{
public:
	RegionAwardDispute();
	virtual ~RegionAwardDispute();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	int m_4;	// +0x04
	_STL::vector<BfmeE16> m_vec8;	// +0x08
	int m_14;	// +0x14
	int m_18;	// +0x18
	unsigned char m_1C;	// +0x1C
};

RegionAwardDispute::~RegionAwardDispute()
{
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_18);
}
