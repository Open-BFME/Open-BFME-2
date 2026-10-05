// cl: /O1 /arch:SSE /Ob0
// ??0Rva0053FDE6@@QAE@ABV0@@Z, retail 0x0053FF5F, 51 bytes.
// Copy constructor: copies the scalar head at +0/+4/+8/+0xC, a 16-byte block
// at +0x10..+0x1F via movs, then the scalar tail at +0x20. Returns receiver
// (mov eax,ecx) and pops 4. Called by the outer copy at 0x00540036.
// The scalar dwords are copied through int* locals (sibling 0x53FE2A idiom):
// that is what schedules the /O1 save pair where retail places it.
struct Rva0053FDE6Block16 { float m_10, m_14, m_18, m_1c; };

class Rva0053FDE6
{
public:
	Rva0053FDE6(const Rva0053FDE6 &);
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	Rva0053FDE6Block16 m_block;
	float m_20;
};

Rva0053FDE6::Rva0053FDE6(const Rva0053FDE6 &other)
{
	m_00 = other.m_00;
	int *dst = &m_04;
	const int *src = &other.m_04;
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	m_block = other.m_block;
	m_20 = other.m_20;
}
