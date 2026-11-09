// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva00355155@Rva00355B61@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z @0x00355155 23B: finds ArmorTemplate in map at +0x10 via rowed hashtable _M_find 0x002888D4.
// Evidence: retail lea eax [esp+4] push eax add ecx 0x10 call _M_find then mov eax [eax+8]; same shape as rowed 0x0035516C find at +0x24; unblocks 9 callers.

#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
vector<void *>::const_reference vector<void *>::operator[](size_type __n) const { return *(begin() + __n); }
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
// The hash body is inline-only in retail; keep this TU's copy from emitting.
namespace rts
{
template <> __declspec(dllimport) __forceinline
size_t hash<NameKeyType>::operator()(const NameKeyType &value) const { return (size_t)value; }
}

#include "../../../Include/GameLogic/Armor.h"

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate *,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
};

class Rva00355B61 : public SubsystemInterface, public SnapshotBase
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
private:
	ArmorTemplateMap m_map1;
	ArmorTemplateMap m_map2;
};

const ArmorTemplate *Rva00355B61::rva00355155(NameKeyType key) const
{
	ArmorTemplateMap::const_iterator it = m_map1.find(key);
	if (it == m_map1.end())
		return 0;
	return it->second;
}
