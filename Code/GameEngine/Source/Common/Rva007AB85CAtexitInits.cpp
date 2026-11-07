// cl: /Ireference/shims/bfme2_ascii /MD
//
// Dynamic initializers from the 0x007AB7DA strip whose atexit cleanup is
// already rowed: the 12-byte ones only register the cleanup (the object's
// constructor folded away), the 27-byte ones first construct a file-scope
// AsciiString from its literal through the out-of-line AsciiString(const
// char *) at 0x0000654A. Each is the compiler-generated initializer of one
// translation unit's file-scope object; the owning TUs are unrecovered, so
// each initializer keeps its address name. Globals with no recovered owner
// are defined here: zero-filled 4-byte slots holding the AsciiString pointer.
// The live camera mode slot has a descriptive name; its original name is unknown.

#include <stdlib.h>
#include "ascii_string.h"

void __cdecl rva007B6C9B();
void __cdecl rva007B6F5C();
void __cdecl rva007B6F98();
void __cdecl rva007B7024();
void __cdecl rva007B7090();
void __cdecl rva007B70A0();
void __cdecl rva007B7270();
void __cdecl rva007B7300();
void __cdecl rva007B7340();
void __cdecl rva007B7380();
void __cdecl rva007B76E6();
void __cdecl rva007B770E();
void __cdecl rva007B796E();
void __cdecl rva007B7979();
void __cdecl rva007B7DB3();
void __cdecl rva007B7E49();
void __cdecl rva007B80A1();
void __cdecl rva007B8119();
void __cdecl rva007B8123();
void __cdecl rva007B9B40();

// VA 0x00DEC290: zero-initialized AsciiString storage, explicitly constructed below.
unsigned BfmeLiveCameraModeNameStorage;
unsigned g_Va00DEC3B8;	// retail RVA 0x009EC3B8 (.bss), defined here
unsigned g_Va00DFF030;
unsigned g_Va00E022E8;
unsigned g_Va00E028C4;
unsigned g_Va00E02D68;
unsigned g_Va00E02E70;
unsigned g_Va00E02E74;

struct Rva007AB85CAtexitInits
{
	static void rva007AC25C();
	static void rva007ACAAA();
	static void rva007ACB5D();
	static void rva007ACCA6();
	static void rva007ACD90();
	static void rva007ACDA0();
	static void rva007ACE80();
	static void rva007ACED0();
	static void rva007ACEE0();
	static void rva007ACEF0();
	static void rva007ADB11();
	static void rva007ADB61();
	static void rva007AE390();
	static void rva007AE3AC();
	static void rva007AF0F1();
	static void rva007AF334();
	static void rva007AF7FE();
	static void rva007AF934();
	static void rva007AF94F();
	static void rva007B55D0();
};

// ?rva007AC25C@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AC25C (12B): atexit(0x007B6C9B)
void Rva007AB85CAtexitInits::rva007AC25C()
{
	atexit( rva007B6C9B );
}

#pragma inline_depth( 0 )
// ?rva007ACAAA@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACAAA (27B): AsciiString at VA 0x00DEC290 = literal at VA 0x00BCF6DC, then atexit(0x007B6F5C)
void Rva007AB85CAtexitInits::rva007ACAAA()
{
	( (AsciiString *)&BfmeLiveCameraModeNameStorage )->AsciiString::AsciiString( "Zoom" );
	atexit( rva007B6F5C );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007ACB5D@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACB5D (27B): AsciiString at VA 0x00DEC3B8 = literal at VA 0x00BCFADC, then atexit(0x007B6F98)
void Rva007AB85CAtexitInits::rva007ACB5D()
{
	( (AsciiString *)&g_Va00DEC3B8 )->AsciiString::AsciiString( "LookupTablePostEffect" );
	atexit( rva007B6F98 );
}
#pragma inline_depth()

// ?rva007ACCA6@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACCA6 (12B): atexit(0x007B7024)
void Rva007AB85CAtexitInits::rva007ACCA6()
{
	atexit( rva007B7024 );
}



// 0x007ACE50 and 0x007ACE60 (12B each, atexit of 0x007B71D0 / 0x007B7200) are
// meshmdl_sidehash.cpp's compiler-emitted _$E2 / _$E5 for LocationHash and
// DuplicateLocationHash; they are rowed there.


// ?rva007ACED0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACED0 (12B): atexit(0x007B7300)
void Rva007AB85CAtexitInits::rva007ACED0()
{
	atexit( rva007B7300 );
}

// ?rva007ACEE0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACEE0 (12B): atexit(0x007B7340)
void Rva007AB85CAtexitInits::rva007ACEE0()
{
	atexit( rva007B7340 );
}

// ?rva007ACEF0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACEF0 (12B): atexit(0x007B7380)
void Rva007AB85CAtexitInits::rva007ACEF0()
{
	atexit( rva007B7380 );
}

// ?rva007ADB11@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ADB11 (12B): atexit(0x007B76E6)
void Rva007AB85CAtexitInits::rva007ADB11()
{
	atexit( rva007B76E6 );
}

// ?rva007ADB61@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ADB61 (12B): atexit(0x007B770E)
void Rva007AB85CAtexitInits::rva007ADB61()
{
	atexit( rva007B770E );
}


#pragma inline_depth( 0 )
// ?rva007AE3AC@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AE3AC (27B): AsciiString at VA 0x00DFF030 = literal at VA 0x00C031DC, then atexit(0x007B7979)
void Rva007AB85CAtexitInits::rva007AE3AC()
{
	( (AsciiString *)&g_Va00DFF030 )->AsciiString::AsciiString( "Palantir.apt" );
	atexit( rva007B7979 );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007AF0F1@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AF0F1 (27B): AsciiString at VA 0x00E022E8 = literal at VA 0x00C18F34, then atexit(0x007B7DB3)
void Rva007AB85CAtexitInits::rva007AF0F1()
{
	( (AsciiString *)&g_Va00E022E8 )->AsciiString::AsciiString( "GuiFX.apt" );
	atexit( rva007B7DB3 );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007AF334@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AF334 (27B): AsciiString at VA 0x00E028C4 = literal at VA 0x00C1AF48, then atexit(0x007B7E49)
void Rva007AB85CAtexitInits::rva007AF334()
{
	( (AsciiString *)&g_Va00E028C4 )->AsciiString::AsciiString( "<!TRUE!>" );
	atexit( rva007B7E49 );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007AF7FE@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AF7FE (27B): AsciiString at VA 0x00E02D68 = literal at VA 0x00C0E900, then atexit(0x007B80A1)
void Rva007AB85CAtexitInits::rva007AF7FE()
{
	( (AsciiString *)&g_Va00E02D68 )->AsciiString::AsciiString( "ALL" );
	atexit( rva007B80A1 );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007AF934@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AF934 (27B): AsciiString at VA 0x00E02E70 = literal at VA 0x00C364C0, then atexit(0x007B8119)
void Rva007AB85CAtexitInits::rva007AF934()
{
	( (AsciiString *)&g_Va00E02E70 )->AsciiString::AsciiString( "ConqueredEffectEvenglow" );
	atexit( rva007B8119 );
}
#pragma inline_depth()

#pragma inline_depth( 0 )
// ?rva007AF94F@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AF94F (27B): AsciiString at VA 0x00E02E74 = literal at VA 0x00C364D8, then atexit(0x007B8123)
void Rva007AB85CAtexitInits::rva007AF94F()
{
	( (AsciiString *)&g_Va00E02E74 )->AsciiString::AsciiString( "ConqueredEffectFlareup" );
	atexit( rva007B8123 );
}
#pragma inline_depth()


