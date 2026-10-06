// cl: /MD
// ?rva00084024@Rva00084024@@QAEXXZ @0x00084024 49B
// Clears per-node fields while walking +0x1320 chain from +0x10 head:
// byte +0x1310 to 0, byte +0x131D to 1, dwords +0x130C/+0x1308/+0x30/+0x34 to 0.
// Evidence: retail loop bytes, caller 0x00084058, no calls or globals.
class Rva00084024Node
{
public:
	char m_pad00[0x30];
	int m_30;
	int m_34;
	char m_pad38[0x12D0];
	int m_1308;
	int m_130C;
	unsigned char m_1310;
	char m_pad1311[0xC];
	unsigned char m_131D;
	char m_pad131E[0x2];
	Rva00084024Node *m_next;
};

class Rva00084024
{
public:
	void rva00084024();
private:
	char m_pad00[0x10];
	Rva00084024Node *m_head;
};

void Rva00084024::rva00084024()
{
	Rva00084024Node *p = m_head;
	while (p != 0)
	{
		p->m_1310 = 0;
		p->m_131D = 1;
		p->m_130C = 0;
		p->m_1308 = 0;
		p->m_30 = 0;
		p->m_34 = 0;
		p = p->m_next;
	}
}
