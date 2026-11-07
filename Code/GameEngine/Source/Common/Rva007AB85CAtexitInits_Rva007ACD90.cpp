// cl: /Ireference/shims/bfme2_ascii /MD
// Split from Rva007AB85CAtexitInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
void __cdecl rva007B7024();
void __cdecl Rva007B7090Set();
void __cdecl Rva007B70A0Set();
void __cdecl rva007B71D0();
void __cdecl rva007B7200();
void __cdecl releaseBrowser();
void __cdecl rva007B7300();
void __cdecl rva007B7340();
void __cdecl rva007B7380();
void __cdecl rva007B76E6();
void __cdecl rva007B770E();
void __cdecl rva007B7979();
void __cdecl rva007B8119();
void __cdecl rva007B8123();
void __cdecl clearMissingVariant();


struct Rva007AB85CAtexitInits
{
	static void rva007AC25C();
	static void rva007ACCA6();
	static void rva007ACD90();
	static void rva007ACDA0();
	static void rva007ACE50();
	static void rva007ACE60();
	static void rva007ACE80();
	static void rva007ACED0();
	static void rva007ACEE0();
	static void rva007ACEF0();
	static void rva007ADB11();
	static void rva007ADB61();
	static void rva007AE3AC();
	static void rva007AF934();
	static void rva007AF94F();
	static void rva007B55D0();
};


#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()



// ?rva007ACD90@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACD90 (12B): atexit(0x007B7090)
void Rva007AB85CAtexitInits::rva007ACD90()
{
	atexit( Rva007B7090Set );
}

// ?rva007ACDA0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACDA0 (12B): atexit(0x007B70A0)
void Rva007AB85CAtexitInits::rva007ACDA0()
{
	atexit( Rva007B70A0Set );
}



// ?rva007ACE80@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACE80 (12B): atexit(0x007B7270)
void Rva007AB85CAtexitInits::rva007ACE80()
{
	atexit( releaseBrowser );
}







#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

// ?rva007B55D0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007B55D0 (12B): atexit(0x007B9B40)
void Rva007AB85CAtexitInits::rva007B55D0()
{
	atexit( clearMissingVariant );
}
