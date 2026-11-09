// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva0041F474@ArmorStore@@QBEPBVArmorTemplate@@ABVAsciiString@@@Z @0x0041F474 51B.
// Armor map find by name via NameKey plus hash_map find (inlines to rowed
// _M_find 0x002888D4) returning second.m_ptr via mov [eax+8]. Evidence:
// callers 0x002090F7 0x002A9519 0x003C5EA3 0x004E9840; map at +0x0C; mirrors
// Rva000AA867 at 0x000AA867 (23B key-only) plus NameKey step.
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
#include "ascii_string.h"
#include "../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
typedef std::hash_map<
	NameKeyType,
	ArmorTemplate *,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;
class ArmorStore : public SubsystemInterface
{
public:
	const ArmorTemplate *rva0041F474(const AsciiString &name) const;
	void init() { }
	void reset() { }
	void update() { }
private:
	ArmorTemplateMap m_map;
};
const ArmorTemplate *ArmorStore::rva0041F474(const AsciiString &name) const
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	return it != m_map.end() ? it->second : 0;
}
