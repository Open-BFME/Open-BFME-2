// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Two STLport sorts over 4-byte values compared through a function pointer:
// sort 0x0021E408 (introsort loop 0x0021DD81) and sort 0x002C571E (introsort
// loop 0x002C56A3), 67 bytes each. Target evidence: both loops call the median
// 0x002C1777, which calls the comparator through the pointer, and the
// partition rowed as __unguarded_partition<int *, int, bool (*)(int, int)>
// (stlport_unguarded_partition_int_funptr.cpp). Most of the heap chain is
// rowed by hand with void * values (Rva002198ECAdjustHeap.cpp,
// Rva002C5556SortHeap.cpp).
//
// The value types are STAND-INS: the image fixes only that the values are 4
// bytes, copied bitwise, and passed to the comparator by value. Retail folded
// the leaves the two sorts share (median, partition, the insertion sorts and
// most of the heap chain) into one body each. The upper levels of each sort
// stay separate, so the two need distinct types. The sort near the void *
// heap rows uses void *; the one near the int partition row uses int.
// Shared bodies are rowed under the void * names and pinned under the int ones.
//
// The linear inserts call STLport's __copy_trivial_backward. Retail's copy
// of it (0x00620840) is the one units built for speed emit, with a stack-
// pointer frame and the imported memmove. So its header is compiled with the
// speed option, and _CRTIMP keeps its import default.

#pragma optimize("t", on)
#include <stl/_algobase.h>
#pragma optimize("", on)
#include <algorithm>

typedef bool (*VoidPtrValueLess)(void *, void *);
typedef bool (*IntValueLess)(int, int);

template void _STL::sort<void **, VoidPtrValueLess>(void **, void **, VoidPtrValueLess);
template void _STL::sort<int *, IntValueLess>(int *, int *, IntValueLess);

// Native 002195E6..00219695 is a 175-byte constructor returning this.
// Float values below are read from retail's literal slots, independently of
// donor names. The four unwritten dwords and original class remain unknown.
struct Rva002195E6Group
{
	__forceinline Rva002195E6Group(float a, float b, float c, float d)
		: value00(a), value04(b), value08(c), value0C(d), value10(0.0f) {}
	float value00, value04, value08, value0C, value10;
	unsigned int untouched14;
};

class Rva002195E6
{
public:
	Rva002195E6();
private:
	Rva002195E6Group group00, group18, group30, group48;
	float value60, value64;
	unsigned int word68;
};

Rva002195E6::Rva002195E6()
	: group00(0.3f, 0.2f, 50.0f, 30.0f),
	  group18(0.4f, 0.3f, 70.0f, 50.0f),
	  group30(0.3f, 0.2f, 50.0f, 30.0f),
	  group48(0.3f, 0.2f, 50.0f, 30.0f),
	  value60(0.5f), value64(0.0f), word68(0)
{
}
