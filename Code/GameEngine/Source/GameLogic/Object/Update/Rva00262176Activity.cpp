// cl: /O1
// Donor1281192f68 Bfme5TinyTwentyFour.cpp; target262176/29B Ghidra entry.
// Target independently tests owner+4 and timer+10 then compares timer+20
// against7FFFFFFF. Matched AIUpdateInterface query262BA9 calls this body;
// the timer interpretation comes from donor source and original names remain
// unknown. This address-derived view defines no competing canonical class.
#pragma comment(linker, "/alternatename:?rva00262176@Rva003638BA@@QAE_NXZ=?rva00262176@Rva00262176@@QBE_NXZ")

class Rva00262176Timer
{
public:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeDeadline;					// +0x20
};

class Rva00262176
{
public:
	bool rva00262176(void) const;

private:
	int m_bfmeHead;						// +0x00
	int *m_bfmeOwner;					// +0x04
	int m_bfmeGap[2];					// +0x08
	Rva00262176Timer *m_bfmeTimer;				// +0x10
};

// ?rva00262176@Rva00262176@@QBE_NXZ
bool Rva00262176::rva00262176(void) const
{
	if (!m_bfmeOwner)
		return false;

	if (!m_bfmeTimer)
		return false;

	return m_bfmeTimer->m_bfmeDeadline != 0x7FFFFFFF;
}

