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
// Strings whose unit is known are defined in that unit (LINK-236).

#include <stdlib.h>
#include "ascii_string.h"

void __cdecl rva007B6C9B();
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
void __cdecl rva007B9B40();


struct Rva007AB85CAtexitInits
{
	static void rva007AC25C();
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
	static void rva007B55D0();
};

// ?rva007AC25C@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AC25C (12B): atexit(0x007B6C9B)
void Rva007AB85CAtexitInits::rva007AC25C()
{
	atexit( rva007B6C9B );
}

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



