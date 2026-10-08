// cl: /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
//
// ?rva00238CC2@Rva00238CC2@@QAEXPAVAsciiString@@@Z @0x00238CC2 118B
// __thiscall method building one registry AsciiString from base at +0x50 plus
// literal g_00BBE09C through PlusText 0xB49C5 plus Build 0x5F17C6 plus Build
// 0x5D2F96 plus materializer 0x238C59 then set into dest at [ebp+8]; callers
// at 0x238D3F 0x238D4A 0x238D55 0x238D60 (four AsciiStrings at +4 +8 +c +10).
// Uses shared AsciiString header so tmp dtor calls 0x36410 and set calls
// 0x366F0; concat nodes are size-only TU shims with empty inheritance so
// derived-to-base binds need no copies (retail pushes outer args first).
extern const char g_00BBE09C[];
struct Rva005F17C6S12
{
	int m0, m1, m2;
};
struct AsciiStringPlusText : Rva005F17C6S12
{
};
struct Rva005D2F96S16
{
	int m0, m1, m2, m3;
};
struct Rva005F17C6S16 : Rva005D2F96S16
{
};
struct Rva00238C34
{
	int m0, m1, m2, m3, m4, m5;
	operator AsciiString();
};
struct Rva005D2F96S24 : Rva00238C34
{
};
struct AsciiStringPlusText __cdecl operator+(const AsciiString &left, const char *right);
struct Rva005F17C6S16 __cdecl Rva005F17C6Build(const struct Rva005F17C6S12 &src, int v);
struct Rva005D2F96S24 __cdecl Rva005D2F96Build(const struct Rva005D2F96S16 &src, const char *text);
class Rva00238CC2
{
public:
	int m_00;
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0c;
	AsciiString m_10;
	char m_pad[0x50 - 0x14];
	AsciiString m_50;
	void rva00238CC2(AsciiString *dest);
	void rva00238D38();
};
void Rva00238CC2::rva00238CC2(AsciiString *dest)
{
	dest->setCopyInline((Rva00238C34 &)Rva005D2F96Build(
		(const Rva005D2F96S16 &)Rva005F17C6Build((const Rva005F17C6S12 &)(m_50 + g_00BBE09C), (int)dest),
		g_00BBE09C));
}
//
// ?rva00238D38@Rva00238CC2@@QAEXXZ @0x00238D38 47B
// chain from 0x00238CC2: inits four AsciiStrings at +4 +8 +c +10 via rva00238CC2; caller 0x0004182F.
void Rva00238CC2::rva00238D38()
{
	rva00238CC2(&m_04);
	rva00238CC2(&m_08);
	rva00238CC2(&m_0c);
	rva00238CC2(&m_10);
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_00BBE09C@@3QBDB=??_C@_01KICIPPFI@?2?$AA@")
