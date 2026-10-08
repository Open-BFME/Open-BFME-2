// ?rva003FE1DB@Rva003FE1DBOwner@@QAEXXZ
// partial score=0.85 date=2026-10-08
// cl: /O1 /MD /DNDEBUG /EHsc
// ?rva003FE1DB@Rva003FE1DBOwner@@QAEXXZ @0x003FE1DB 52B: when the element vector at +0x3C is
// non-empty, pop its front into two owner words at +0x50/+0x54; otherwise clear the flag at +0x5C.
struct Rva003FE1DBElem
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

class Rva003FE1DBVec
{
public:
	Rva003FE1DBElem *m_begin;
	Rva003FE1DBElem *m_end;
	void rva00538E43(Rva003FE1DBElem *out);
};

class Rva003FE1DBOwner
{
public:
	void rva003FE1DB();

private:
	char m_pad00[0x3C];
	Rva003FE1DBVec m_vec;
	int m_50;
	int m_54;
	unsigned char m_5C;
};

// ?rva003FE1DB@Rva003FE1DBOwner@@QAEXXZ @0x003FE1DB
void Rva003FE1DBOwner::rva003FE1DB()
{
	Rva003FE1DBVec *vec = &m_vec;
	int count = ((char *)vec->m_end - (char *)vec->m_begin) >> 4;
	if (count != 0)
	{
		Rva003FE1DBElem front;
		m_vec.rva00538E43(&front);
		m_50 = front.m_04;
		m_54 = front.m_08;
	}
	else
	{
		m_5C = 0;
	}
}
