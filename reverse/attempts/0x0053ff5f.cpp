// ??0Rva0053FDE6@@QAE@ABV0@@Z
// partial score=0.96 date=2026-10-05
// cl: /O1
// ??0Rva0053FDE6@@QAE@ABV0@@Z, retail 0x0053FF5F, 51 bytes.
// Copy constructor: copies the scalar head at +0/+4/+8/+0xC, a 16-byte block
// at +0x10..+0x1F via movs, then the scalar tail at +0x20. Returns receiver
// (mov eax,ecx) and pops 4. Called by the outer copy at 0x00540036.
//
// partial: size-exact 51/51; sole residual is the scheduler's placement of
// `push edi` -- retail pushes it after the +0x8 store and +0xC load, we push
// it immediately after `push esi`. Source order, block type, memcpy, /Ob0 and
// individual-field variants do not move it.
struct Rva0053FDE6Block16 { float m_10, m_14, m_18, m_1c; };

class Rva0053FDE6
{
public:
	Rva0053FDE6(const Rva0053FDE6 &);
	int m_00;
	float m_04;
	float m_08;
	float m_0c;
	Rva0053FDE6Block16 m_block;
	float m_20;
};

Rva0053FDE6::Rva0053FDE6(const Rva0053FDE6 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0c = other.m_0c;
	m_block = other.m_block;
	m_20 = other.m_20;
}
