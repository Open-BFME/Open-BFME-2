// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Default-flag emission of the FXListStore hash_map node allocator (speed-optimised instantiation; FXList.cpp itself is size-optimised).
//
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
// Suppress this TU's non-retail const-begin copy (row 47 family2-LK3).
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
#include "GameClient/FXList.h"
#include "Common/DrawModule.h"
#include "Common/GameAudio.h"
#include "Common/INI.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/TerrainLogic.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "GameClient/ParticleSys.h"
#include "GameLogic/PartitionManager.h"
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$_Construct@U?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBW4Nam:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> void _Construct<pair<NameKeyType const ,FXList>,pair<NameKeyType const ,FXList> >(pair<NameKeyType const ,FXList> *,pair<NameKeyType const ,FXList> const &); }
// Suppress this TU's non-retail copy of ??0?$pair@$$CBW4NameKeyType@@VFXList@@@_STL@@QAE@ABU01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class FXList;
namespace _STL { template <> pair<NameKeyType const ,FXList>::pair(pair<NameKeyType const ,FXList> const &); }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }
#ifdef _INTERNAL
#endif

// Suppress this TU's non-retail list<FXNugget*>::insert copy: it is first in
// link order, so it displaced the retail copy FXListNuggetParse.cpp and FXList.cpp
// emit. Plain declaration-only form (no __imp_).
namespace _STL { template <> list<FXNugget *>::iterator list<FXNugget *>::insert(iterator, FXNugget *const &); }


// The constructor unit supplies the whole retail 48-byte bucket-count copy.
// This speed-optimized unit's former 50-byte copy displaced it at link time.
namespace _STL {
template <> unsigned int hashtable<pair<NameKeyType const, FXList>, NameKeyType,
    rts::hash<NameKeyType>, _Select1st<pair<NameKeyType const, FXList> >,
    rts::equal_to<NameKeyType>, allocator<pair<NameKeyType const, FXList> >
    >::_M_next_size(unsigned int) const;
}

// LINK-COMDAT: rts::equal_to<NameKeyType> is kept as the /O1 copy from FXList.cpp;
// this TU is default-flag (speed) for its _M_new_node row, so its own copy differs.
// Specialize only the member under "s" so our emitted copy matches the kept /O1 body,
// while inlined key compares and the _M_new_node row keep default flags.
namespace rts {
template<> Bool equal_to<NameKeyType>::operator()(const NameKeyType &a, const NameKeyType &b) const { return a == b; }
}
#pragma optimize("", on)

typedef _STL::pair<const NameKeyType, FXList> BfmeFXListMapValue;
template _STL::_Hashtable_node<BfmeFXListMapValue> *
_STL::hashtable<BfmeFXListMapValue, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<BfmeFXListMapValue>, rts::equal_to<NameKeyType>,
    _STL::allocator<BfmeFXListMapValue> >::_M_new_node(const BfmeFXListMapValue &);
template BfmeFXListMapValue &
_STL::hashtable<BfmeFXListMapValue, NameKeyType, rts::hash<NameKeyType>,
    _STL::_Select1st<BfmeFXListMapValue>, rts::equal_to<NameKeyType>,
    _STL::allocator<BfmeFXListMapValue> >::_M_insert(const BfmeFXListMapValue &);
template _STL::_List_base<FXNugget *, _STL::allocator<FXNugget *> >::_List_base(
    const _STL::allocator<FXNugget *> &);
