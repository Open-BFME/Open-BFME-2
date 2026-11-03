// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Native5E49FD..5E4A1B is the complete30B cdecl partition forwarder.
// Caller5E4E55 uses the returned EAX as an iterator into its int vector.
// The four-byte comparator carries the caller's army context. The fifth
// bool* is passed last and is unused by the owned75B partition provider.
// Original function names remain unknown; remove the former void alias pin.
struct Rva005E4300Context;
#include "../../../Libraries/Source/WWVegas/WWLib/Rva005E4300Cmp.h"
int *__cdecl Rva005E4817Partition(int *,int *,Rva005E4300Cmp,int,bool *);

int *__cdecl rva005E49FD(int *first,int *last,Rva005E4300Cmp comp,int pivot)
{
	bool tmp;
	return Rva005E4817Partition(first,last,comp,pivot,&tmp);
}
