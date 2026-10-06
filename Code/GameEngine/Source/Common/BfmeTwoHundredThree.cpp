// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three errands: a run told two things, a held thing swapped for another with
// the counts kept straight, and two things compared for sameness.
// ?bfmeSameGX@@YAHPAVBfmeThingGX@@0@Z
// retail 0x00405976, 54 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/BfmeTwoHundredThree.cpp (reference/open-bfme-1
// @ 6d943426). Byte-identical to retail once relocations are masked (unique hit
// on unclaimed .text). Only the placed body is defined here; the donor's other
// two bodies (bfmeTellGY, bfmeSetGW) and their classes are omitted.

// Two things compared for sameness: both kinds must agree (slot 0x14) and then
// the left must accept the right (slot 0x10). Both callees are __thiscall with
// no stack result slot -- the only push is the argument passed to the second --
// so each returns its value directly in eax.

class BfmeThingGX;

class BfmeThingGX
{
public:
	virtual void bfmeSpare000GX(void) = 0;
	virtual void bfmeSpare001GX(void) = 0;
	virtual void bfmeSpare002GX(void) = 0;
	virtual void bfmeSpare003GX(void) = 0;
	virtual unsigned char bfmeMatchGX(BfmeThingGX *other) = 0;
	virtual int bfmeKindGX(void) = 0;
};

int bfmeSameGX(BfmeThingGX *left, BfmeThingGX *right)
{
	if (left->bfmeKindGX() == right->bfmeKindGX())
	{
		if (left->bfmeMatchGX(right) != 0)
			return 1;
	}

	return 0;
}
