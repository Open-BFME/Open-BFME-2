// ?rva002766F8@Rva002766F8Host@@QAEXPAURva002766F8Arg@@@Z
// partial score=0.7 date=2026-10-05
// cl: /O1 /MD
struct Rva002766F8Arg
{
	int m_key;
};
struct Rva002DFE78C
{
	unsigned char m_pad[0x40];
	unsigned int m_40;
};
extern Rva002DFE78C *g_00DFE78C;
class Rva00239099Slot
{
public:
	void rva00239099(void *arg);
};
struct Rva002766F8Pair
{
	int m_key;
	unsigned int m_val;
};
class Rva002766F8Host
{
public:
	void rva002766F8(Rva002766F8Arg *arg);
private:
	unsigned char m_pad[0x38C];
	Rva002766F8Pair m_pairs[3];
};
// ?rva002766F8@Rva002766F8Host@@QAEXPAURva002766F8Arg@@@Z
void Rva002766F8Host::rva002766F8(Rva002766F8Arg *arg)
{
	int key = arg->m_key;
	int best = -1;
	volatile int i = 0;
	unsigned int *pVal = &m_pairs[0].m_val;
	for (; i < 3; i++, pVal += 2)
	{
		if (*(pVal - 1) == key)
		{
			best = i;
			break;
		}
		if (best == -1)
			best = i;
		else if (*pVal < m_pairs[best].m_val)
			best = i;
	}
	((Rva00239099Slot *)&m_pairs[best])->rva00239099(arg);
	m_pairs[best].m_val = g_00DFE78C->m_40;
}
