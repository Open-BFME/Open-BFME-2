// cl: /DNDEBUG /MD
//
// ?Rva00318D9BFill@@YAPAVRva00318B5C@@PAV1@IABV1@ABU__false_type@_STL@@@Z @0x00318D9B (37B).
// Null-guarded fill of count Rva00318B5C (0x10 stride) via the rowed
// Rva00318D63Copy at 0x00318D63. Fourth arg is the caller's tag byte at
// [ebp+0x1b] (STL __false_type dispatch, unused in the loop). Evidence:
// sole caller FUN_00719F5A at 0x00319FC5 pushes 4 (dest eax plus count plus
// value plus tag) and cleans 0x10; sibling copy at 0x00318D75 shares the
// Copy callee and 0x10 stride.

class Rva00318B5C
{
	char _m[0x10];
public:
	Rva00318B5C(const Rva00318B5C &that);
};

void Rva00318D63Copy(Rva00318B5C *dest, const Rva00318B5C &src);

namespace _STL
{
struct __false_type {};
}

Rva00318B5C *Rva00318D9BFill(Rva00318B5C *first, unsigned int n, const Rva00318B5C &x, const _STL::__false_type &)
{
	Rva00318B5C *cur = first;
	for (; n > 0; --n, ++cur)
		Rva00318D63Copy(cur, x);
	return cur;
}
