// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva000D3FA0Map@@QAE@XZ @0x00243177 50B. Ctor stores vtable 0x00BEE024 then constructs map<long LadderPref> at +4.
// Evidence: vptr store plus rowed map ctor 0x00242F01 plus __EH_prolog plus caller 0x0024410C plus unblocks 0x00243EE7.
#include "unicode_string.h"
#include "ascii_string.h"
#include <map>
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@U?$pair@$$CBJVLadderPref@@@_STL@@V?$allocator@U?$pair@$$CBJVLadderPref@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LadderPref;
namespace _STL { template <> _Rb_tree_base<pair<long const ,LadderPref>,allocator<pair<long const ,LadderPref> > >::_Rb_tree_base(allocator<pair<long const ,LadderPref> > const &); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBJVLadderPref@@@_STL@@@_STL@@@_STL@@QBEP:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class LadderPref;
namespace _STL { template <> _Rb_tree_node<pair<long const ,LadderPref> > * allocator<_Rb_tree_node<pair<long const ,LadderPref> > >::allocate(unsigned int,void const *) const; }

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

#include "../../../../GameEngine/Include/GameNetwork/LadderPref.h"

// The base is the canonical Snapshot (vtable 0x00BBB554): the ctor's unwind
// funclet 0x007713DB destroys it through the folded Snapshot destructor
// 0x0049B47C.
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva000D3FA0Map : public Snapshot
{
public:
	Rva000D3FA0Map();
	virtual ~Rva000D3FA0Map();
protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	_STL::map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > > m_map;
};

Rva000D3FA0Map::Rva000D3FA0Map()
{
}
