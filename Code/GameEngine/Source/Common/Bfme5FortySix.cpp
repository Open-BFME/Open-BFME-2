// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Five more: a guarded four-word copy, an indexed read behind a size test, a
// two-flag global check, a three-argument constructor, and a visibility
// test.

class BfmeQuadDO
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
	int m_bfmeFourth;					// +0x0C
};

class Gen_00478220
{
public:
	int bfmeGet(BfmeQuadDO *out) const;

private:
	int m_bfmeHead[5];					// +0x00
	BfmeQuadDO m_bfmeQuad;					// +0x14
};

// ?bfmeGet@Gen_00478220@@QBEHPAVBfmeQuadDO@@@Z
int Gen_00478220::bfmeGet(BfmeQuadDO *out) const
{
	if (out != 0)
		*out = m_bfmeQuad;

	return 0;
}
