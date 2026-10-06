// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/S3TwoFieldComparators.cpp
// (reference/open-bfme-1 @ 6d943426), recompiled /Os. Both bodies are
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text), where BFME 1's own flags do not. Only these two placed
// bodies are defined here; the donor's Gen_000970a0::bfmeEquals and
// Gen_00477d30::bfmeDispatch stay out, so the unmatched-definition gate passes.
//
//  ?bfmeEquals@Gen_004c1180@@QBEHPBV1@@Z 0x004059CF, 30 bytes
//  ?bfmeEquals@Gen_004b2190@@QBEHPBV1@@Z 0x00567720, 30 bytes
//
// Donor bodies the ledger had split three ways -- a comparison, an eight-byte
// return TRUE aliased to W3DShadowGeometry::init, and a five-byte return FALSE
// aliased to AIUpdateInterface::getAiFreeToExit. The branches inside the first
// part target the third, so all three are one function.
//
// They compare two fields against the same two fields of the argument. Their
// offsets are the only thing that differs -- +0x00 with a 16-bit second field,
// +0x04 and +0x08, +0x08 and +0x0C -- and the 16-bit one is a word compare, so
// that field really is a short.
//
// mov eax,1 rather than mov al,1 makes all of them int-width.

class Gen_004b2190
{
public:
	int bfmeEquals(const Gen_004b2190 *other) const;

private:
	char m_bfmeHead[0x04];
	int m_bfme0004;							// +0x04
	int m_bfme0008;							// +0x08
};

class Gen_004c1180
{
public:
	int bfmeEquals(const Gen_004c1180 *other) const;

private:
	char m_bfmeHead[0x08];
	int m_bfme0008;							// +0x08
	int m_bfme000C;							// +0x0C
};

// ?bfmeEquals@Gen_004b2190@@QBEHPBV1@@Z 0x00567720
int Gen_004b2190::bfmeEquals(const Gen_004b2190 *other) const
{
	if (m_bfme0004 == other->m_bfme0004 && m_bfme0008 == other->m_bfme0008)
		return 1;

	return 0;
}

// ?bfmeEquals@Gen_004c1180@@QBEHPBV1@@Z 0x004059CF
int Gen_004c1180::bfmeEquals(const Gen_004c1180 *other) const
{
	if (m_bfme0008 == other->m_bfme0008 && m_bfme000C == other->m_bfme000C)
		return 1;

	return 0;
}
