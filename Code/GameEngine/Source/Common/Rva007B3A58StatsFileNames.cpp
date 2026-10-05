// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Dynamic initializers of two file-scope UnicodeString globals, each built
// from a temporary AsciiString of a stats .ini name and registered for
// destruction with atexit. Target evidence: game.dat's __xc_a table points
// at 0x007B3A58 and 0x007B3AA5; each builds the temporary with
// StringBase<char>(const char *) at 0x00037BA0, converts it through
// UnicodeString(const AsciiString &) at 0x006CB6D0 into 0x00E05E00 /
// 0x00E05E04, releases the temporary at 0x00036410 and registers the matched
// atexit thunk that jumps to ~UnicodeString at 0x005B804E. The owning TU and
// the globals' names are not established; the RVA names stand in for them.
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" int __cdecl atexit( void ( __cdecl * )( void ) );

void __cdecl rva007B92B6();
void __cdecl rva007B92C0();

extern unsigned g_Va00E05E00;
extern unsigned g_Va00E05E04;

struct Rva007B3A58StatsFileNames
{
	static void __cdecl rva007B3A58();
	static void __cdecl rva007B3AA5();
};

void __cdecl Rva007B3A58StatsFileNames::rva007B3A58()
{
	( (UnicodeString *)&g_Va00E05E00 )->UnicodeString::UnicodeString( AsciiString( "RealTimeStats.ini" ) );
	atexit( rva007B92B6 );
}

void __cdecl Rva007B3A58StatsFileNames::rva007B3AA5()
{
	( (UnicodeString *)&g_Va00E05E04 )->UnicodeString::UnicodeString( AsciiString( "StrategicStats.ini" ) );
	atexit( rva007B92C0 );
}
