// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1Rva0031763A@@QAE@XZ @0x003175D1 105B, ??0Rva0031763A@@QAE@XZ @0x0031763A 127B,
// ??4Rva0031763A@@QAEAAV0@ABV0@@Z @0x00317779 115B. Honest-address ctor/dtor/copy-assign
// trio for the same 0x2C-byte value struct used as a local in FUN_007177ec and
// FUN_008115a9 (Apt/Window layout-block parsing): 5 dwords at +0x00..+0x10 zeroed,
// 5 AsciiStrings at +0x14..+0x24, _STL::list<int> at +0x28.
// - dtor destroys list via rowed _List_base dtor 0x4EC395 then 5 Strings via pinned
//   0x36410 (both ??1AsciiString and ??1StringBase fold there), EH states 4..0 + -1.
// - ctor mem-inits 5 ints to 0, 3 Strings from AsciiString::TheEmptyString (0x9E0878)
//   via pinned copy 0x365F0 (AsciiString and StringBase spellings fold there), 2 Strings
//   default-zeroed inline, list via rowed _List_base ctor 0x4EC36C, body clears list via
//   rowed 0x23DAA5; EH states mirror the dtor and the StringBase-forwarder gives the
//   retail lea-before-push order (probe-proven: simple AsciiString model misorders).
// - assign copies 5 dwords then 5 Strings via pinned assign 0x366F0 then list via rowed
//   list assign 0x2C54EE, ret 4.
// Identity: honest Rva0031763A (ctor address); class layout proven by the assign body
// (5x dword + 5x String assign + list assign) and by FUN_007177ec setting +0x14..+0x20
// to "APT:None" and inserting into +0x28. Callers: ctor from 0x3176D3/0x317843/
// 0x4116C0/0x411709, dtor from 0x317755/0x3179E6/0x4116F7/0x411746 plus Unwind funclets,
// assign sole-called from 0x317B1D. Flags: neighbour parseDrawCallback /O1 /DNDEBUG /MD
// /EHsc plus /D_STLP_USE_STATIC_LIB for list<int> (ProductionUpdateCtor precedent);
// shims with /D_CRTIMP=/bfmealloc/bfmelist collapse the dtor EH to max 3 (probe-proven).
// No BFME1 donor; non-virtual QAE (no vptr stores).

#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}


#include "ascii_string.h"


class Rva0031763A
{
public:
	Rva0031763A();
	~Rva0031763A();
	Rva0031763A &operator=(const Rva0031763A &that);
private:
	int m_unk00; // +0x00
	int m_unk04; // +0x04
	int m_unk08; // +0x08
	int m_unk0C; // +0x0C
	int m_unk10; // +0x10
	AsciiString m_s14; // +0x14
	AsciiString m_s18; // +0x18
	AsciiString m_s1C; // +0x1C
	AsciiString m_s20; // +0x20
	AsciiString m_s24; // +0x24
	_STL::list<int, _STL::allocator<int> > m_list28; // +0x28
};

Rva0031763A::Rva0031763A() :
	m_unk00(0),
	m_unk04(0),
	m_unk08(0),
	m_unk0C(0),
	m_unk10(0),
	m_s14(AsciiString::TheEmptyString),
	m_s18(AsciiString::TheEmptyString),
	m_s1C(AsciiString::TheEmptyString)
{
	m_list28.clear();
}

// ??1Rva0031763A@@QAE@XZ @0x003175D1
Rva0031763A::~Rva0031763A()
{
}

Rva0031763A &Rva0031763A::operator=(const Rva0031763A &that)
{
	m_unk00 = that.m_unk00;
	m_unk04 = that.m_unk04;
	m_unk08 = that.m_unk08;
	m_unk0C = that.m_unk0C;
	m_unk10 = that.m_unk10;
	m_s14 = that.m_s14;
	m_s18 = that.m_s18;
	m_s1C = that.m_s1C;
	m_s20 = that.m_s20;
	m_s24 = that.m_s24;
	m_list28 = that.m_list28;
	return *this;
}
