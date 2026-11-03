// The comparator carries the army context at +0 (native 5E4300); keep
// its four-byte state and class spelling consistent through the sort family.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??$__unguarded_insertion_sort@PAHVRva005E4300Cmp@@@_STL@@YAXPAH0VRva005E4300Cmp@@@Z @0x005E4A48 23B unguarded insertion sort entry for int keys.
// Forwards first last plus NULL type tag plus comparator to rowed aux 0x005E48A1.
// Evidence: chain from just-landed aux; frameless 4-push forwarder with push 0 dummy; caller at 0x005E4C57 in 0x005E4C2F; same 23B shape as 0x00423E0E and 0x001739CD.
struct Rva005E4300Context;
#include "Rva005E4300Cmp.h"
namespace _STL {
template <class RandomAccessIter, class T, class Compare>
void __unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T *, Compare comp);
template <class RandomAccessIter, class Compare>
void __unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp)
{
	__unguarded_insertion_sort_aux(first, last, (int *)0, comp);
}
template void __unguarded_insertion_sort<int *, Rva005E4300Cmp>(int *, int *, Rva005E4300Cmp);
}
