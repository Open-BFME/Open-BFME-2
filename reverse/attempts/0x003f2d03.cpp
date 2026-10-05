// ??1Rva003F2D03@@QAE@XZ
// partial score=0.98 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva003F2D03@@QAE@XZ @0x003F2D03 545B
// Large cleanup dtor: two manual DeleteRange clears (basic_string vector at
// +0xfc/0x100, Rva003F0C6C vector at +0x8/0xc, both flag false) then reverse
// member teardown: AsciiString releases, null-checked frees, vector dtors,
// Release_Ref pair, Snapshot vtable restore at +0x78. Evidence: chain lane
// via 0x003F1E87, prev Rva003F2CD6 / next LivingWorldRegionConnectionXfer,
// callee rows 0x3F2BEB 0x3F1E87 0x36410 0x30830 0x3F1797 0x50ED3 0x2CC70,
// vtable g_00BBB554, EH prolog scope 0xb83cbc with states 0x1d..0.
#include <vector>
#include <string>
#include "ascii_string.h"

extern "C" void __cdecl free(void *block);

extern const void *const g_00BBB554[];

class Snapshot78
{
public:
	virtual ~Snapshot78();
};

inline Snapshot78::~Snapshot78()
{
	*(const void **)this = g_00BBB554;
}

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct FreeStore
{
	~FreeStore()
	{
		if (p != 0)
			free(p);
	}
	char *p;
};

struct RefStore
{
	~RefStore()
	{
		if (p != 0)
			p->Release_Ref();
	}
	OpaqueRefCounted *p;
};

struct PtrTriple
{
	~PtrTriple()
	{
		if (start != 0)
			free(start);
	}
	void *start;
	void *finish;
	void *end;
};

class Rva003F0C6C;
struct Rva003F1E87Holder
{
	bool flag;
	void doDelete(Rva003F0C6C *p);
};

bool __cdecl Rva003F2BEBDeleteRange(
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **first,
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **last,
	bool flag);

bool __cdecl Rva003F1E87DeleteRange(Rva003F0C6C **first, Rva003F0C6C **last, Rva003F1E87Holder h);

class LivingWorldRegionConnection;
struct Rva003F1797
{
	~Rva003F1797();
	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_end;
};

class Rva003F2D03
{
public:
	~Rva003F2D03();
private:
	AsciiString m00; // +0x00
	AsciiString m04; // +0x04
	PtrTriple m08; // +0x08 (first/last/end)
	_STL::vector<AsciiString> m14; // +0x14
	AsciiString m20; // +0x20
	AsciiString m24; // +0x24
	AsciiString m28; // +0x28
	AsciiString m2c; // +0x2c
	AsciiString m30; // +0x30
	AsciiString m34; // +0x34
	RefStore m38; // +0x38
	RefStore m3c; // +0x3c
	AsciiString m40; // +0x40
	unsigned char m44_pad[8]; // +0x44
	Rva003F1797 m4c; // +0x4c
	AsciiString m58; // +0x58
	AsciiString m5c; // +0x5c
	FreeStore m60; // +0x60
	unsigned char m64_pad[20]; // +0x64
	Snapshot78 m78; // +0x78
	unsigned char m7c_pad[40]; // +0x7c
	AsciiString ma4; // +0xa4
	FreeStore ma8; // +0xa8
	unsigned char mac_pad[8]; // +0xac
	FreeStore mb4; // +0xb4
	unsigned char mb8_pad[8]; // +0xb8
	FreeStore mc0; // +0xc0
	unsigned char mc4_pad[8]; // +0xc4
	AsciiString mcc; // +0xcc
	FreeStore md0; // +0xd0
	unsigned char md4_pad[8]; // +0xd4
	FreeStore mdc; // +0xdc
	unsigned char me0_pad[8]; // +0xe0
	FreeStore me8; // +0xe8
	unsigned char mec_pad[16]; // +0xec
	PtrTriple mfc; // +0xfc
	unsigned char m108_pad[4]; // +0x108
	AsciiString m10c; // +0x10c
	AsciiString m110; // +0x110
	AsciiString m114; // +0x114
};

// ??1Rva003F2D03@@QAE@XZ present-unmatched
Rva003F2D03::~Rva003F2D03()
{
	{
		void *first = mfc.start;
		Rva003F1E87Holder h1 = Rva003F1E87Holder();
		Rva003F2BEBDeleteRange(
			(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **)first,
			(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **)mfc.finish,
			h1.flag);
	}
	{
		void *first = m08.start;
		Rva003F1E87Holder h2 = Rva003F1E87Holder();
		Rva003F1E87DeleteRange((Rva003F0C6C **)first, (Rva003F0C6C **)m08.finish, h2);
	}
}
