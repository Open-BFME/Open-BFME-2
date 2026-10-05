// cl: /O2 /MD
// Dynamic initializers of seven file-scope STLport strings, each constructed
// from a literal with a default allocator temporary and registered for
// destruction with atexit. Target evidence: game.dat's __xc_a table points at
// these bodies; each reserves the allocator temporary with `push ecx`, passes
// its address and the literal to the rowed basic_string(const C *, const
// allocator &) constructor (0x00009100 narrow, 0x0000BF20 wide) on the global,
// then registers the matched atexit thunk (Rva007B6880Thunks.cpp) whose
// ecx is the same global. The literals are read from .rdata: "*" (0x00BBBC28),
// "true" (0x00BBC408), "false" (0x00BBC410), "" (0x00BBAC1C) and L""
// (0x00BBB5C4). The owning TUs and the globals' names are not established; the
// RVA names stand in for them. /O2: retail drops the two stack words with
// `add esp, 8`, where /O1 emits `pop ecx` twice.
extern "C" int __cdecl atexit( void ( __cdecl * )( void ) );

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
	basic_string( const C *s, const A &a = A() );
};
}

typedef _STL::basic_string<char> NarrowString;
typedef _STL::basic_string<unsigned short> WideString;

void __cdecl rva007B68C0();
void __cdecl rva007B69D0();
void __cdecl rva007B69E0();
void __cdecl rva007B69F0();
void __cdecl rva007B6A20();
void __cdecl rva007B6A30();
void __cdecl rva007B6A40();

extern unsigned g_Va00DDEB2C;
extern unsigned g_Va00DDEF08;
extern unsigned g_Va00DDEEFC;
extern unsigned g_Va00DDEF14;
extern unsigned g_Va00DDEEE4;
extern unsigned g_Va00DDEF38;
extern unsigned g_Va00DDEF2C;

struct Rva007AB8D0StringInits
{
	static void __cdecl rva007AB8D0();
	static void __cdecl rva007ABA00();
	static void __cdecl rva007ABA30();
	static void __cdecl rva007ABA60();
	static void __cdecl rva007ABAF0();
	static void __cdecl rva007ABB20();
	static void __cdecl rva007ABB50();
};

void __cdecl Rva007AB8D0StringInits::rva007AB8D0()
{
	( (NarrowString *)&g_Va00DDEB2C )->NarrowString::basic_string( "*" );
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
	( (WideString *)&g_Va00DDEF2C )->WideString::basic_string( (const unsigned short *)L"" );
	atexit( rva007B6A40 );
}
