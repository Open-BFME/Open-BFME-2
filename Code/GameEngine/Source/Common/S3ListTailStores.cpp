// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3ListTailStores.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. The body is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only this one placed
// body is defined here; the donor's Gen_0007b5a0::bfmeAppend stays out, so the
// unmatched-definition gate passes.
//
// 0x000C8990 zeroes +0x04 and +0x08 out of one xor and then stores its
// argument at +0x0C. The ledger kept the first eight bytes and claimed the
// rest as an alias of AudioEventRTS::setPlayingHandle, whose parameter is what
// names the argument type here.

typedef unsigned int UnsignedInt;

class Gen_000c8990
{
public:
	void bfmeSetPlaying(UnsignedInt handle);

private:
	char m_bfmeHead[0x04];
	int m_bfme0004;							// +0x04
	int m_bfme0008;							// +0x08
	UnsignedInt m_bfme000C;						// +0x0C
};

// ?bfmeSetPlaying@Gen_000c8990@@QAEXI@Z 0x002A97DB, 18 bytes
void Gen_000c8990::bfmeSetPlaying(UnsignedInt handle)
{
	m_bfme0004 = 0;
	m_bfme0008 = 0;
	m_bfme000C = handle;
}
