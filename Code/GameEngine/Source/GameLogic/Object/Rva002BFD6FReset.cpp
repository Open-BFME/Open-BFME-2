// cl: /Ireference/shims/bfme2_ascii /MD /O1 /arch:SSE /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002BFD6F@Rva002BFD6F@@QAEXXZ @0x002BFD6F 63B.
// Reset-like __thiscall: zeroes the dword at +0x88, clears the Rva002BF75A
// member at +0xAC via rowed 0x002BF7BE, clears the ArmorTemplate hashtable at
// +0x98 via rowed 0x001DBCDC, then zeroes bytes +0x19/+0x24/+0x25/+0x78/+0x94
// and the float at +0x7C (xorps/movss). Evidence: REL32 callees match this
// TU's own call graph; map typedef copied from neighbour ArmorStoreCtor.cpp
// (same rowed hashtable clear); chain lane: calls 0x002BF7BE now rowed;
// caller is unclaimed 0x0009AB6B 26B which this unblocks.
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

class Rva002BF75A
{
public:
	void rva002BF7BE();
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

class Rva002BFD6F
{
public:
	void rva002BFD6F();

private:
	char m_pad00[0x19];
	unsigned char m_19; // +0x19
	char m_pad1A[0x24 - 0x1A];
	unsigned char m_24; // +0x24
	unsigned char m_25; // +0x25
	char m_pad26[0x78 - 0x26];
	unsigned char m_78; // +0x78
	char m_pad79[0x7C - 0x79];
	float m_7C; // +0x7C
	char m_pad80[0x88 - 0x80];
	unsigned int m_88; // +0x88
	char m_pad8C[0x94 - 0x8C];
	unsigned char m_94; // +0x94
	char m_pad95[0x98 - 0x95];
	ArmorTemplateMap m_map; // +0x98
	Rva002BF75A m_thing; // +0xAC
};

void Rva002BFD6F::rva002BFD6F()
{
	m_88 = 0;
	m_thing.rva002BF7BE();
	m_map.clear();
	m_24 = 0;
	m_25 = 0;
	m_78 = 0;
	m_94 = 0;
	m_19 = 0;
	m_7C = 0.0f;
}
