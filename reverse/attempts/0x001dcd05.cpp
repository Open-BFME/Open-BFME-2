// ?rva001DCD05@Rva001DCD05@@QAEPAXXZ
// partial score=0.95 date=2026-10-06
// cl: /MD
//
// ?rva001DCD05@Rva001DCD05@@QAEPAXXZ, retail 0x001DCD05, 23 bytes.
// Thiscall void* with no params: if m_21 return &m_14 else return m_20 ? &m_08 : 0.
// Evidence: direct calls prove start; caller 0x001DE106; neighbours
// 0x001DCD01/0x001DCD1C; ret with no stack args.
class Rva001DCD05
{
public:
	void *rva001DCD05();
private:
	char m_pad[8];
	char m_08;
	char m_pad2[0x14 - 0x09];
	char m_14;
	char m_pad3[0x20 - 0x15];
	unsigned char m_20;
	unsigned char m_21;
};

void *Rva001DCD05::rva001DCD05()
{
	if (m_21)
		return &m_14;
	unsigned char b = m_20;
	Rva001DCD05 *p = (Rva001DCD05 *)((char *)this + 8);
	return b ? (void *)p : 0;
}
