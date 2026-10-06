// ??$__adjust_heap@PAHHHURva005E4300Cmp@@@_STL@@YAXPAHHHHURva005E4300Cmp@@@Z
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// _STL::__adjust_heap<int*, int, int, Compare> at 0x5E48C2, retail 94 bytes.
// Read from the retail disassembly, not from a mangled name: the bytes are
// stlport's __adjust_heap line for line, including the vendor quirk that spills
// topIndex over the hole-index argument slot so the __push_heap tail call
// receives topIndex.
//
// The test at 0x5E48D7 loads *values* into the comparator:
//
//   5e48d7  push [edi+esi*4-4]
//   5e48db  lea  ecx,[ebp+0x18]
//   5e48de  push [edi+esi*4]
//   5e48e1  call 0x5E4300
//
// so Compare::operator() takes its two ints by value and keeps state via
// `this` (the object at [ebp+0x18]); 0x5E4300 dereferences `this` and looks the
// two ids up through an indexed field before comparing them. That rules out
// _STL::greater<int>, whose operator() is the 22-byte by-reference twin already
// rowed at 0x003B005B, and whose __adjust_heap instantiation is rowed there
// too. Compare has no target-proven name, so it is address-derived here from
// its only unknown-callee operator() at 0x5E4300. Declared and never defined,
// so the call stays out of line as retail has it; this reproduces all 94 bytes,
// with the remaining REL32 sites being that call and the __push_heap tail call.
#include <algorithm>
#include <functional>

struct Rva005E4300Cmp
{
	bool operator()(int a, int b) const;
};

void bfmeEmitAdjustHeapGreater(int *first, int *last)
{
	_STL::make_heap(first, last, Rva005E4300Cmp());
}
