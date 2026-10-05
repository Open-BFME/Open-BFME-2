// cl: /O1 /DNDEBUG /MD /EHsc
// ?j_00036124@Glo012F1024Item@@QAEXXZ @0x0056552C 176B BFME1 donor j_00036124 adapted to BFME2 layout Outer at +0x9C and single global g_009FE1C8 with rowed forwarders 0x00210EBF 0x00210ECF 0x00210EE1. Evidence: caller 0x005669A3 bfmeEnter plus donor game/GameEngine/Source/Common/Glo012F1024Entry_bfmeStep.cpp plus retail offsets +0x9C +0xA0 stride 0xC inner stride 8.

class Rva0021294A;
extern Rva0021294A *g_009FE1C8;

struct BfmeE8
{
	char m_body[8];
};

class Rva00210EBF
{
public:
	void rva00210EBF();
};

class Rva00210ECF
{
public:
	void rva00210ECF(const BfmeE8 &x);
};

class Rva00210EE1
{
public:
	void rva00210EE1();
};

struct BfmeElem12
{
	BfmeE8 *m_begin;
	BfmeE8 *m_end;
	char m_tail[4];
};

class BfmeElem12Vector
{
public:
	unsigned int bfmeSize() const { return m_end - m_begin; }
	BfmeElem12 *m_begin;
	BfmeElem12 *m_end;
};

class Glo012F1024Item
{
public:
	void j_00036124();
private:
	char m_pad[0x9C];
	BfmeElem12Vector m_outer;
};

void Glo012F1024Item::j_00036124()
{
	if (m_outer.bfmeSize() != 0)
	{
		((Rva00210EBF *)g_009FE1C8)->rva00210EBF();
		for (unsigned int outer = 0; outer < m_outer.bfmeSize(); ++outer)
		{
			BfmeElem12 *element = m_outer.m_begin + outer;
			for (unsigned int inner = 0; inner < (unsigned int)(element->m_end - element->m_begin); ++inner)
				((Rva00210ECF *)g_009FE1C8)->rva00210ECF(*(element->m_begin + inner));
		}
		((Rva00210EE1 *)g_009FE1C8)->rva00210EE1();
	}
}
