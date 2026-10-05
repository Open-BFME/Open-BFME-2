// cl: /O1 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// Rva003FA26F retail 0x003FA14B..0x003FA381: dtor 167B, copyItems 125B,
// copy ctor 157B, operator= 117B.
// Evidence: the six-handle sibling of Rva00403055 and Rva00402D7E. Handles
// sit at +0x10..+0x24 and two plain ints at +0x28/+0x2C. Elements are new'd
// at 0x60 bytes through the rowed Rva003FA118 copy ctor 0x003FA118. The dtor
// calls the shared clearItems 0x00402C4E. Names are generated.
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

class Rva003FA118
{
public:
	Rva003FA118(const Rva003FA118 &src);
private:
	char m_bytes[0x60];
};

class Rva003FA26F
{
public:
	Rva003FA26F(const Rva003FA26F &other);
	~Rva003FA26F();
	Rva003FA26F &operator=(const Rva003FA26F &other);
	void clearItems();
	void copyItems(const Rva003FA26F &other);

private:
	AsciiString m_name;
	_STL::vector<Rva003FA118 *> m_items;
	Rva0036CA00Str m_at10;
	Rva0036CA00Str m_at14;
	Rva0036CA00Str m_at18;
	Rva0036CA00Str m_at1C;
	Rva0036CA00Str m_at20;
	Rva0036CA00Str m_at24;
	int m_28;
	int m_2C;
};

Rva003FA26F::Rva003FA26F(const Rva003FA26F &other)
	: m_name(other.m_name), m_items(), m_at10(other.m_at10), m_at14(other.m_at14), m_at18(other.m_at18),
	  m_at1C(other.m_at1C), m_at20(other.m_at20), m_at24(other.m_at24), m_28(other.m_28), m_2C(other.m_2C)
{
	copyItems(other);
}

Rva003FA26F::~Rva003FA26F()
{
	clearItems();
}

Rva003FA26F &Rva003FA26F::operator=(const Rva003FA26F &other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_at10 = other.m_at10;
		m_at14 = other.m_at14;
		m_at18 = other.m_at18;
		m_at1C = other.m_at1C;
		m_at20 = other.m_at20;
		m_at24 = other.m_at24;
		m_28 = other.m_28;
		m_2C = other.m_2C;
		copyItems(other);
	}
	return *this;
}

void Rva003FA26F::copyItems(const Rva003FA26F &other)
{
	clearItems();
	m_items.reserve(other.m_items.size());
	_STL::vector<Rva003FA118 *>::const_iterator it = other.m_items.begin();
	_STL::vector<Rva003FA118 *>::const_iterator end = other.m_items.end();
	for (; it != end; ++it)
		m_items.push_back(new Rva003FA118(**it));
}

// ?clearItems@Rva003FA26F@@QAEXXZ present-unmatched
void Rva003FA26F::clearItems()
{
	_STL::vector<Rva003FA118 *>::iterator it = m_items.begin();
	_STL::vector<Rva003FA118 *>::iterator end = m_items.end();
	for (; it != end; ++it)
		delete *it;
	m_items.clear();
}
