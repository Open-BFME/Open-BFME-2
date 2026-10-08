// cl: /DNDEBUG /MD
//
// ?rva005F4B57@Rva005F4B57@@QAEXXZ @0x005F4B57 56B: thiscall void method
// gated by byte +0x30 then forwarding to Rva005FD956 via rowed helpers.
// Evidence: packet disasm with rowed GetMaxCommandPoints 0x003192B9 plus rowed
// rva00318FBE 0x00318FBE plus rowed rva005FD956 0x005FD956, caller 0x005F5537.

int GetMaxCommandPoints(void *key);

class Rva00318FBE
{
public:
	int rva00318FBE();
};

class Rva005FD956
{
public:
	void rva005FD956(int index, int a, int b);
};

struct Rva005F4B57Holder08
{
	char m_pad00[0x14];
	Rva005FD956 *m_14;
};

class Rva005F4B57
{
public:
	void rva005F4B57();
private:
	char m_pad00[8];
	Rva005F4B57Holder08 *m_08;
	int m_0C;
	Rva00318FBE *m_10;
	char m_pad14[0x30 - 0x14];
	unsigned char m_30;
};

void Rva005F4B57::rva005F4B57()
{
	if (m_30 == 0)
		return;
	Rva005FD956 *p = m_08->m_14;
	if (p != 0)
		p->rva005FD956(m_0C, m_10->rva00318FBE(), GetMaxCommandPoints(m_10));
	m_30 = 0;
}
