// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x0024952E, 48 bytes. The target LANAPI table places this callback
// at slot 48, corresponding to BFME1 OnNameChange. Retail dispatches through
// an opaque no-argument virtual at slot 33, then releases the by-value
// UnicodeString argument through StringBase's target release helper.

typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

#include "unicode_string.h"
#include "../../Include/GameNetwork/LANAPI.h"

void LANAPI::OnNameChange( UnsignedInt address, UnicodeString newName )
{
	rva00248E87();
}
