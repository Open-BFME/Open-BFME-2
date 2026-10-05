// cl: /O1
// ?rva004B0FA0@Gen_0028EF10@@QAE_NXZ, retail 0x004B0FA0, 25 bytes.
// Bool getter chasing the Gen_0028EF10 link at +0x9C then tail-calling
// rowed ?Rva004B0E34Get@@YG_NI@Z with *(link->m_bfmeNext + 4); false when
// null. Evidence: same +0x9C member as rowed bfmeValue 0x004B0E1F in
// Bfme5TinyFifteen.cpp; callers 0x0046E783 and 0x004975FA.
bool __stdcall Rva004B0E34Get(unsigned int x);

class BfmeLinkCF
{
public:
	int m_bfmeTag; // +0x00
	int m_bfmeNext; // +0x04
};

class Gen_0028EF10
{
public:
	bool rva004B0FA0();

private:
	char m_bfmeHead[0x9C]; // +0x00
	BfmeLinkCF *m_bfmeLink; // +0x9C
};

bool Gen_0028EF10::rva004B0FA0()
{
	BfmeLinkCF *link = m_bfmeLink;
	if (link)
		return Rva004B0E34Get(*(unsigned int *)(link->m_bfmeNext + 4));
	return false;
}
