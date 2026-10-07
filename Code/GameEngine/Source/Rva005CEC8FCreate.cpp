// ?Rva005CEC8FCreate@@YAPAVRva005CEC8F@@PAV1@PBUPayload@Rva005CEAE6@@@Z
// cl: /O1 /MD /Oy-
// Packet disassembly supports a free cdecl allocation helper at 0x005CEC8F:
// allocate 0x14 bytes through 0x002FDA0, call 0x005CEAE6 with src when nonnull,
// store the resulting pointer through out, then increment the +4 field.
// The helper and payload names and member layout remain RVA-derived inference.
// Retail reserves a 4-byte compiler stack slot and clears it with AND [ebp-4],0.
// The local plus this narrow asm operation reproduce that observed codegen.

class Rva005CEAE6
{
public:
	struct Payload { int v[3]; };
	Rva005CEAE6(const Payload *src) throw();
	virtual ~Rva005CEAE6() throw() {}
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CEC8F
{
public:
	Rva005CEAE6 *m_00;
};

Rva005CEC8F * __cdecl Rva005CEC8FCreate(Rva005CEC8F *out, const Rva005CEAE6::Payload *src)
{
	int state;
	__asm { and state, 0 }
	Rva005CEAE6 *p = new Rva005CEAE6(src);
	out->m_00 = p;
	if (p != 0)
		p->m_ref++;
	return out;
}
