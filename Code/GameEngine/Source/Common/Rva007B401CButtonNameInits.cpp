// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Dynamic initializers of two file-scope objects whose constructor is
// expanded in place. Target evidence: game.dat's __xc_a table points at
// 0x007B401C and 0x007B4081; each builds a temporary AsciiString of a button
// name with StringBase<char>(const char *) at 0x00037BA0, passes it to the
// pinned base constructor ??0Rva00221635@@QAE@ABVAsciiString@@@Z (0x00221635)
// on 0x00E062FC / 0x00E0630C, zeroes the words at +0x08 and +0x0C, stores
// the class table 0x00C6E3A8 at +0 last, releases the temporary at
// 0x00036410 and registers the matched atexit thunk that runs
// ??1Rva00574499@@QAE@XZ. Each funcinfo's unwind map holds one state (the
// temporary), so the expanded constructor adds none. Scalar members set in
// the mem-initializer list put the zero stores before the table store, the
// order retail has (the Rva005E16DA.cpp finding, read the other way round).
// The owning TU, class and member names are not established; the RVA names
// stand in for them.
#include "ascii_string.h"

extern "C" int __cdecl atexit( void ( __cdecl * )( void ) );

void __cdecl rva007B94AA();
void __cdecl rva007B94B4();

extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;

class Rva00221635
{
public:
	Rva00221635( const AsciiString &name );
	virtual void Rva00221635_pure() = 0; // vptr at +0
	int m_4;                             // +0x04
};

class Rva007B401CButton : public Rva00221635
{
	void *m_8; // +0x08
	void *m_c; // +0x0C

public:
	__forceinline Rva007B401CButton( const AsciiString &name ) : Rva00221635( name ), m_8( 0 ), m_c( 0 ) {}
	virtual void Rva007B401CButton_pure();
};

struct Rva007B401CButtonNameInits
{
	static void __cdecl rva007B401C();
	static void __cdecl rva007B4081();
};

void __cdecl Rva007B401CButtonNameInits::rva007B401C()
{
	( (Rva007B401CButton *)&g_Va00E062FC )->Rva007B401CButton::Rva007B401CButton( AsciiString( "OptionsButton" ) );
	atexit( rva007B94AA );
}

void __cdecl Rva007B401CButtonNameInits::rva007B4081()
{
	( (Rva007B401CButton *)&g_Va00E0630C )->Rva007B401CButton::Rva007B401CButton( AsciiString( "ObjectivesButton" ) );
	atexit( rva007B94B4 );
}
