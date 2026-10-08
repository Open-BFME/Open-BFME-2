// stlport
// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva000AA867@Rva000AA867@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z @0x000AA867 23B
// Armor map find with map at +0x08 calling rowed _M_find 0x002888D4 returning it->second.m_ptr via mov [eax+8]; mirrors Rva0035516C at +0x24; honest Rva name
#include <hash_map>
#include <cstddef>
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
class ArmorTemplate
{
public:
	void *m_ptr;
	char m_pad4[4];
	int m_check;
	char m_padC[0x70];
};
typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;
class Rva000AA867
{
public:
	const ArmorTemplate *rva000AA867(NameKeyType key) const;
private:
	char m_pad[0x08];
	ArmorTemplateMap m_map;
};
const ArmorTemplate *Rva000AA867::rva000AA867(NameKeyType key) const
{
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	if (it == m_map.end())
		return 0;
	return (const ArmorTemplate *)it->second.m_ptr;
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?find@Rva00786BD0Owner@@QAEPAXI@Z=?rva000AA867@Rva000AA867@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z")
