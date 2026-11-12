// cl: /DNDEBUG /MD /EHsc
// ?Rva005E7285Copy@@YAPAVRva005E7198@@PAV1@00PAXH@Z @0x005E7285 47B
// forward copy for Rva005E7198 4B entries via rowed assign 0x005E7198 with dummy tag args.
// Same 47B shape as Rva005EF4C0Copy (forward *dest=*first ++first ++dest loop with sar 2 count)
// plus two dummy trailing args (tag pointer plus zero) that ride dead above the frame;
// caller 0x005E74A0 passes 5 args. Precedent: Rva0014FA90Copy 50B 5-arg forward copy.
#include "../../../Include/Common/Rva005E7198.h"
Rva005E7198 *__cdecl Rva005E7285Copy(Rva005E7198 *sourceBegin, Rva005E7198 *sourceEnd, Rva005E7198 *destination, void *unusedTag, int unusedExtra)
{
	int elementCount = sourceEnd - sourceBegin;
	if (elementCount <= 0)
		return destination;
	for (int remainingElements = elementCount; remainingElements != 0; --remainingElements) {
		*destination = *sourceBegin;
		++sourceBegin;
		++destination;
	}
	return destination;
}
Rva005E7198 *__cdecl Rva005E748DForward(Rva005E7198 *sourceBegin, Rva005E7198 *sourceEnd, Rva005E7198 *destination, void *ignored)
{
	char unusedDispatchTag;
	return Rva005E7285Copy(sourceBegin, sourceEnd, destination, &unusedDispatchTag, 0);
}
