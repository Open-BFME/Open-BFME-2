// cl: /MD /EHsc
// Split from BfmeConv902.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db:
// game/GameEngine/Source/GameClient/GUI/Rva00435270ApplyLayout.cpp.
// Target 0x00260787 (126B) is the callee of this TU's existing iterator.
// Identity remains address-derived: the readiness callee has the retail string
// "Unrecognized SubTitleRenderState!", supporting the donor's subtitle role.
// Target loads establish each accessed offset; +0x2C is split into color bytes
// by 0x0025FE30. The donor's field meanings are otherwise structural leads.
// All four calls go to native body starts (no thunks); declarations follow
// their ECX this and ret 0/0/24/12 ABI. Use direct members instead of the
// donor's BFME 1 thunk-pointer unions.
class BfmeItemKA
{
public:
	void bfmeDoKA();
private:
	bool rva002602DA();
	void rva002606E6();
	void rva0025FE30(float, float, float, float, int, int);
	void rva0025FCE8(int, int, int);

	char pad00[0x2C];
	int color;
	char pad30[0x1C];
	float left, top, right, bottom;
	char pad5C[4];
	float split60;
	char pad64[4];
	float split68;
};


extern BfmeItemKA **g_bfmeBegKA;
// Second pointer of the shared item container whose first pointer
// (g_bfmeBegKA, retail RVA 0x009FEA44) Rva007B6880Thunks.cpp defines; this
// walker reads it, and no unit defined it. Retail RVA 0x009FEA48, zero-initialized .data.
BfmeItemKA **g_bfmeEndKA;

// Previously recovered from BFME 1 game/GameEngine/Source/Common/BfmeConv902.cpp;
// retail 0x00260805 (33B), still exact with the layout method's compiler flags.
void bfmeGoKA(void)
{
	BfmeItemKA **iter = g_bfmeBegKA;
	BfmeItemKA **end = g_bfmeEndKA;
	while (iter != end) {
		(*iter)->bfmeDoKA();
		++iter;
	}
}
