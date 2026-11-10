// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?erase@?$hash_map@W4NameKeyType@@VArmorTemplate@@U?$hash@W4NameKeyType@@@rts@@U?$equal_to@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@6@@_STL@@QAEXU?$_Ht_iterator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@2@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@2@@Z @ 0x001E2861 (30B).
// Armor hash_map iterator eraser forwarding to rowed hashtable erase.
// Evidence: 12 callers all use Armor _M_find 0x002888D4; same flags as ArmorStoreCtor member ctor.
// It calls the hashtable erase at 0x000557BB (ICF fold with the rowed
// hashtable<int> erase), which divides the key inline: rts::hash<NameKeyType>
// is Zero Hour's inline identity hash, as in the other Armor table views.
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class ArmorTemplate;
namespace _STL { template <> void allocator<_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > >::deallocate(_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > *,unsigned int) const; }
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const { return (size_t)value; }	// Zero Hour's rts::hash<NameKeyType>, inline
};

}

#include "../../../Include/GameLogic/Armor.h"

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

// Retail table erase hashes inline; retain that visibility without an external bucket copy.
namespace _STL {
typedef pair<const NameKeyType, ArmorTemplate> ArmorValue;
typedef hashtable<ArmorValue, NameKeyType, rts::hash<NameKeyType>,
    _Select1st<ArmorValue>, equal_to<NameKeyType>, allocator<ArmorValue> > ArmorTable;
// ?ArmorTable::_M_bkt_num_key absent-from-retail
// The native erase inlines this calculation; this specialization emits no body.
template <> __declspec(dllimport) __forceinline
size_t ArmorTable::_M_bkt_num_key(const NameKeyType &key) const
{
    return _M_hash(key) % _M_buckets.size();
}
// Use XferSaveOpen.obj's _M_delete_node copy instead of emitting a conflicting 32-byte one.
template <> void ArmorTable::_M_delete_node(_Hashtable_node<ArmorValue> *);
}

template void ArmorTemplateMap::erase(ArmorTemplateMap::iterator);
