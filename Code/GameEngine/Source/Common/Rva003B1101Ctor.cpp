// cl: /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva003B1101 default ctor, retail 0x003B140E (284B):
// Default ctor for Rva003B1101 (vtable 0x00C1ED18, dtor at 0x003B1101,
// assign at 0x003B1337). Empty Rva001E3624 base (inline ctor,
// declared-only dtor pins EH state 0), all scalar/string/vector-base
// defaults in mem-init in declaration order so they emit interleaved
// with the Rva ctors and bitset reset (whose user ctor calls reset).
// FixedStorage initFromStorages plus Science vector erase in body.
// Evidence: gap lane between assign and deleting dtor, same vtable,
// all callees rowed or pinned, callers 0x003B164F/0x003B1699/0x003B1751.
// Retail's unwind map: base 0x001E3624 (virtual dtor, so the base holds the
// vptr and its fields sit at +4/+8/+0xC), strings at +0x10/+0x3C/+0x40/
// +0x5C, the vector at +0x24, two ref-counted handles at +0x34/+0x38 (dtor
// 0x0010F149 releases through Release_Ref) and the Rva003623E5 members at
// +0x60/+0x78. The banked attempt had a non-polymorphic base, an explicit
// vtable member and plain ints at +0x34/+0x38.
#include <vector>

typedef int Int;

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva001E3624
{
public:
	Rva001E3624() : m_04(0), m_08(0), m_0c(-1) {}
	virtual ~Rva001E3624();
private:
	Int m_04; // +0x04
	unsigned char m_08; // +0x08
	Int m_0c; // +0x0C
};

class AsciiString
{
public:
	AsciiString(int zero) : m_data(reinterpret_cast<void *>(zero)) {}
	~AsciiString();
private:
	void *m_data;
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(class BfmeFixedStorage0004543D first, class BfmeFixedStorage0004543D second);
private:
	Int m_x;
};

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	unsigned char m_bytes[28];
};

namespace _STL
{
template <unsigned _Bits>
class bitset
{
public:
	bitset() { reset(); }
	bitset<_Bits> &reset();
private:
	unsigned long m_words[(_Bits + 31) / 32];
};
}

extern Int g_Va00DBA4E4;
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;

class Rva003B1101Ref
{
public:
	Rva003B1101Ref() : m_ptr(0) {}
	~Rva003B1101Ref();
private:
	void *m_ptr;
};
class Rva003B1101 : public Rva001E3624
{
public:
	Rva003B1101();
	virtual ~Rva003B1101();
private:
	AsciiString m_10; // +0x10
	Int m_14; // +0x14
	Int m_18; // +0x18
	Int m_1c; // +0x1C
	Int m_20; // +0x20
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_24; // +0x24
	Int m_30; // +0x30
	Rva003B1101Ref m_34; // +0x34
	Rva003B1101Ref m_38; // +0x38
	AsciiString m_3c; // +0x3C
	AsciiString m_40; // +0x40
	Int m_44; // +0x44
	Int m_48; // +0x48
	Int m_4c; // +0x4C
	float m_50; // +0x50
	float m_54; // +0x54
	unsigned char m_58; // +0x58
	unsigned char m_59; // +0x59
	AsciiString m_5c; // +0x5C
	Rva003623E5Member m_60; // +0x60
	_STL::bitset<128> m_64; // +0x64
	float m_74; // +0x74
	Rva003623E5Member m_78; // +0x78
	float m_7c; // +0x7C
};

Rva003B1101::Rva003B1101()
	: Rva001E3624()
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_1c(0)
	, m_20(0)
	, m_30(0)
	, m_3c(0)
	, m_40(0)
	, m_44(-1)
	, m_48(g_Va00DBA4E4 * 10)
	, m_4c(0)
	, m_50(0.0f)
	, m_54(0.0f)
	, m_58(0)
	, m_59(0)
	, m_5c(0)
	, m_74(0.0f)
	, m_7c(0.0f)
{
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > &vec24 = m_24;
	m_60.initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
	vec24.erase(vec24.begin(), vec24.end());
	m_78.initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_defaultStorage009FEFA4@@3VBfmeFixedStorage0004543D@@B=?g_00DFEFA4StoragePrototype@@3PAEA")
