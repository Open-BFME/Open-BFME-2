// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?remove@ThreatFinderManager@@QAEXABVAsciiString@@PAX@Z @0x003ED2A3 (62B):
// manager remove-by-name (erases hash_map entry when _M_find hits; second
// arg ignored but kept for ret-8 parity with the add twin 0x003ED265).
// Called once from the heap-object unregister helper 0x003ECDB7. Callees
// are the rowed AsciiString nameToKey 0x0009FA65 plus the rowed Armor
// hashtable _M_find 0x002888D4 plus the rowed hash_map erase 0x001E2861.
// Layout mirrors ArmorStore (SubsystemInterface base 0x0C plus map at
// +0x0C) so the +0x0C hashtable calls match. No donor name claimed.
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
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

#include "ascii_string.h"
// bfme link decl-only begin
template <> unsigned int rts::hash<NameKeyType>::operator()(NameKeyType const &) const;
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_ST:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; class ArmorTemplate;
namespace _STL { template <> void allocator<_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > >::deallocate(_Hashtable_node<pair<NameKeyType const ,ArmorTemplate> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??A?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEABQAXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void *const &vector<void *>::operator[](size_t) const; }

#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

// The retail erase wrapper is owned by ArmorHashMapErase.cpp.
namespace _STL {
template <> void ArmorTemplateMap::erase(ArmorTemplateMap::iterator);
typedef pair<const NameKeyType, ArmorTemplate> ThreatArmorValue;
typedef hashtable<ThreatArmorValue, NameKeyType, rts::hash<NameKeyType>,
    _Select1st<ThreatArmorValue>, equal_to<NameKeyType>,
    allocator<ThreatArmorValue> > ThreatArmorTable;
// Suppress the member-template body, retaining the standard find wrapper.
template <> template <class Key> _Hashtable_node<ThreatArmorValue> *
ThreatArmorTable::_M_find(const Key &) const;
}

class ThreatFinderManager : public SubsystemInterface
{
public:
	void remove(const AsciiString &name, void *unused);
	void add(const AsciiString &name, void *obj);
	void init() { }
	void reset() { }
	void update() { }

private:
	ArmorTemplateMap m_map;
};

class Object;

#include "../../../Include/Common/ObjectLookupMap.h"

void ThreatFinderManager::remove(const AsciiString &name, void *unused)
{
	(void)unused;
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::iterator it = m_map.find(key);
	if (it != m_map.end())
		m_map.erase(it);
}

void ThreatFinderManager::add(const AsciiString &name, void *obj)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::iterator it = m_map.find(key);
	if (it == m_map.end())
	{
		Object **slot = ((ObjectLookupMap *)&m_map)->findSlot((int *)&key);
		*slot = (Object *)obj;
	}
}
