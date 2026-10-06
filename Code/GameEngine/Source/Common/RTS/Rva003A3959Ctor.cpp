// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva003A3959@@QAE@XZ @0x003A3959 50B: outer ctor storing vtable 0x0081ADFC then constructing member at +4 via rowed 0x003A393A with EH frame.
// Evidence: chain packet calls rowed 0x003A393A; vtable store at [this] plus EH_prolog with handler 0x00781A02; callers 0x002AF8BB and 0x003A3AB8; unblocks 0x003A39A7; empty base arms EH state 0 (ProductionUpdateModuleData precedent).
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

typedef ArmorTemplateMap::value_type ArmorPair003A3959;
typedef ArmorTemplateMap::hasher ArmorHasher003A3959;
typedef ArmorTemplateMap::key_equal ArmorEqual003A3959;
typedef ArmorTemplateMap::allocator_type ArmorAlloc003A3959;

typedef _STL::hashtable<
	ArmorPair003A3959,
	NameKeyType,
	ArmorHasher003A3959,
	_STL::_Select1st<ArmorPair003A3959>,
	ArmorEqual003A3959,
	ArmorAlloc003A3959> ArmorHashtable003A3959;

class Rva003A393A
{
public:
	Rva003A393A();
private:
	ArmorHashtable003A3959 m_table;
};

extern const void *const g_00C1ADFC[];

// Empty base with inline empty ctor but declared-only dtor: no base call is
// emitted, but the base is unwindable, so retail arms EH state 0 before the
// first member call (ProductionUpdateModuleData precedent, EBO keeps +0).
class Rva003A3959Base
{
public:
	Rva003A3959Base() {}
	~Rva003A3959Base();
};

class Rva003A3959 : public Rva003A3959Base
{
public:
	Rva003A3959();
private:
	const void *m_vtable;
	Rva003A393A m_inner;
};

Rva003A3959::Rva003A3959()
	: Rva003A3959Base()
	, m_vtable(g_00C1ADFC)
{
}
