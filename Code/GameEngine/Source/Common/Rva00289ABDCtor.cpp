// cl: /Ireference/shims/bfme2_ascii /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00289ABD@@QAE@XZ retail 0x00289ABD 263 bytes v3.
// Ctor with baseConstruct then vector<BfmeE16> at +0x14 plus bool at +0x24 plus map at +0x28,
// new Rva00288BBA NOTFOUND then push 1.0f onto its ModuleData vector then two new Armor hash_maps.
// Evidence: rowed baseConstruct 0x001B4E63 plus Vector_base<BfmeE16> 0x00211E58 plus map 0x0033C432
// plus StringBase PBD 0x00037BA0 plus Rva00288BBA 0x00288BBA plus push_back ModuleData 0x004DFCB0
// plus hash_map default 0x002898E3 times two plus float g_Va00BBB8D8; vtable 0x007FB8F4.
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

#include "ascii_string.h"
#include <vector>
#include <map>
#include <hash_map>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

inline bool operator==(const ArmorTemplate &x, const ArmorTemplate &y)
{
	return x.m_damageCoefficient[0] == y.m_damageCoefficient[0];
}

namespace rts
{

template <class _Key>
struct hash
{
};

template <>
struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &key) const
	{
		const unsigned int *words = (const unsigned int *)&key;
		return (words[1] << 16) + words[0];
	}
};

template <class _Key>
struct equal_to
{
	bool operator()(const _Key &left, const _Key &right) const
	{
		return left == right;
	}
};

}

typedef _STL::hash_map<NameKeyType, ArmorTemplate, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > ArmorRtsMap;

struct BfmeE16 { float x, y, z, w; };

class ModuleData;

class Rva00288BBA
{
public:
	_STL::vector<const ModuleData *> m_vec;
	AsciiString m_str;
	Rva00288BBA(const AsciiString &s);
};

extern const float g_Va00BBB8D8;

class __declspec(novtable) BFME2NativeNetwork
{
public:
	__forceinline BFME2NativeNetwork() { baseConstruct(); }
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
	void baseConstruct();
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

class Rva00289ABD : public BFME2NativeNetwork
{
public:
	Rva00289ABD();
	ArmorRtsMap *m_hash0C;
	ArmorRtsMap *m_hash10;
	_STL::vector<BfmeE16> m_vec14;
	Rva00288BBA *m_rva20;
	unsigned char m_b24;
	_STL::map<int, void *> m_map28;
};
Rva00289ABD::Rva00289ABD()
	: m_vec14(_STL::allocator<BfmeE16>()), m_b24(0)
{
	m_rva20 = new Rva00288BBA("NOTFOUND_DEFAULT_ScalarTable");
	float f = g_Va00BBB8D8;
	((_STL::vector<const ModuleData *> *)m_rva20)->push_back(*(const ModuleData **)&f);
	m_hash0C = new ArmorRtsMap;
	m_hash10 = new ArmorRtsMap;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_Va00BBB8D8@@3MB=?g_Va00BBB8D8@@3MA")
