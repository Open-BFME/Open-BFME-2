// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three errands: a piece asked and settled before its next is read, three rows
// of pieces each run to the end, and a target marked and asked before it is
// ?bfmeGetIJ@BfmeThingIJ@@QAEHXZ
// retail 0x001327AE, 42 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeTwoHundredTwelve.cpp (reference/open-bfme-1 @
// 6d943426). Byte-identical to retail once relocations are masked (unique hit
// on unclaimed .text). Only the placed body is defined here; the donor's other
// two bodies (bfmeClearIK, bfmeGoIN) and their classes are omitted.

// A piece asked and settled before its next is read: ask the current item,
// settle it if it is unset, then advance to the next and return its value, or
// 1 when there is no next.

// handed the piece.

class BfmeItemIJ
{
public:
	virtual void bfmeSpare000IJ(void) = 0;
	virtual void bfmeSpare001IJ(void) = 0;
	virtual void bfmeSpare002IJ(void) = 0;
	virtual void bfmeSpare003IJ(void) = 0;
	virtual void bfmeSpare004IJ(void) = 0;
	virtual void bfmeSpare005IJ(void) = 0;
	virtual void bfmeSpare006IJ(void) = 0;
	virtual void bfmeSpare007IJ(void) = 0;
	virtual void bfmeSpare008IJ(void) = 0;
	virtual void bfmeSpare009IJ(void) = 0;
	virtual unsigned char bfmeAskIJ(void) = 0;
	virtual void bfmeDoIJ(void) = 0;

	unsigned char m_bfmeGap[0x10];		// 0x04
	BfmeItemIJ *m_bfmeNext;			// 0x14
	unsigned char m_bfmeMore[0x18];		// 0x18
	int m_bfmeValue;			// 0x30
};

class BfmeThingIJ
{
public:
	int bfmeGetIJ(void);

private:
	BfmeItemIJ *m_bfmeItem;			// 0x0
};

int BfmeThingIJ::bfmeGetIJ(void)
{
	BfmeItemIJ *at = m_bfmeItem;

	if (at != 0)
	{
		if (at->bfmeAskIJ() == 0)
			at->bfmeDoIJ();

		at = at->m_bfmeNext;

		if (at != 0)
			return at->m_bfmeValue;
	}

	return 1;
}
