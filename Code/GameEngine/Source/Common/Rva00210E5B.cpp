// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00210E5B@@YGXPAXH@Z @0x00210E5B 33B
// Target evidence: lookup through g_00DFEF18 using rowed 0x002BFDAE, then
// forward the second stack argument to 0x003FA781 on the returned entry. The
// entry is also used as the address-derived Rva003FA835 view by another target
// consumer. The operation and argument meaning remain unresolved.

class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;

#include "../../Include/GameLogic/LivingWorldClass.h"

#include "../../Include/Common/Rva003FA835.h"

void __stdcall rva00210E5B(void *key, int value)
{
	void *entry = ((LivingWorld *)((Rva002D3627Host *)TheLivingWorld))->FindClickableObject(key);
	if (entry)
		((Rva003FA835 *)entry)->rva003FA781(value);
}

#include "../../Include/Common/Rva00DFE1C8Host.h"

// ICF-folded twin of rva00210E5B above (same 33 bytes at 0x00210E5B): the
// member spelling ignores its receiver, so its stack frame matches the
// stdcall spelling exactly, including the callee-cleaned return.
void Rva00DFE1C8Host::rva00210E5B(int key, int value)
{
	void *entry = ((LivingWorld *)((Rva002D3627Host *)TheLivingWorld))->FindClickableObject((void *)key);
	if (entry)
		((Rva003FA835 *)entry)->rva003FA781(value);
}
