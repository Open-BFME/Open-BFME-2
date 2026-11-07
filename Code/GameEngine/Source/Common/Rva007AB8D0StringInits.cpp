// cl: /O2 /MD
// Dynamic initializers of file-scope STLport strings, each constructed
// from a literal with a default allocator temporary and registered for
// destruction with atexit. Target evidence: game.dat's __xc_a table points at
// these bodies; each reserves the allocator temporary with `push ecx`, passes
// its address and the literal to the rowed basic_string(const C *, const
// allocator &) constructor (0x00009100 narrow, 0x0000BF20 wide) on the global,
// then registers the matched atexit thunk (Rva007B6880Thunks.cpp) whose
// ecx is the same global. The literals are read from .rdata: "*" (0x00BBBC28),
// "true" (0x00BBC408), "false" (0x00BBC410), "" (0x00BBAC1C) and L""
// (0x00BBB5C4) plus L"true" (0x00BBC418). The owning TUs and the globals' names are not established; the
// RVA names stand in for them. /O2: retail drops the two stack words with
// `add esp, 8`, where /O1 emits `pop ecx` twice.
#include <stdlib.h>

namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};

template <class C> class char_traits;

template <class C, class Tr = char_traits<C>, class A = allocator<C> > class basic_string
{
public:
	__declspec(dllimport) __forceinline basic_string() {} // storage-only definition below; emits nothing
	basic_string( const C *s, const A &a = A() );
private:
	C *m_start;
	C *m_finish;
	C *m_endOfStorage;
};
}

typedef _STL::basic_string<char> NarrowString;
typedef _STL::basic_string<unsigned short> WideString;

void __cdecl rva007B68C0();
void __cdecl rva007B69D0();
void __cdecl rva007B69E0();
void __cdecl rva007B69F0();
void __cdecl rva007B6A00();
void __cdecl rva007B6A10();
void __cdecl rva007B6A20();
void __cdecl rva007B6A30();
void __cdecl rva007B6A40();

// STLport's locale name sentinel (0x009DEB2C), constructed from "*" by the
// initializer below: storage only here, so no compiler initializer is emitted.
namespace _STL { basic_string<char> _Nameless; }
unsigned int g_Va00DDEF08[3];	// retail RVA 0x009DEF08 (.bss), defined here
unsigned g_Va00DDEEFC;	// retail RVA 0x009DEEFC (.bss), defined here
unsigned int g_Va00DDEF14[3];	// retail RVA 0x009DEF14 (.bss), defined here
extern unsigned char g_009DEEF0Static[12];
extern unsigned char g_00DDEF20Static[12];
unsigned int g_Va00DDEEE4[3];	// retail RVA 0x009DEEE4 (.bss), defined here
unsigned g_Va00DDEF38;	// retail RVA 0x009DEF38 (.bss), defined here
// RVA 0x009DEF2C: the 12-byte string storage Rva00017B00StringInit.cpp defines.
extern unsigned char g_00DDEF2CStatic[];

struct Rva007AB8D0StringInits
{
	static void __cdecl rva007AB8D0();
	static void __cdecl rva007ABA00();
	static void __cdecl rva007ABA30();
	static void __cdecl rva007ABA60();
	static void __cdecl rva007ABA90();
	static void __cdecl rva007ABAC0();
	static void __cdecl rva007ABAF0();
	static void __cdecl rva007ABB20();
	static void __cdecl rva007ABB50();
};

void __cdecl Rva007AB8D0StringInits::rva007AB8D0()
{
	( &_STL::_Nameless )->NarrowString::basic_string( "*" );
	atexit( rva007B68C0 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABA00()
{
	( (NarrowString *)&g_Va00DDEF08 )->NarrowString::basic_string( "true" );
	atexit( rva007B69D0 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABA30()
{
	( (NarrowString *)&g_Va00DDEEFC )->NarrowString::basic_string( "false" );
	atexit( rva007B69E0 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABA60()
{
	( (NarrowString *)&g_Va00DDEF14 )->NarrowString::basic_string( "" );
	atexit( rva007B69F0 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABAF0()
{
	( (NarrowString *)&g_Va00DDEEE4 )->NarrowString::basic_string( "" );
	atexit( rva007B6A20 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABB20()
{
	( (NarrowString *)&g_Va00DDEF38 )->NarrowString::basic_string( "" );
	atexit( rva007B6A30 );
}

void __cdecl Rva007AB8D0StringInits::rva007ABB50()
{
	( (WideString *)g_00DDEF2CStatic )->WideString::basic_string( (const unsigned short *)L"" );
	atexit( rva007B6A40 );
}

// The __xc entry at RVA 0x9A4054 points to 0x7ABA90..0x7ABAB3 (35 bytes).
// It constructs L"true" at VA 0xDDEEF0 and registers 0x7B6A00,
// whose cleanup uses the same global. The existing 12-byte storage owner is
// used directly. Copy initializer 0x17B00 later reads this value; its older
// comments calling the initialized global empty are incorrect.
void __cdecl Rva007AB8D0StringInits::rva007ABA90()
{
	( (WideString *)g_009DEEF0Static )->WideString::basic_string( (const unsigned short *)L"true" );
	atexit( rva007B6A00 );
}

// The __xc entry at RVA 0x9A4058 names this 35-byte initializer.
// Its L"false" literal is at VA 0xBBC424; cleanup 0x7B6A10 destroys
// the same existing 12-byte global at VA 0xDDEF20.
void __cdecl Rva007AB8D0StringInits::rva007ABAC0()
{
	( (WideString *)g_00DDEF20Static )->WideString::basic_string( (const unsigned short *)L"false" );
	atexit( rva007B6A10 );
}
