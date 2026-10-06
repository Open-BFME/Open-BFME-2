// cl: /DNDEBUG /MD
//
// ?Rva000B3EECNotEqual@@YA_NPBX0@Z @0x000B3EEC (21B).
// Free inequality wrapper: returns !Rva00045473Equal(a b) for the 76-byte
// blocks. Retail pushes the two pointers, calls the rowed 0x00045473, negates
// al, pops the inner args to ecx, then booleanizes with sbb eax eax inc eax.
// Caller at 0x004ABBBB passes two pointers and tests al.

typedef bool Bool;

Bool Rva00045473Equal(const void *a, const void *b);

Bool Rva000B3EECNotEqual(const void *a, const void *b)
{
	return !Rva00045473Equal(a, b);
}
