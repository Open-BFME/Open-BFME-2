// ?aptKeyCode@@YAPAVAptValue@@XZ
// Open-BFME7: Apt key-code callback (41 B): maps the last key through the
// special-key table when the modifier bits are set and the code is small.
// cl: /DNDEBUG /MD /EHsc /D_CRTIMP=
class AptValue;
#include <ctype.h>
#include "../../../Include/Common/AptInteger.h"
extern unsigned int Rva008A5250LastKey;
// Rva008A5250LastKey: matched references place it at VA 0xe18328 (zero-filled .bss).
unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
AptValue* aptKeyCode()
{
	unsigned int key = Rva008A5250LastKey;
	int code = key >> 17;
	if ((key & 0x3fc) && code < 0x14)
		code = Rva008A5250KeyTable[code];
	return AptInteger::Create(code);
}

// BFME1 donor aptKeyValue at 0x008A52F0 transfers to BFME2 0x006E8BF0.
// The target bytes use the same last-key state and AptInteger factory as the
// adjacent matched aptKeyCode body. The callback name remains donor-derived;
// there is no named target caller.
AptValue* aptKeyValue()
{
	int code = Rva008A5250LastKey >> 17;
	if (code >= 0x20 && code <= 0x7e)
	{
		__asm
		{
			push eax
			call toupper
			add esp, 4
			push eax
			call AptInteger::Create
			add esp, 4
			ret
		}
		__assume(0);
	}
	if (code < 0x14)
		code = Rva008A5250KeyTable[code];
	return AptInteger::Create(code);
}
