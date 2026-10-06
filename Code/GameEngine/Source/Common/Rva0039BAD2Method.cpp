// cl: /DNDEBUG /MD /EHsc
// ?rva0039BAD2@Rva0039BAD2@@QAEXPAURva0039BAD2Input@@H@Z, retail 0x0039BAD2, 56 bytes.
// Adds arg2 to one of +0x14/+0x18/+0x1c based on input+0x108/+0x113 bits, always to +0x1E0.
// Evidence: 7 callers, adjacency to Rva0039BAA0Copy family, ret 8 with 2 args.

struct Rva0039BAD2Input
{
	char m_pad00[0x108];
	unsigned char m_108;
	char m_pad109[0x113 - 0x109];
	unsigned char m_113;
};

class Rva0039BAD2
{
public:
	void rva0039BAD2(Rva0039BAD2Input *a, int v);

private:
	char m_pad00[0x14];
	int m_14;
	int m_18;
	int m_1C;
	char m_pad20[0x1E0 - 0x20];
	int m_1E0;
};

void Rva0039BAD2::rva0039BAD2(Rva0039BAD2Input *a, int v)
{
	if (a != 0 && !(a->m_113 & 4))
	{
		if (a->m_108 & 0x80)
			m_18 += v;
		else
			m_14 += v;
	}
	else
		m_1C += v;
	m_1E0 += v;
}
