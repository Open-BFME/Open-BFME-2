// cl: /GX-
// stlport
// STLport __unguarded_linear_insert over 8-byte {float, unsigned} keyframes,
// @0x00599435 49B: the banked attempt wrote it as a free function with a local
// copy of the value and could not explain why retail reloads the value from
// [esp+8] on every iteration and keeps the loop test at the top. Both follow
// from the template: comp(val, *next) takes val by reference, so its address
// escapes into the (inlined) comparator and the stores through last may alias
// it. The four caller dwords are last, the value (two dwords) and the empty
// comparator; eax holds last at ret. Callers 0x5994BC and 0x599A16 (not yet
// rowed then) are the insertion-sort siblings of this instantiation. Element and
// comparator names are address-derived; the comparator orders descending by
// the float field.
//
// The rest of the 0x599466-0x599D55 run is the STLport sort family for the
// same element and comparator, reproduced by the explicit sort instantiation
// at the end: __push_heap, __unguarded_insertion_sort(_aux), __adjust_heap,
// __unguarded_partition, __pop_heap(_aux), __make_heap, make_heap, pop_heap,
// __linear_insert, sort_heap, __insertion_sort, __partial_sort,
// __final_insertion_sort, partial_sort, __introsort_loop and sort, each
// calling the next by REL32. swap and copy_backward fold onto the rowed
// pair<ObjectID,unsigned> bodies at 0x5A9125 and 0x4C72FE (byte-identical
// under these flags); __median, __lg, iter_swap and the comparator inline.
#include <algorithm>

struct Rva00599435Keyframe
{
	float m_value;
	unsigned int m_frame;
};

struct Rva00599435Compare
{
	bool operator()(const Rva00599435Keyframe &a, const Rva00599435Keyframe &b) const { return a.m_value > b.m_value; }
};

// ??$__unguarded_linear_insert@PAURva00599435Keyframe@@U1@URva00599435Compare@@@_STL@@YAXPAURva00599435Keyframe@@U1@URva00599435Compare@@@Z @0x00599435
template void _STL::__unguarded_linear_insert<Rva00599435Keyframe *, Rva00599435Keyframe, Rva00599435Compare>(Rva00599435Keyframe *, Rva00599435Keyframe, Rva00599435Compare);

// ??$sort@PAURva00599435Keyframe@@URva00599435Compare@@@_STL@@YAXPAURva00599435Keyframe@@0URva00599435Compare@@@Z @0x00599D13 and its callees
template void _STL::sort<Rva00599435Keyframe *, Rva00599435Compare>(Rva00599435Keyframe *, Rva00599435Keyframe *, Rva00599435Compare);
