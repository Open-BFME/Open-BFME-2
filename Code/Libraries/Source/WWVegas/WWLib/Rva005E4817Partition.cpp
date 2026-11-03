// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?Rva005E4817Partition@@YAPAHPAH0VRva005E4300Cmp@@HPA_N@Z
// stlport

// Native5E4817..5E4862:75B partition; EAX returns the split iterator.
// Calls comparator5E4300 with its four-byte context at arg10. The comparator
// owner reads that context, and caller5E49FD passes an unused bool* at arg18.
// Keep the original private address-derived names; WB's MoveTo alignment
// for the forwarder is unrelated and does not establish a function identity.
struct Rva005E4300Context;
#include "Rva005E4300Cmp.h"

int *__cdecl Rva005E4817Partition(int *first, int *last, Rva005E4300Cmp comp, int pivot, bool *)
{
loop:
	if ((first?first:first) == last)
		return first;
	if (comp(*first, pivot))
	{
		++first;
		goto loop;
	}
	do
	{
		--last;
		if (first == last)
			return first;
	} while (!comp(*last, pivot));
	int tmp = *first;
	*first = *last;
	*last = tmp;
	++first;
	goto loop;
}
