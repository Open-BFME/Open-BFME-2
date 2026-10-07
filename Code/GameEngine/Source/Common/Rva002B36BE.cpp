// cl: /O1 /MD
// ?rva002B36BE@Rva002B36BE@@QAEXPAX0_N@Z @0x002B36BE 53B.
class Rva0020F832Helper
{
public:
	bool rva0020F832(void *a1, void *a2);
};

class Rva002B296F
{
public:
	void rva002B35DF();
};

class Rva002B36BE
{
public:
	void rva002B36BE(void *a1, void *a2, bool c);

private:
	unsigned char m_pad00[0xB0];
	Rva0020F832Helper *m_b0;
	int m_padB4;
	int m_B8;
	unsigned char m_padBC[0x2D];
	unsigned char m_flagE9;
};

void Rva002B36BE::rva002B36BE(void *a1, void *a2, bool c)
{
	bool r = m_b0->rva0020F832(a1, a2);
	m_flagE9 = r;
	if (c == 0)
		((Rva002B296F *)this)->rva002B35DF();
	m_B8 = -1;
}
