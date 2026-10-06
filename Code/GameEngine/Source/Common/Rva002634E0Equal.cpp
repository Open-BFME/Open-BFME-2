// cl: /DNDEBUG /MD
//
// ?Rva002634E0Equal@@YA_NPBX0@Z @0x002634E0 (24B).
// Free memcmp wrapper: returns memcmp(a b 0x10)==0 as bool. Retail pushes
// constant 0x10 then the two pointers and emits a real E8 to the memcmp
// import thunk with no intrinsic. Callers at 0x00263500 and 0x00264103 pass
// two pointers and test al. Precedent is equalTag_Rva003B31C7 at 0x003B31C7
// with identical 24B shape and /O1 flags.

typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

Bool Rva002634E0Equal(const void *a, const void *b)
{
	return memcmp(a, b, 0x10) == 0;
}
