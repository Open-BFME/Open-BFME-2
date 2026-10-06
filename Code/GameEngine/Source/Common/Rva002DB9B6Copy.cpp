// cl: /Oi- /MD
//
// ?rva002DB9B6@Rva002DB9B6@@QAEXPAX@Z, retail 0x002DB9B6, 21 bytes.
// __thiscall memcpy-out of 0x28 bytes from this+0x60 to its arg via CRT
// memcpy thunk 0x006291A8. Plain extern (no dllimport) so the call emits E8
// to the jmp-IAT thunk; /Oi- stops the 40-byte copy inlining to rep movsd.
// Leaf (one import callee). Callers 0x002DE2DC 0x0057EA52. Prev 0x002DB93E
// ctor / next 0x002DBA19 lea getter. Honest address name; owner unproven.
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

struct Rva002DB9B6
{
	char m_pad[0x60];
	char m_data[0x28];
	void rva002DB9B6(void *out);
};

void Rva002DB9B6::rva002DB9B6(void *out)
{
	memcpy(out, m_data, 0x28);
}
