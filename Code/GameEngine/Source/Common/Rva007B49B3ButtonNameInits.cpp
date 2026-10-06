// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Dynamic initializers of three file-scope Rva005E16DA objects, each built
// from a temporary AsciiString of a button name and registered for
// destruction with atexit. Target evidence: game.dat's __xc_a table points
// at 0x007B49B3, 0x007B509A and 0x007B50E7; each builds the temporary with
// StringBase<char>(const char *) at 0x00037BA0, passes its address to the
// constructor at 0x005E16DA on 0x00E06620 / 0x00E06734 / 0x00E06748,
// releases the temporary at 0x00036410 and registers the matched atexit thunk
// that runs ??1Rva005E16DA@@UAE@XZ (0x005E16FD). These call sites are what
// show the constructor's one argument is a const AsciiString & (it forwards it
// to the base 0x00221635, pinned with that signature from 0x005EA635); the
// ledger row's int spelling predates them. The owning TUs and the globals'
// names are not established; the RVA names stand in for them.
#include "ascii_string.h"

extern "C" int __cdecl atexit( void ( __cdecl * )( void ) );

void __cdecl rva007B9734();
void __cdecl rva007B9979();
void __cdecl rva007B9983();

extern unsigned g_Va00E06620;
extern unsigned g_Va00E06734;
extern unsigned g_Va00E06748;

class Rva005E16DA
{
public:
	Rva005E16DA( const AsciiString &name );
};

struct Rva007B49B3ButtonNameInits
{
	static void __cdecl rva007B49B3();
	static void __cdecl rva007B509A();
	static void __cdecl rva007B50E7();
};

void __cdecl Rva007B49B3ButtonNameInits::rva007B49B3()
{
	( (Rva005E16DA *)&g_Va00E06620 )->Rva005E16DA::Rva005E16DA( AsciiString( "ToggleSelectionDetailsButton" ) );
	atexit( rva007B9734 );
}

void __cdecl Rva007B49B3ButtonNameInits::rva007B509A()
{
	( (Rva005E16DA *)&g_Va00E06734 )->Rva005E16DA::Rva005E16DA( AsciiString( "DestroyBuildingButton" ) );
	atexit( rva007B9979 );
}

void __cdecl Rva007B49B3ButtonNameInits::rva007B50E7()
{
	( (Rva005E16DA *)&g_Va00E06748 )->Rva005E16DA::Rva005E16DA( AsciiString( "CancelBuildingConstructionButton" ) );
	atexit( rva007B9983 );
}
