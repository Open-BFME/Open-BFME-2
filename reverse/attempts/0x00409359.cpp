// ??4CreateAHeroData@@QAEAAV0@ABV0@@Z
// partial score=0.97 date=2026-10-09
// ??4CreateAHeroData@@QAEAAV0@ABV0@@Z
// Trial: preserve existing setter definitions before the caller so cl observes ECX.
// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4CreateAHeroData@@QAEAAV0@ABV0@@Z @0x00409359 254B
// Evidence: unlock lane; CreateAHeroData 0x140 layout from matched copy ctor
// 0x00409D4D and dtor 0x00409285 with vtable C38D88; callees all rowed
// (setters 407A6A 407004 406EFD 406F12 406F27 406F3C, vector/tree assigns,
// BfmeHeroElement assign 406E22); callers 40A384 2DBAB9 5B5C02 5B2725 21A428 3FF50C 5B1E71.
#include <memory>
#include <vector>
#include <map>

#include "ascii_string.h"
#include "unicode_string.h"
class Xfer;
class Snapshot {
public:
    __forceinline virtual ~Snapshot() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
struct TreeHintPayload001F8ACB { unsigned int value; };
bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::map<int,int> IntegerMap;
typedef _STL::map<AsciiString,TreeHintPayload001F8ACB> StringPayloadMap;
typedef _STL::map<int,_STL::vector<unsigned int> > IntegerVectorMap;
struct BfmeHeroElement005C39DE {
    AsciiString text;
    unsigned int word4, word8;
    BfmeHeroElement005C39DE();
    BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &);
};
// ?rva00406EFD@Rva00406EFD@@QAE_NH@Z @0x00406EFD 21B: conditional setter comparing stack arg with +0x10 and setting bit 2 at +0x38. Caller 0x00407012 passes 0. Owner unknown so honest-address name.
// ?rva00407004@Rva00406EFD@@QAE_NH@Z @0x00407004 28B: when the argument
// differs from +0x0C, stores it, calls rva00406EFD(0) and ORs 0xEF into the
// flags at +0x38 (cl narrows the dword OR to a byte); returns true. Caller
// 0x0040937F. Retail keeps this in ecx across the rva00406EFD call, which cl
// only does when that callee was compiled earlier in the same TU.
class Rva00406EFD
{
	int m_00[3];
	int m_0c;
	int m_10;
	int m_14[9];
	int m_38;
public:
	bool rva00406EFD(int v);
	bool rva00407004(int v);
};
bool Rva00406EFD::rva00406EFD(int v)
{
	if (v != m_10) {
		m_38 |= 2;
		m_10 = v;
	}
	return true;
}
bool Rva00406EFD::rva00407004(int v)
{
	if (v != m_0c) {
		m_0c = v;
		rva00406EFD(0);
		m_38 |= 0xEF;
	}
	return true;
}

// ?rva00406F12@Rva00406F12@@QAE_NH@Z @0x00406F12 21B: conditional setter comparing +0x2C and setting bit 8 at +0x38. Sibling of 0x00406EFD. Owner unknown so honest-address name.
class Rva00406F12
{
	int m_00[11];
	int m_2C;
	int m_30[2];
	int m_38;
public:
	bool rva00406F12(int v);
};
bool Rva00406F12::rva00406F12(int v)
{
	if (m_2C != v) {
		m_38 |= 8;
		m_2C = v;
	}
	return true;
}

// ?rva00406F27@Rva00406F27@@QAE_NH@Z @0x00406F27 21B: conditional setter comparing +0x30 and setting bit 8 at +0x38. Sibling of 0x00406F12. Owner unknown so honest-address name.
class Rva00406F27
{
	int m_00[12];
	int m_30;
	int m_34;
	int m_38;
public:
	bool rva00406F27(int v);
};
bool Rva00406F27::rva00406F27(int v)
{
	if (m_30 != v) {
		m_38 |= 8;
		m_30 = v;
	}
	return true;
}

// ?rva00406F3C@Rva00406F3C@@QAE_NH@Z @0x00406F3C 21B: conditional setter comparing +0x34 and setting bit 8 at +0x38. Sibling of 0x00406F27. Owner unknown so honest-address name.
class Rva00406F3C
{
	int m_00[13];
	int m_34;
	int m_38;
public:
	bool rva00406F3C(int v);
};
bool Rva00406F3C::rva00406F3C(int v)
{
	if (m_34 != v) {
		m_38 |= 8;
		m_34 = v;
	}
	return true;
}

class Rva00407A6A {public:bool rva00407A6A(const UnicodeString &);};
class CreateAHeroData : public Snapshot {
    unsigned int word04;
    UnicodeString text08;
    unsigned int word0C, word10;
    IntegerMap map14, map20;
    unsigned int word2C, word30, word34, word38;
    _STL::vector<AsciiString> strings3C;
    unsigned char flag48;
    AsciiString text4C;
    StringPayloadMap map50;
    _STL::vector<bool> bits5C;
    unsigned char flag70, flag71;
    IntegerVectorMap map74;
    BfmeHeroElement005C39DE elements80[15];
    unsigned int word134, word138, word13C;
public:
    CreateAHeroData &operator=(const CreateAHeroData &o);
    virtual ~CreateAHeroData();
};
CreateAHeroData &CreateAHeroData::operator=(const CreateAHeroData &o)
{
    if (this != &o) {
        word04 = o.word04;
        ((Rva00407A6A *)this)->rva00407A6A(o.text08);
        ((Rva00406EFD *)this)->rva00407004(o.word0C);
        ((Rva00406EFD *)this)->rva00406EFD(o.word10);
        map14 = o.map14;
        map20 = o.map20;
        ((Rva00406F12 *)this)->rva00406F12(o.word2C);
        ((Rva00406F27 *)this)->rva00406F27(o.word30);
        ((Rva00406F3C *)this)->rva00406F3C(o.word34);
        word38 |= 0xE4;
        strings3C = o.strings3C;
        flag48 = o.flag48;
        text4C = o.text4C;
        map50 = o.map50;
        bits5C = o.bits5C;
        flag70 = 0;
        flag71 = o.flag71;
        map74 = o.map74;
        word134 = o.word134;
        word138 = o.word138;
        word13C = o.word13C;
        for (int i = 0; i < 15; ++i)
            elements80[i] = o.elements80[i];
    }
    return *this;
}
