// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoFDH@BfmeThingFDH@@QAEDPAX@Z
// retail 0x00492543, 40 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv893.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// Target-side naming: retail 0x0028D891 is already a matched row,
// ?testBit@Rva0028D891Owner@@QBE_NH@Z ("opaque bit-test twin reusing landed
// Object testStatus unsigned-shr shape, over the flag words at +0x370,
// caller bits 0x12-0x1A"). This body's two calls pass exactly those bits --
// 0x12 and 0x13 -- so the call goes through that one name rather than giving
// the address a second one.
class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;
};

struct BfmeThingFDH
{
	char bfmeGoFDH(void *unused);
};

char BfmeThingFDH::bfmeGoFDH(void *unused)
{
	Rva0028D891Owner *o = *(Rva0028D891Owner **)((char *)this - 0x18);
	if (o->testBit(0x12))
		return false;
	return o->testBit(0x13) == 0;
}