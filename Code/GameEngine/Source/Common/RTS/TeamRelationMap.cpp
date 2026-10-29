// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0TeamRelationMap@@QAE@XZ @0x003A3959 50B: outer ctor storing vtable 0x0081ADFC then constructing member at +4 via rowed 0x003A393A with EH frame.
// Identity: the stored table 0x00C1ADFC is TeamRelationMap's (slot 0 the rowed
// ??_GTeamRelationMap 0x003A2A8A, slot 2 the getter returning "TeamRelationMap"),
// and Team's ctor allocates this object into its +0x118 relations pointer.
// Evidence: chain packet calls rowed 0x003A393A; vtable store at [this] plus EH_prolog with handler 0x00781A02; callers 0x002AF8BB and 0x003A3AB8; unblocks 0x003A39A7; empty base arms EH state 0 (ProductionUpdateModuleData precedent).
#include <hash_map>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
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
public:
	~Rva003A393A();
};

extern "C" const void *const __identifier("??_7TeamRelationMap@@6B@")[];
extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];

// Empty base with inline empty ctor but declared-only dtor: no base call is
// emitted, but the base is unwindable, so retail arms EH state 0 before the
// first member call (ProductionUpdateModuleData precedent, EBO keeps +0).
class Rva003A3959Base
{
public:
	Rva003A3959Base() {}
	// The base is retail's Snapshot: the ctor's unwind funclet 0x007819FA
	// destroys it through 0x0049B47C, the folded Snapshot destructor that
	// restores the Snapshot table 0x00BBB554 and returns. This view keeps
	// the vptr as a member, so the restore is spelled by hand.
	~Rva003A3959Base()
	{
		*(const void *const **)this = __identifier("??_7Snapshot@@6B@");
	}
};

class TeamRelationMap : public Rva003A3959Base
{
public:
	TeamRelationMap();
private:
	const void *m_vtable;
	Rva003A393A m_inner;
};

TeamRelationMap::TeamRelationMap()
	: Rva003A3959Base()
	, m_vtable(__identifier("??_7TeamRelationMap@@6B@"))
{
}
