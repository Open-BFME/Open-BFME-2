// Open-BFME5 conversions.

struct BfmeElemVJX;

struct BfmeCmpVJX
{
	char m_bfme00;
};

void __cdecl bfmeSortAVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);
void __cdecl bfmeSortBVJX(BfmeElemVJX *a, BfmeElemVJX *b, BfmeCmpVJX c);

struct BfmeRangeVJX
{
	BfmeElemVJX *m_bfme00;
	BfmeElemVJX *m_end;
};

class BfmeThingVJX
{
public:
	void Sort(int mode);
	BfmeRangeVJX *m_bfme00;
};

void BfmeThingVJX::Sort(int mode)
{
	BfmeCmpVJX comparator;
	switch (mode)
	{
	case 2:
		comparator.m_bfme00 = 0;
		bfmeSortAVJX(m_bfme00->m_bfme00, m_bfme00->m_end, comparator);
		break;
	case 1:
		comparator.m_bfme00 = 0;
		bfmeSortBVJX(m_bfme00->m_bfme00, m_bfme00->m_end, comparator);
		break;
	}
}
