// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?erase@?$hash_map@W4NameKeyType@@VArmorTemplate@@U?$hash@W4NameKeyType@@@rts@@U?$equal_to@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@6@@_STL@@QAEXU?$_Ht_iterator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@2@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@2@@Z @ 0x001E2861 (30B).
// Armor hash_map iterator eraser forwarding to rowed hashtable erase.
// Evidence: 12 callers all use Armor _M_find 0x002888D4; same flags as ArmorStoreCtor member ctor.
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

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

template void ArmorTemplateMap::erase(ArmorTemplateMap::iterator);
