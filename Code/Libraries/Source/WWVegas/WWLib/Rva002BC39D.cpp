// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ?rva002BC39D@Rva002BBBE7@@QAEXXZ @0x002BC39D 41B.
// Clear guarded by count at +4: recurse via rowed 0x002BBBE7 on header+4,
// reset header links to self and zero counts.
// Evidence: chain lane; callee rowed 0x002BBBE7; callers at 0x002BC60C 0x002BC778 0x002BD57B 0x00500D7D plus tail jmps 0x002BC588 0x002BC5CE.

struct Node002BBBE7;

struct Header002BC39D {
	int m_00;
	Node002BBBE7 *m_04;
	Header002BC39D *m_08;
	Header002BC39D *m_0C;
};

class Rva002BBBE7
{
public:
	void rva002BBBE7(Node002BBBE7 *n);
	void rva002BC39D();
private:
	Header002BC39D *m_00;
	int m_04;
};

void Rva002BBBE7::rva002BC39D()
{
	if (m_04 != 0) {
		rva002BBBE7(m_00->m_04);
		m_00->m_08 = m_00;
		m_00->m_04 = 0;
		m_00->m_0C = m_00;
		m_04 = 0;
	}
}
