// cl: /DNDEBUG /MD /EHsc
// ??1Rva00596CDF@@UAE@XZ @0x00596CDF 11B
// Derived dtor: stores its own vtable 0x00870AF0, then tail-jumps to the rowed
// base dtor ??1Rva00573B23@@UAE@XZ (0x00573B23). Empty body, no new members.
// Sibling of ??1Rva00573F03@@UAE@XZ in Rva00573B23Dtor.cpp (same 11B shape).
// Evidence: mov [ecx] vtable then jmp 0x00573B23. Chain from 0x00573B23.
struct Rva00573B23
{
	virtual ~Rva00573B23();
};
struct Rva00596CDF : Rva00573B23
{
	virtual ~Rva00596CDF();
};
Rva00596CDF::~Rva00596CDF()
{
}
