// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??1Rva003ED1FC@@UAE@XZ @0x003ED1FC 77B
// Dtor: vtable 0x00C36100 store then ArmorTemplateMap clear plus hashtable
// dtor plus GameEngineDeletingBase dtor. Evidence: caller ??_GRva003ED1FC
// at 0x003ED249 in OpaqueScalarDeletingDtorsB07 plus vtable 0x00C36100 slot 0
// plus callees clear 0x001DBCDC plus dup_003ed1be 0x003ED1BE plus base
// 0x001B4E74; ledger notes ThreatFinderManager identity for this copy vs
// ArmorStore 0x00360A45 but no VTABLE line proves a real name so honest Rva
// name keeps the pin.

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

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	unsigned char m_pad04[8];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva003ED1FC : public GameEngineDeletingBase
{
public:
	virtual ~Rva003ED1FC();
private:
	ArmorTemplateMap m_map;
};

// ??1Rva003ED1FC@@UAE@XZ
Rva003ED1FC::~Rva003ED1FC()
{
	m_map.clear();
}
