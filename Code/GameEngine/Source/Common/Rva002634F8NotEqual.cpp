// cl: /DNDEBUG /MD
//
// ?Rva002634F8NotEqual@@YA_NPBX0@Z @0x002634F8 (21B).
// Free inequality wrapper: returns !Rva002634E0Equal(a b) for the 16-byte
// blocks. Retail pushes the two pointers, calls the rowed 0x002634E0, negates
// al, pops the inner args to ecx, then booleanizes with sbb eax eax inc eax.
// Caller at 0x004ABBCD passes two pointers and tests al.

typedef bool Bool;

Bool Rva002634E0Equal(const void *a, const void *b);

Bool Rva002634F8NotEqual(const void *a, const void *b)
{
	return !Rva002634E0Equal(a, b);
}
