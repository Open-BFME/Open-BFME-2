// cl: /DNDEBUG /MD
// Native6CC4A0..6CC4C0 is a 32-byte deleting helper. The receiver is in
// ECX, the flags are on the stack, and the complete body ends RET4.
// Cleanup6DAFA0 walks the pool; flag1 then releases the 28-byte allocation
// through the named size-aware free thunk6CBC50. The legacy Init spelling
// does not establish initializer semantics; the original name is unknown.
class Rva006CC4A0;
#include "../../../Libraries/Source/Apt/Rva006DAFA0Walk.h"
void rva006CBC50(void *,unsigned);

Rva006CC4A0 *__fastcall rva006CC4A0Init(Rva006CC4A0 *o, int fwd, int arg)
{
	((Rva006DAFA0Walk *)o)->rva006DAFA0();
	if (arg & 1)
		rva006CBC50(o, 0x1C);
	return o;
}
