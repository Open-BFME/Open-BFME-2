// cl: /DNDEBUG /MD
// ?rva005E2371@Rva005E2371@@QAEXH@Z @0x005E2371 53B.
// If +0x10->m_0 null return; else getter 0x005CB265 via m_8->+0x10 vs it;
// if equal calls rowed 0x005CB260 forwarder; then clear +0x10 via rowed 0x002BED91.
// Ret 4 ignores int. Address-derived; same getter/tail shape as 0x005E0D9C.
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva002BED91
{
public:
	void clear();
	int m_0;
};

class Rva005E2371M8
{
public:
	unsigned char m_pad[0x10];
	Rva005CB265 *m_10;
};

class Rva005E2371
{
public:
	void rva005E2371(int ignored);
protected:
	unsigned char m_pad[8];
	Rva005E2371M8 *m_8;
	int m_pad0C;
	Rva002BED91 m_10;
};

void Rva005E2371::rva005E2371(int ignored)
{
	(void)ignored;
	int b = m_10.m_0;
	if (b == 0)
		return;
	int r = m_8->m_10->Rva005CB265::rva005CB265();
	if (r == b)
		((Rva005CB260 *)m_8->m_10)->rva005CB260();
	m_10.clear();
}
