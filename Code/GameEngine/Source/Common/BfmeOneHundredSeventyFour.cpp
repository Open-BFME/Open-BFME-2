// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three errands handed straight on: one to a holder that may not be there, one
// to a part of the record itself, and one that asks first which of two to run.

class BfmeSubBJ
{
public:
	virtual void bfmeDoBJ(void);
};

struct BfmeKindBJ
{
	unsigned char m_bfmeHead[0x10];		// 0x00
	unsigned char m_bfmeStop;		// 0x10
};

class BfmeThingBJ
{
public:
	void bfmeGoBJ(void);

private:
	int m_bfmeFirst;			// 0x00
	BfmeKindBJ *m_bfmeKind;			// 0x04
	unsigned char m_bfmeGap[8];		// 0x08
	BfmeSubBJ m_bfmeSub;			// 0x10
};

void BfmeThingBJ::bfmeGoBJ(void)
{
	if (m_bfmeKind->m_bfmeStop != 0)
		return;

	m_bfmeSub.bfmeDoBJ();
}

class BfmeThingBK
{
public:
	virtual void bfmeSpare00BK(void) = 0;
	virtual void bfmeSpare01BK(void) = 0;
	virtual void bfmeSpare02BK(void) = 0;
	virtual void bfmeSpare03BK(void) = 0;
	virtual void bfmeSpare04BK(void) = 0;
	virtual void bfmeSpare05BK(void) = 0;
	virtual unsigned char bfmeTestBK(void) = 0;
	virtual void bfmeNoBK(void) = 0;
	virtual void bfmeYesBK(void) = 0;

	void bfmeGoBK(void);
};

void BfmeThingBK::bfmeGoBK(void)
{
	if (bfmeTestBK() != 0)
		bfmeYesBK();
	else
		bfmeNoBK();
}


