// stlport
// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva0035516C@Rva0035516C@@QBEPBVArmorTemplate@@W4NameKeyType@@@Z retail 0x0035516C 23B.
// Unlock lane: ready body calling rowed Armor hashtable _M_find 0x002888D4 with map at +0x24.
// Returns first dword of the ArmorTemplate value (mov [eax+8]) as const pointer; callers at
// 0x000E05A3 0x0035521F 0x003553E3 use return+4 as list head proving +0 is pointer-sized.
// Layout mirrors ArmorStoreCtor TU-local hash_map but at +0x24 with 0x24 pad.

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
	void *m_ptr; // +0x00 returned via mov [node+8]
	char m_pad4[4]; // +0x04 pad to +0x08
	int m_check; // +0x08 compared by rva003551B5
	char m_padC[0x70]; // +0x0C..+0x7C pad to true 0x7C size
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva0035516C
{
public:
	const ArmorTemplate *rva0035516C(NameKeyType key) const;
	bool rva003551B5(NameKeyType key) const;
	void rva003551EA(NameKeyType key) const;

private:
	char m_pad[0x24]; // +0x00..+0x24 unknown
	ArmorTemplateMap m_map; // +0x24
};

class Rva0054840A
{
public:
	void rva00548700();
};

const ArmorTemplate *Rva0035516C::rva0035516C(NameKeyType key) const
{
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	if (it == m_map.end())
		return 0;
	return (const ArmorTemplate *)it->second.m_ptr;
}

bool Rva0035516C::rva003551B5(NameKeyType key) const
{
	const ArmorTemplate *found = rva0035516C(key);
	if (found)
		return found->m_check != 0;
	return false;
}

void Rva0035516C::rva003551EA(NameKeyType key) const
{
	const ArmorTemplate *found = rva0035516C(key);
	if (!found)
		return;
	((Rva0054840A *)found)->rva00548700();
}
