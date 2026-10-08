// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ??0Rva00403055@@QAE@ABV0@@Z retail 0x00403055 97B.
// Evidence: copies the string at +0 through the rowed StringBase copy ctor
// 0x000365F0, builds an empty pointer vector at +4 through the shared
// _Vector_base ctor 0x00211E58, copies the two handles at +0x10 and +0x14
// through the rowed nothrow Rva0036CA00Str copy ctor 0x000A8C7C, then calls
// 0x00402FD8 with the source. That 125-byte routine clears the vector,
// reserves the source's count and push_backs a new 0x5C-byte copy of each
// element, so the vector holds owned pointers. Unwind states 0 and 3 bracket
// the nothrow member copies. The snapped-boundary queue named it
// GrantStealthBehaviorModuleData's ctor; names here are generated.
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

class Rva003F9FE6
{
public:
	virtual void v00() = 0;
	Rva003F9FE6(const Rva003F9FE6 &src);
private:
	AsciiString m_04;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_08;
	AsciiString m_14;
	AsciiString m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_55;
	unsigned char m_56;
};

class Rva00402F28Item : public Rva003F9FE6
{
public:
	virtual void v00();
	Rva00402F28Item(const Rva00402F28Item &other);
	~Rva00402F28Item();
private:
	unsigned char m_58;
	unsigned char m_59;
	unsigned char m_5A;
};

class Rva00403055
{
public:
	Rva00403055(const Rva00403055 &other);
	~Rva00403055();
	Rva00403055 &operator=(const Rva00403055 &other);
	void clearItems();
	void copyItems(const Rva00403055 &other);

private:
	AsciiString m_name;
	_STL::vector<Rva00402F28Item *> m_items;
	Rva0036CA00Str m_at10;
	Rva0036CA00Str m_at14;
};

Rva00403055::Rva00403055(const Rva00403055 &other)
	: m_name(other.m_name), m_items(), m_at10(other.m_at10), m_at14(other.m_at14)
{
	copyItems(other);
}

void Rva00403055::copyItems(const Rva00403055 &other)
{
	clearItems();
	m_items.reserve(other.m_items.size());
	_STL::vector<Rva00402F28Item *>::const_iterator it = other.m_items.begin();
	_STL::vector<Rva00402F28Item *>::const_iterator end = other.m_items.end();
	for (; it != end; ++it)
		m_items.push_back(new Rva00402F28Item(**it));
}

Rva00403055::~Rva00403055()
{
	clearItems();
}

void Rva00403055::clearItems()
{
	_STL::vector<Rva00402F28Item *>::iterator it = m_items.begin();
	_STL::vector<Rva00402F28Item *>::iterator end = m_items.end();
	for (; it != end; ++it)
		delete *it;
	m_items.clear();
}

Rva00402F28Item::Rva00402F28Item(const Rva00402F28Item &other)
	: Rva003F9FE6(other)
{
	m_58 = other.m_58;
	m_59 = other.m_59;
	m_5A = other.m_5A;
}

Rva00403055 &Rva00403055::operator=(const Rva00403055 &other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_at10 = other.m_at10;
		m_at14 = other.m_at14;
		copyItems(other);
	}
	return *this;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?clearItems@Rva00402D7E@@QAEXXZ=?clearItems@Rva00403055@@QAEXXZ")
