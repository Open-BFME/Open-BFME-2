// cl: /DNDEBUG /MD
//
// ?Rva0037DC8AEqual@@YA_NPBX0@Z @0x0037DC8A (27B).
// Free memcmp wrapper: returns memcmp(a b 0x80)==0 as bool. Retail pushes
// constant 0x80 then the two pointers and emits a real E8 to the memcmp
// import thunk with no intrinsic. Callers at 0x0037E11D 0x004382A8 0x0045F4CA
// pass two pointers and test al. Precedent is Rva002634E0Equal at 0x002634E0
// and Rva00045473Equal at 0x00045473 with identical shape and /O1 flags.
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

Bool Rva0037DC8AEqual(const void *a, const void *b)
{
	return memcmp(a, b, 0x80) == 0;
}
