// cl: /GX- /GS
// jabba util.cpp int64-array join @ 0x0066C4F0 (289B), ported from BFME1
// Y2FeslUtilJoinI64.cpp. Clears dest; sprintf each parts[i] as %I64d;
// ensures used+len+1 < destSize (else diag fail); inserts sep before i>0;
// strcat appends.
//
// Repairs against the BFME1 source, all read from retail:
// - sprintf is declared without <stdio.h>'s dllimport so the call is a
//   direct REL32 to the import stub at 0x006291B4, as retail has it (the
//   Y2ProtoMangleHelpers TU documents the same pattern).
// - The diag fail arguments are the literals retail references ("false"
//   at 0x00BBC410 and the util.cpp build path at 0x00CE3A30), not the
//   globals BFME1 spells; the string verifier checks them byte for byte.
// - The diag getter is BFME1's ?Rva007EB810Get@@YAHXZ (int(void),
//   pinned at 0x006587A0), so its result is cast to the diag pointer
//   at the call site instead of BFME1's pointer-returning declaration.

#include <string.h>
#include <stdio.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get(void);

// BFME2 0x0066C460; body from Open-BFME-1 5cae4bdff (BFME1 0x007FFFB0), unchanged.
// 0x007FFFB0 -- length of a present C string including its NUL, 0 for null.
// Same jabba util.cpp neighbourhood as the joins below the DirtySock text
// helpers. The goto-loop spelling selects retail's EDX cursor register; the
// while form mirrors into ECX. Identity is address-derived: no caller,
// string, or vtable names it.
unsigned int Rva007FFFB0Span( const char *text )
{
	const char *cursor;
	const char *afterStart;
	if( text == 0 )
		return 0;
	cursor = text;
	afterStart = text + 1;
loop:
	{
		char c = *cursor;
		++cursor;
		if( c != 0 )
			goto loop;
	}
	return (unsigned int)( cursor - afterStart ) + 1;
}
