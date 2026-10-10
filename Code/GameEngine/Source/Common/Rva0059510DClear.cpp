// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva0059510D@Rva0059510D@@QAEXXZ @0x0059510D 54B: clear 8 GameNetwork drain slots at this+0x14. Evidence: rowed UDP dtor 0x00594918 plus operator delete 0x0002FD60; caller 0x0059515C.
class UDP
{
public:
	~UDP();
};

struct Rva0059510DEntry
{
	UDP *ptr;
	unsigned short flag;
	char _pad[2];
};

class Rva0059510D
{
public:
	void rva0059510D();
private:
	char m_lead[0x14];
	Rva0059510DEntry m_entries[8];
};

void Rva0059510D::rva0059510D()
{
	Rva0059510DEntry *e = m_entries;
	int n = 8;
	do {
		if (e->flag != 0)
			e->flag = 0;
		UDP *p = e->ptr;
		if (p != 0) {
			delete p;
			e->ptr = 0;
		}
		++e;
	} while (--n != 0);
}
