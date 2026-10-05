// cl: /O1 /DNDEBUG /MD
// Dump lane range 13: contiguous Pathfinder cell-query predicates around
// 0x002E9897. Each forwards (this, b, a) to the rowed lookup 0x001E3647
// (forward push order), then tests the low nibble of the dword at +0x0C
// (plus bit 16/17) of the returned record. thiscall with ecx passthrough;
// ?rva names: class lead from the 0x002E9871 Pathfinder pin, identities unproven.
class Pathfinder
{
public:
	void *rva001E3647(int a, int b);
	bool rva002E9897(int a, int b);
	bool rva002E98C6(int a, int b);
	bool rva002E98EA(int a, int b);
	bool rva002E9919(int a, int b);
	bool rva002E9948(int a, int b);
};
struct Rva001E3647Result
{
	char m_pad[0x0C];
	unsigned int m_flags;
};
// ?rva002E9897@Pathfinder@@QAE_NHH@Z @0x002E9897 47B: tag&0xf in {1,7}.
bool Pathfinder::rva002E9897(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647(b, a);
	if (rec != 0)
	{
		int tag = rec->m_flags & 0x0F;
		return tag == 1 || tag == 7;
	}
	return false;
}
// ?rva002E98C6@Pathfinder@@QAE_NHH@Z @0x002E98C6 36B: tag&0xf == 2.
bool Pathfinder::rva002E98C6(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647(b, a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 2 : false;
}
// ?rva002E98EA@Pathfinder@@QAE_NHH@Z @0x002E98EA 47B: tag==4 && bit17.
// ?Pathfinder::rva002E98EA present-unmatched
bool Pathfinder::rva002E98EA(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647(b, a);
	if (rec != 0)
	{
		int val = rec->m_flags;
		return (val & 0x0F) == 4 && ((val >> 17) & 1);
	}
	return false;
}
// ?rva002E9919@Pathfinder@@QAE_NHH@Z @0x002E9919 47B: tag==2 && !bit16.
// ?Pathfinder::rva002E9919 present-unmatched
bool Pathfinder::rva002E9919(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647(b, a);
	if (rec != 0)
	{
		int val = rec->m_flags;
		return (val & 0x0F) == 2 && !((val >> 16) & 1);
	}
	return false;
}
// ?rva002E9948@Pathfinder@@QAE_NHH@Z @0x002E9948 38B: null->true else tag==5.
bool Pathfinder::rva002E9948(int a, int b)
{
	Rva001E3647Result *rec = (Rva001E3647Result *)rva001E3647(b, a);
	return rec != 0 ? (rec->m_flags & 0x0F) == 5 : true;
}
