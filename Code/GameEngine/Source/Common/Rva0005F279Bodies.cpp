// cl: /O1 /DNDEBUG /MD
class Rva0005F279Elem
{
public:
	bool rva0005106A();
};

class Rva0005F279Host
{
public:
	void rva0005F279();
	void rva0005EA8F(Rva0005F279Elem *e);
	unsigned char m_pad[0xBD4];
	void *m_base;
	int m_count;
};

void Rva0005F279Host::rva0005F279()
{
	int i = 0;
	int off = 0;
	if (m_count <= 0)
		return;
	do {
		if (((Rva0005F279Elem *)((char *)m_base + off))->rva0005106A())
			rva0005EA8F((Rva0005F279Elem *)((char *)m_base + off));
		++i;
		off += 0x48;
	} while (i < m_count);
}
