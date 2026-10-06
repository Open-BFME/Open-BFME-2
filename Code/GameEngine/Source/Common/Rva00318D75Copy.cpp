// cl: /DNDEBUG /MD
//
// ?Rva00318D75Copy@@YAPAVRva00318B5C@@PAV1@00ABU__false_type@_STL@@@Z @0x00318D75 (38B).
// Copies range of Rva00318B5C (0x10 stride) via the rowed Rva00318D63Copy at
// 0x00318D63. Fourth arg is the caller's tag dword (STL __false_type
// dispatch, unused in the loop). Evidence: callers at 0x00319322 0x00319C6B
// 0x00319F98 0x00319FE3 push 4 and clean 0x10; sibling fill at 0x00318D9B
// shares the Copy callee and stride.

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

Rva00318B5C *Rva00318D75Copy(Rva00318B5C *first, Rva00318B5C *last, Rva00318B5C *result, const _STL::__false_type &)
{
	Rva00318B5C *cur = result;
	for (; first != last; ++first, ++cur)
		Rva00318D63Copy(cur, *first);
	return cur;
}
