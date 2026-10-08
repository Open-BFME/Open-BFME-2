// cl: /O2 /MD
// ?rva0014A0B0@Rva0014A0B0@@QBEHXZ @0x0014A0B0 (25B).
// Target evidence: thiscall, no arguments; reads the pointer at +0xC4 and
// answers 1 only when it is non-null and bit 2 of its byte +0x19 is set
// (mov eax,1 / xor eax,eax returns). Called twice from the unrowed
// W3DHordeModelDrawManager::ProcessGroup body at 0x00079FBC (REL32 at
// 0x0007A0A6 and 0x0007A19E). The 'mov eax,1; ret' at 0x0014A0C0 is this
// body's true-return tail, not a function: nothing calls, jumps to or points
// at it. Owner and field names are unknown, so the class stays address-derived.

struct Rva0014A0B0Target
{
	unsigned char m_pad00[0x19];
	unsigned char m_19;
};

class Rva0014A0B0
{
public:
	int rva0014A0B0() const;

private:
	unsigned char m_pad00[0xC4];
	Rva0014A0B0Target *m_c4;
};

int Rva0014A0B0::rva0014A0B0() const
{
	return m_c4 && (m_c4->m_19 & 4);
}
