// cl: /O1 /EHsc /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// 0x000BBBF3 (38B): STLport's __uninitialized_copy loop over 8-byte records.
// Each element goes through the placement-copy body at 0x000BBA47, which the
// ledger owns as Rva000BBA47Construct (stlport_construct_game_structs.cpp):
// retail keeps several identical 8-byte placement copies apart (each with its
// own EH data), so they and this loop carry address names rather than
// _Construct/__uninitialized_copy over an element type nobody has recovered.
// The fourth (tag) argument is pushed by the caller and never read.

namespace _STL { struct __false_type; }

#include "TreeKey00242F5E.h"

void Rva000BBA47Construct(TreeKey00242F5E *dest, const TreeKey00242F5E &source);

TreeKey00242F5E *Rva000BBBF3UninitializedCopy(const TreeKey00242F5E *first, const TreeKey00242F5E *last,
	TreeKey00242F5E *result, const _STL::__false_type &)
{
	TreeKey00242F5E *cur = result;
	for (; first != last; ++first, ++cur)
		Rva000BBA47Construct(cur, *first);
	return cur;
}
