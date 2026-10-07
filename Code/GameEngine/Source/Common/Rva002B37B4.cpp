// cl: /O1 /MD
// ?rva002B37B4@Rva002B37B4@@QAEXPAURva002B37B4P1@@PAURva002B37B4P2@@@Z @0x002B37B4 75B.
class Rva0020F2F1Helper
{
public:
	void rva0020F2F1(void *a1, void *a2);
};

struct Rva002B37B4P1
{
	unsigned char m_pad00[0x12C];
	void *m_12C;
	unsigned char m_pad130[0xC];
	void *m_13C;
};

struct Rva002B37B4P2
{
	unsigned char m_pad00[0x14];
	void *m_14;
	unsigned char m_pad18[0x3AC];
	unsigned char m_3C4;
};

class Rva002B36BE
{
public:
	void rva002B36BE(void *a1, void *a2, bool c);
};

class Rva002B37B4
{
public:
	void rva002B37B4(Rva002B37B4P1 *a1, Rva002B37B4P2 *a2);

private:
	unsigned char m_pad00[0xB0];
	Rva0020F2F1Helper *m_b0;
	int m_padB4;
	int m_B8;
};

void Rva002B37B4::rva002B37B4(Rva002B37B4P1 *a1, Rva002B37B4P2 *a2)
{
	if (a2->m_3C4 != 0)
		return;
	if (a1->m_13C == a2->m_14)
		return;
	m_B8 = (int)a1->m_12C;
	m_b0->rva0020F2F1(a1, a2);
	((Rva002B36BE *)this)->rva002B36BE(a1, a2, true);
}
