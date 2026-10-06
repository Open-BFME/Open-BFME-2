// cl: /DNDEBUG /MD
//
// ?Rva00045473Equal@@YA_NPBX0@Z @0x00045473 (24B).
// Free memcmp wrapper: returns memcmp(a b 0x4c)==0 as bool. Retail pushes
// constant 0x4c then the two pointers and emits a real E8 to the memcmp
// import thunk with no intrinsic. Callers at 0x000B3EEC and 0x000B4B23 pass
// two pointers and test al. Precedent is Rva002634E0Equal at 0x002634E0
// with identical 24B shape and /O1 flags.

typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

Bool Rva00045473Equal(const void *a, const void *b)
{
	return memcmp(a, b, 0x4c) == 0;
}
