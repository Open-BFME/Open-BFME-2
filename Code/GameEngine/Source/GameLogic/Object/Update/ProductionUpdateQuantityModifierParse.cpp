// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva0049FDF9Parse@@YAXPAVINI@@PAVProductionUpdateModuleData@@@Z @0x0049FDF9 113B: INI parse of ProductionUpdateModuleData +0x1C QuantityModifier list entry AsciiString-plus-int 8-byte element; first token via getNextToken 0x2DF97 and second via getNextTokenOrNull 0x2DEED defaulting quantity to 1 else scanInt 0x2ECCF then StringBase set 0x55F5 and vector push_back 0x49FDC2 with releaseBuffer 0x36410 cleanup.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ascii_string.h"
// Suppress this TU's non-retail copy of ?push_back@?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAEXA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> void vector<QuantityModifier,allocator<QuantityModifier> >::push_back(QuantityModifier const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> void vector<QuantityModifier,allocator<QuantityModifier> >::_M_insert_overflow(QuantityModifier *,QuantityModifier const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAUQuantityModifier@@PAU1@@_STL@@YAPAUQuantityModifier@@PAU1@00ABU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> QuantityModifier * __uninitialized_copy<QuantityModifier *,QuantityModifier *>(QuantityModifier *,QuantityModifier *,QuantityModifier *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAUQuantityModifier@@IU1@@_STL@@YAPAUQuantityModifier@@PAU1@IABU:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> QuantityModifier * __uninitialized_fill_n<QuantityModifier *,unsigned int,QuantityModifier>(QuantityModifier *,unsigned int,QuantityModifier const &,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> void vector<QuantityModifier,allocator<QuantityModifier> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAUQuantityModifier@@U1@V?$allocator@UQuantityModifier@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> QuantityModifier * _STLP_alloc_proxy<QuantityModifier *,QuantityModifier,allocator<QuantityModifier> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@UQuantityModifier@@@_STL@@QBEXPAUQuantityModifier@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct QuantityModifier;
namespace _STL { template <> void allocator<QuantityModifier>::deallocate(QuantityModifier *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

#include "../../../../Include/Common/INI/INI.h"

#include "../../../../Include/Common/QuantityModifier.h"

class ProductionUpdateModuleData
{
public:
	const void *m_vtable;
	int m_pad04;
	int m_numDoorAnimations;
	unsigned int m_doorOpeningTime;
	unsigned int m_doorWaitOpenTime;
	unsigned int m_doorClosingTime;
	unsigned int m_constructionCompleteDuration;
	_STL::vector<QuantityModifier, _STL::allocator<QuantityModifier> > m_quantityModifiers;
};

void Rva0049FDF9Parse(INI *ini, ProductionUpdateModuleData *data)
{
	const char *first = ini->getNextToken(0);
	const char *second = ini->getNextTokenOrNull(0);
	int qty;
	if (second != 0)
		qty = ini->scanInt(second);
	else
		qty = 1;
	QuantityModifier mod;
	mod.m_quantity = qty;
	mod.m_templateName.set(first);
	data->m_quantityModifiers.push_back(mod);
}
