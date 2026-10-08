// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/V4SubObjectSizeGuard.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?refresh@Rva003BBA00@@QAE_NXZ 0x003FD2F6 (43B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// One 44-byte __thiscall member that asks a sub-object at +0xC how many entries
// it has and either gives up or copies one field out of its first entry:
//
//     push esi / mov esi,ecx / push edi / lea edi,[esi+0xC] / mov ecx,edi
//     call <count> / cmp eax,2 / jge .have
//     pop edi / mov al,1 / pop esi / ret
//   .have:
//     push 0 / mov ecx,edi / call <at> / mov eax,[eax+0x18]
//     mov [esi+0x18],eax / pop edi / xor al,al / pop esi / ret
//
// WHAT THE BYTES SHOW.  `lea edi,[esi+0xC]` and then TWO __thiscall calls on that
// same address make +0xC a SUB-OBJECT of this class, not a stored pointer -- a
// pointer would have been loaded, not computed.  The first call takes nothing
// and answers in eax; `cmp eax,2 / jge` is a SIGNED comparison, so the count is a
// signed int.  The second call takes one pushed zero and answers a pointer that
// is immediately dereferenced at +0x18, and that dword is stored to +0x18 of
// this object -- same offset on both sides.
//
// BOTH RESULT CONSTANTS ARE MATERIALISED SEPARATELY (`mov al,1` on one path,
// `xor al,al` on the other) with the epilogue duplicated, so the two returns are
// two constants in the source rather than one computed value.
//
// The count is the rowed FrameData::getCommandCount and the indexed accessor
// the rowed Rva00504138::rva00504138.
//
// IDENTITY IS NOT RECOVERED.  Every other name is derived from an address.

class Gen003BBA00Element
{
public:
	char m_pad00[ 0x18 ];
	int  m_at18;
};

class FrameData
{
public:
	unsigned int getCommandCount();
};

class Rva00504138
{
public:
	void *rva00504138( int index );
};

class Gen_00064730
{
public:
	int                   m();
	Gen003BBA00Element *  at( int index );
};

class Rva003BBA00
{
public:
	bool refresh();
	char m_pad00[ 0x18 ];
	int  m_at18;
};
bool Rva003BBA00::refresh()
{
	Gen_00064730 *entries = (Gen_00064730 *)( (char *)this + 0xC );
	if( (int)((FrameData *)entries)->getCommandCount() < 2 )
		return true;
	m_at18 = ((Gen003BBA00Element *)((Rva00504138 *)entries)->rva00504138( 0 ))->m_at18;
	return false;
}
