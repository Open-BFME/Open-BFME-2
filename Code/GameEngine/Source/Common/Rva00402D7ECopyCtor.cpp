// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// Rva00402D7E retail 0x00402C8A..0x00402E30: dtor 119B, copyItems 125B,
// copy ctor 109B, operator= 69B.
// Evidence: the three-handle sibling of Rva00403055 (Rva00403055CopyCtor.cpp).
// Same string at +0, owned pointer vector at +4 and nothrow handles, here at
// +0x10, +0x14 and +0x18. Elements are new'd at 0x64 bytes through the rowed
// Rva00402C0F copy ctor 0x00402C0F. The dtor calls clearItems 0x00402C4E, the
// body Rva00403055 also calls, since both element dtors fold to the same tail
// jump. Names are generated.
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

#include <vector>

#include "string_base.h"

#include "ascii_string.h"

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Release_Ref();
private:
	long refs;
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
	OpaqueRefElement4 &rva00239057(const OpaqueRefElement4 *other);
};

class Rva0036CA00Str : public OpaqueRefElement4
{
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (referent) referent->Release_Ref(); }
};

class Rva00402C0F
{
public:
	Rva00402C0F(const Rva00402C0F &src);
private:
	char m_bytes[0x64];
};

class Rva00402D7E
{
public:
	Rva00402D7E(const Rva00402D7E &other);
	~Rva00402D7E();
	Rva00402D7E &operator=(const Rva00402D7E &other);
	void clearItems();
	void copyItems(const Rva00402D7E &other);

private:
	AsciiString m_name;
	_STL::vector<Rva00402C0F *> m_items;
	Rva0036CA00Str m_at10;
	Rva0036CA00Str m_at14;
	Rva0036CA00Str m_at18;
};

Rva00402D7E::Rva00402D7E(const Rva00402D7E &other)
	: m_name(other.m_name), m_items(), m_at10(other.m_at10), m_at14(other.m_at14), m_at18(other.m_at18)
{
	copyItems(other);
}

Rva00402D7E::~Rva00402D7E()
{
	clearItems();
}

Rva00402D7E &Rva00402D7E::operator=(const Rva00402D7E &other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_at10 = other.m_at10;
		m_at14 = other.m_at14;
		m_at18 = other.m_at18;
		copyItems(other);
	}
	return *this;
}

void Rva00402D7E::copyItems(const Rva00402D7E &other)
{
	clearItems();
	m_items.reserve(other.m_items.size());
	_STL::vector<Rva00402C0F *>::const_iterator it = other.m_items.begin();
	_STL::vector<Rva00402C0F *>::const_iterator end = other.m_items.end();
	for (; it != end; ++it)
		m_items.push_back(new Rva00402C0F(**it));
}
