// cl: /MD
//
// ?rva002D22D5@Rva002D22CA@@QAE_NXZ
// RVA 0x002D22D5 size 108. Duplicate-unk validator over the 12 tables at +0x0C:
// each entry is {key@+0, name@+4, unk@+8} terminating on key==0; returns false
// when two distinct entries share the same nonzero unk. Evidence: tail-called
// from slot1 0x002D2457 via jmp; same Rva002D22CA class as 0x002D23ED (tables
// array proven by its store at +0x0C+index*4); no callees.

struct TableEntry
{
	int key;
	const char *name;
	int unk;
};

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase();
	virtual ~GameEngineDeletingBase();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

class Rva002D22CA : public GameEngineDeletingBase
{
public:
	bool rva002D22D5();

private:
	void *m_tables[12];
};

bool Rva002D22CA::rva002D22D5()
{
	bool ok = true;
	void **pOuter = m_tables;
	int nOuter = 12;
	do
	{
		for (TableEntry *e = (TableEntry *)*pOuter; e != 0 && e->key != 0; e++)
		{
			int unk = e->unk;
			if (unk == 0)
				continue;
			void **pMiddle = m_tables;
			int nMiddle = 12;
			do
			{
				for (TableEntry *f = (TableEntry *)*pMiddle; f != 0 && f->key != 0; f++)
				{
					if (e == f)
						continue;
					if (unk != f->unk)
						continue;
					ok = false;
				}
				pMiddle++;
			} while (--nMiddle != 0);
		}
		pOuter++;
	} while (--nOuter != 0);
	return ok;
}
