// cl: /DNDEBUG /MD
//
// ?rva002C9BC3@Rva002C9BC3Owner@@QAEXPAX0@Z @0x002C9BC3 33B: float-delta
// forwarder (thiscall). Retail reads float arg2[2], subtracts arg1[0x10],
// and calls the pinned sibling ?rva002C9B80@Rva002C9BC3Owner@@QAEXPAXM@Z at
// 0x002C9B80 (REL32 read at 0x002C9BDC; Ghidra 67B FUN_006c9b80) with
// (arg1, delta) and the same this (entry ecx preserved through the push-ecx
// float temp slot). Frameless two-arg thiscall (ret 8). Subss/movss need
// /arch:SSE. Honest address-derived names.

class Rva002C9BC3Owner
{
public:
	void rva002C9B80(void *a, float b);
	void rva002C9BC3(void *a, void *b);
};

struct Rva002C9BC3A
{
	int m_pad[16]; // +0x00..+0x40 unclaimed
	float m_f40; // +0x40
};

struct Rva002C9BC3B
{
	int m_pad[2]; // +0x00..+0x08 unclaimed
	float m_f08; // +0x08
};

// ?rva002C9BC3@Rva002C9BC3Owner@@QAEXPAX0@Z
void Rva002C9BC3Owner::rva002C9BC3(void *a, void *b)
{
	rva002C9B80(a, ((Rva002C9BC3B *)b)->m_f08 - ((Rva002C9BC3A *)a)->m_f40);
}
