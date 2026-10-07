// cl: /DNDEBUG /MD /EHsc
//
// ?Rva00132C28Register@@YAXPAX00@Z
// Retail 0x00132C28, 85 bytes. The target rejects null first and second
// arguments, allocates 0x54 bytes, calls the address-derived three-argument
// constructor at 0x0013213B, then registers its return with Add_Prototype at
// 0x0061EF90. The constructor argument meanings and concrete type remain
// unknown; the callsite establishes a thiscall with three 32-bit arguments.

class Rva00132C28Prototype
{
	unsigned char m_unknown[0x54];

public:
	Rva00132C28Prototype(void *a, void *b, void *c);
};

void Add_Prototype(void *prototype);

void __cdecl Rva00132C28Register(void *a, void *b, void *c)
{
	if (a && b)
	{
		Rva00132C28Prototype *prototype =
			new Rva00132C28Prototype(a, b, c);
		Add_Prototype(prototype);
	}
}
