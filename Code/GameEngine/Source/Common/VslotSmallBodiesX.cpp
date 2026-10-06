// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) whose shape needs /O2 /G7 (16-byte aligned, add reg,1
// loop steps, lea-scaled indexing with duplicated returns), batch X. As in
// VslotSmallBodiesA-W, each class and method is address-derived unless the
// ledger already names it, and models only what its body touches. Meanings
// are not recovered.

typedef int Int;

// 0x0018E6F0: 0x54 plus the rowed 0x0018D220 size of each of the +0x48
// entries (0x24 bytes each) at +0x50.
class BfmeThingVID
{
public:
	Int bfmeSizeVID();
private:
	char m_pad00[0x24];
};
class Rva0018E6F0
{
public:
	Int rva0018E6F0();
private:
	char m_pad00[0x48];
	Int m_48;
	Int m_4C;
	BfmeThingVID *m_50;
};
Int Rva0018E6F0::rva0018E6F0()
{
	Int total = 0x54;
	for (Int i = 0; i < m_48; i++)
		total += m_50[i].bfmeSizeVID();
	return total;
}

// 0x0018F640: whether entry i has a non-zero word: +0x10 of the 0x18-byte
// entries at +0x58 when present, else +0x14 of the 0x1C-byte entries at
// +0x54.
struct Rva0018F640EntryA
{
	char m_pad00[0x10];
	Int m_10;
	Int m_14;
};
struct Rva0018F640EntryB
{
	char m_pad00[0x14];
	Int m_14;
	Int m_18;
};
class HCompressedAnimClass
{
public:
	bool Has_VisibilityF(Int i) const;
private:
	char m_pad00[0x54];
	Rva0018F640EntryB *m_54;
	Rva0018F640EntryA *m_58;
};
bool HCompressedAnimClass::Has_VisibilityF(Int i) const
{
	if (m_58)
		return m_58[i].m_10 != 0;
	return m_54[i].m_14 != 0;
}
