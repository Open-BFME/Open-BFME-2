// ?rva00577634@Rva005765D1@@QAEXH@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00577634@Rva005765D1@@QAEXH@Z, retail 0x00577634..0x005776A7 (115
// bytes, EH, RET 4): slot 63 of Rva005765D1's vtable. The holder at +0x14 of
// the +0x18 object either already holds an entry for the given id -- which is
// then re-run (rowed 0x00576FBA) -- or is cleared (rowed 0x0057702E) and given
// a new 0x1C-byte entry for that object and id (0x005774E3, not yet rowed;
// pinned) through its rowed setter 0x0057704C. The holder's clear and set are
// rowed under different view names and are called by them.

struct Rva0057702EBase;

class Rva00576FBA
{
public:
	void rva00576FBA();
	unsigned char m_pad00[0x0C];
	int m_id0C;
};

class Rva0057702E
{
public:
	void rva0057702E();
	Rva00576FBA *m_entry;
};

class Rva0057704C
{
public:
	void rva0057704C(Rva0057702EBase *entry);
};

struct Rva00577634Owner
{
	unsigned char m_pad00[0x14];
	Rva0057702E m_holder14;
};

class Rva005774E3
{
public:
	Rva005774E3(Rva00577634Owner *owner, int id);
private:
	unsigned char m_pad00[0x1C];
};

class Rva005765D1
{
public:
	void rva00577634(int id);
private:
	unsigned char m_pad00[0x18];
	Rva00577634Owner *m_18;
};

void Rva005765D1::rva00577634(int id)
{
	Rva0057702E *holder = &m_18->m_holder14;
	if (holder->m_entry && holder->m_entry->m_id0C == id)
	{
		holder->m_entry->rva00576FBA();
		return;
	}
	holder->rva0057702E();
	reinterpret_cast<Rva0057704C *>(&m_18->m_holder14)->rva0057704C((Rva0057702EBase *)new Rva005774E3(m_18, id));
}
