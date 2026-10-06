// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva001D901B@Rva001D901B@@QBEPBVArmorTemplate@@ABVAsciiString@@@Z @0x001D901B 47B unlock.
// Evidence: NameKeyGenerator->nameToKey 0x0009FA65 rowed plus hashtable _M_find
// 0x002888D4 rowed; lea ecx [esi+0xc] proves map at +0xc; callers 0x001D908A
// 0x001D910C 0x001D9130 0x00339544 use AsciiString arg and ArmorTemplate result.
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
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate *,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva001D901B
{
public:
	const ArmorTemplate *rva001D901B(const AsciiString &name) const;
private:
	unsigned char m_pad[12];
	ArmorTemplateMap m_map;
};

const ArmorTemplate *Rva001D901B::rva001D901B(const AsciiString &name) const
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorTemplateMap::const_iterator it = m_map.find(key);
	if (it == m_map.end())
		return 0;
	return (*it).second;
}
