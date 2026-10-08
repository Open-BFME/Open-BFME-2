// stlport
// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// Retail RVA 0x00360BB8, 70 bytes.
// ArmorStore::ArmorStore: base SubsystemInterface init (retail 0x001B4E63,
// which installs vtable 0xBD77A0 and zeroes +4/+8, proving the BFME2 base is
// 0xC bytes, not the ZH 8), derived vtable 0xC16988, member hash_map default
// construction (retail 0x00360B99) then hashtable clear (rowed 0x001DBCDC).
// Shard: Armor.cpp sees the ZH 8-byte SubsystemInterface, which puts the map
// at +0x8; the TU-local base below carries the retail-proven extra members.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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
	float m_damageCoefficient[38]; // DAMAGE_NUM_TYPES, ZH count
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	unsigned char m_bfme04[8]; // retail ctor zeroes byte@4 and dword@8
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class ArmorStore : public SubsystemInterface
{
public:
	ArmorStore();
	virtual ~ArmorStore();
	void init() { }
	void reset() { }
	void update() { }
	const ArmorTemplate *findArmorTemplate(AsciiString name) const;

private:
	ArmorTemplateMap m_armorTemplates; // +0x0C
};

ArmorStore::ArmorStore()
{
	m_armorTemplates.clear();
}

ArmorStore::~ArmorStore()
{
	m_armorTemplates.clear();
}

const ArmorTemplate *ArmorStore::findArmorTemplate(AsciiString name) const
{
	NameKeyType namekey = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_armorTemplates.find(namekey);
	if (it == m_armorTemplates.end())
	{
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}
