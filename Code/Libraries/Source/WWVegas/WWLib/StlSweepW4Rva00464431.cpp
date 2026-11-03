// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Target facts: the only caller, 0x00464923 (WeaponTemplateSetHeadMapLookupRva00464923.cpp),
// is a lookup-or-create under an unsigned key (jae compare) of a 0x4C-byte value and
// calls this wrapper as map<unsigned, WeaponTemplateSetHead>::insert(hint, value);
// this body forwards to that tree's hinted insert_unique at 0x00463E4D.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

#include "../../../../GameEngine/Include/Common/WeaponTemplateSetHead.h"

typedef _STL::pair<const unsigned int, WeaponTemplateSetHead> WeaponTemplateSetHeadPair;
typedef _STL::_Rb_tree_iterator<WeaponTemplateSetHeadPair, _STL::_Nonconst_traits<WeaponTemplateSetHeadPair> > WeaponTemplateSetHeadIter;

// The hinted insert_unique is retail's 0x00463E4D (Rva00463E4DHintInsert.cpp); a
// declaration-only specialization stops this TU emitting its own copy.
// bfme link decl-only begin
namespace _STL { template <> WeaponTemplateSetHeadIter _Rb_tree<unsigned int, WeaponTemplateSetHeadPair, _STL::_Select1st<WeaponTemplateSetHeadPair>, _STL::less<unsigned int>, _STL::allocator<WeaponTemplateSetHeadPair> >::insert_unique(WeaponTemplateSetHeadIter, const WeaponTemplateSetHeadPair &); }
// bfme link decl-only end

// Instantiate the recovered operation.
template WeaponTemplateSetHeadIter _STL::map<unsigned int, WeaponTemplateSetHead, _STL::less<unsigned int>, _STL::allocator<WeaponTemplateSetHeadPair> >::insert(WeaponTemplateSetHeadIter, const WeaponTemplateSetHeadPair &);
