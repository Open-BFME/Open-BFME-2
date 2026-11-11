// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00549DCB@Rva00549DCB@@QBE_NABQAUFoo00549DCB@@0@Z, RVA 0x00549DCB, 39B
// Comparator for sort: unsigned WORD at +0x5da via Foo+4 indirection.
// Evidence: 12 callers all lea ecx (this) + 2 pushes + direct call; twin
// 0x00549DF2 is descending (loads arg2 first, returns arg2<arg1); callers
// 0x00549F02/101 median-of-three and 0x0054A086/82 linear-insert-like both
// use this shape; sbb/neg proves unsigned WORD less-than returning 0/1.
struct Bar00549DCB {
	char pad[0x5da];
	unsigned short key;
};
struct Foo00549DCB {
	int unk0;
	Bar00549DCB *bar;
};
#include "Rva00549DCB.h"
bool Rva00549DCB::rva00549DCB(Foo00549DCB * const &lhs, Foo00549DCB * const &rhs) const
{
	return lhs->bar->key < rhs->bar->key;
}
