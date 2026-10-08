// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva004121B2@@QAE@XZ @0x004121B2 31B: hash_map-shape default ctor, one more
// twin of 0x00360B99 (and of 0x003A393A): the same 31B pushing 0x64 with three
// empty functor temporaries, calling the Armor-shaped hashtable ctor fold at
// 0x00411AC7 (already rowed as a gen-alias of the Armor hashtable ctor). Its
// only callers are the four file-scope initializers below, whose cleanups
// (rowed 0x007B8247/821F/8229/8233) tear the maps down through three different
// hashtable destructors, so the value types differ and fold here; the owner is
// unknown and the ctor keeps an honest address name. The layout is the Armor
// hashtable's: 0x14 bytes per map, the stride between the four globals.
// The fold keeps its own EH handler operand, so its hashtable ctor is pinned
// under a unique equal_to spelling (the Rva002D0C71Twin convention).
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
	size_t operator()(const T &value) const;
};

}

namespace Rva004121B2Twin
{
template <typename T> struct equal_to
{
	bool operator()(const T &a, const T &b) const;
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

typedef ArmorTemplateMap::value_type ArmorPair004121B2;
typedef ArmorTemplateMap::hasher ArmorHasher004121B2;
typedef Rva004121B2Twin::equal_to<NameKeyType> ArmorEqual004121B2;
typedef ArmorTemplateMap::allocator_type ArmorAlloc004121B2;

typedef _STL::hashtable<
	ArmorPair004121B2,
	NameKeyType,
	ArmorHasher004121B2,
	_STL::_Select1st<ArmorPair004121B2>,
	ArmorEqual004121B2,
	ArmorAlloc004121B2> ArmorHashtable004121B2;

class Rva004121B2
{
public:
	Rva004121B2();
private:
	ArmorHashtable004121B2 m_table;
};

Rva004121B2::Rva004121B2() : m_table(100, ArmorHasher004121B2(), ArmorEqual004121B2(), ArmorAlloc004121B2()) {}

extern "C" int __cdecl atexit(void (__cdecl *)(void));

void __cdecl rva007B8247();
void __cdecl rva007B821F();
void __cdecl rva007B8229();
void __cdecl rva007B8233();

struct BfmeAptScreenRefStorage;
extern BfmeAptScreenRefStorage g_aptScreenReferences;
extern unsigned g_Va00E02FE4;
extern unsigned g_Va00E02FF8;
extern unsigned g_Va00E0300C;

struct Rva004121B2HashMapInits
{
	static void rva007AFF1A();
	static void rva007AFF30();
	static void rva007AFF46();
	static void rva007AFF5C();
};

// 0x007AFF1A (22B): Rva004121B2() on VA 0x00E02FD0, atexit(0x007B8247 -> hashtable dtor 0x004111CC)
void Rva004121B2HashMapInits::rva007AFF1A()
{
	( (Rva004121B2 *)&g_aptScreenReferences )->Rva004121B2::Rva004121B2();
	atexit( rva007B8247 );
}

// 0x007AFF30 (22B): Rva004121B2() on VA 0x00E02FE4, atexit(0x007B821F -> hashtable dtor 0x00410C42)
void Rva004121B2HashMapInits::rva007AFF30()
{
	( (Rva004121B2 *)&g_Va00E02FE4 )->Rva004121B2::Rva004121B2();
	atexit( rva007B821F );
}

// 0x007AFF46 (22B): Rva004121B2() on VA 0x00E02FF8, atexit(0x007B8229 -> hashtable dtor 0x00410C7B)
void Rva004121B2HashMapInits::rva007AFF46()
{
	( (Rva004121B2 *)&g_Va00E02FF8 )->Rva004121B2::Rva004121B2();
	atexit( rva007B8229 );
}

// 0x007AFF5C (22B): Rva004121B2() on VA 0x00E0300C, atexit(0x007B8233 -> hashtable dtor 0x00410C7B)
void Rva004121B2HashMapInits::rva007AFF5C()
{
	( (Rva004121B2 *)&g_Va00E0300C )->Rva004121B2::Rva004121B2();
	atexit( rva007B8233 );
}
