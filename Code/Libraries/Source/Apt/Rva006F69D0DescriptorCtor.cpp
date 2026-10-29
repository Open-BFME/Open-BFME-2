// ??0Rva006F69D0@@QAE@PAXHH@Z
// cl: /O2 /MD /DNDEBUG
// Retail 0x006F69D0 (116 B, ret 0xC): descriptor interpretation constructor built by Rva006F6A50
// (0x006F6A50, Rva006F6A50Cluster.cpp) when the descriptor kind is 3; the object is 0x1C bytes.
// WorldBuilder 0x01790970 (same body, unnamed) gives the statement shape: a pointer to the descriptor
// body at +4 is taken first, +0x18 is two 16-bit bitfields (and/or merges in the debug build, word
// stores here), and +0x04 is an if/else while +0x08/+0x0C/+0x10 are conditionals. x87 float copy:
// this unit keeps the x87 (no /arch:SSE) flags. Field names are structural inferences.

struct Rva006F69D0DescriptorBody
{
	unsigned int m_flags;
	char m_pad04[0x0c - 0x04];
	char m_block0C[0x24 - 0x0c];
	char m_colorTransform[0x2c - 0x24];
	float m_float2C;
	char m_pad30[0x34 - 0x30];
	unsigned short m_clipDepth;
	char m_pad36[0x38 - 0x36];
	void *m_clipActions;
};

struct Rva006F69D0Descriptor
{
	int m_kind;
	Rva006F69D0DescriptorBody m_body;
};

class Rva006F69D0
{
public:
	Rva006F69D0(void *descriptor, int second, int fourth) throw();

	int m_00;
	void *m_04;
	void *m_08;
	void *m_0c;
	float m_10;
	unsigned int m_14;
	unsigned int m_18 : 16;
	unsigned int m_1a : 16;
};

Rva006F69D0::Rva006F69D0(void *descriptor, int second, int fourth) throw()
{
	const Rva006F69D0DescriptorBody *b = &((const Rva006F69D0Descriptor *)descriptor)->m_body;
	m_18 = second;
	m_14 = b->m_flags;
	m_00 = fourth;
	m_1a = b->m_clipDepth;
	if (b->m_flags & 4)
		m_04 = (void *)b->m_block0C;
	else
		m_04 = 0;
	m_08 = (b->m_flags & 8) ? (void *)b->m_colorTransform : 0;
	m_0c = (b->m_flags & 0x80) ? b->m_clipActions : 0;
	m_10 = (b->m_flags & 0x10) ? b->m_float2C : 0.0f;
}
