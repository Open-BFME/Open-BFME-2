// ??0Rva00588FFA@@QAE@PAVThing@@PBVModuleData@@@Z
// cl: /DNDEBUG /MD
//
// ??0Rva00588FFA@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00588FFA, 53 bytes.
// Behavior module base ctor over rowed BehaviorModule 0x253330. Writes the
// member at +0x10 (0x00C6FFFC, then the folded vtable slot 0x00C4A50C), and
// zeroes +0x14, then installs the folded vtable slots 0x00C700C4 at +0 and
// 0x00C70008 at +0xC. Sole caller is PillageModule ctor 0x484F0D.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;

// The retail table at RVA 0x008700C4: 12 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00484EF4@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@UpdateModule@@MAEXXZ")();
void __identifier("?Rva0058902FGet@@YAHXZ")();
void __identifier("?xfer@Rva00589051@@MAEXPAVXfer@@@Z")();
int __cdecl _purecall(void);
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
}
extern const void *const g_008700C4[12] = {
	(const void *)&__identifier("??_GRva00484EF4@@UAEPAXI@Z"), // slot 0 0x00589035
	(const void *)&__identifier("?loadPostProcess@UpdateModule@@MAEXXZ"), // slot 1 0x0058B03E
	(const void *)&__identifier("?Rva0058902FGet@@YAHXZ"), // slot 2 0x0058902F
	(const void *)&__identifier("?xfer@Rva00589051@@MAEXPAVXfer@@@Z"), // slot 3 0x00589051
	(const void *)&__identifier("_purecall"), // slot 4 0x0003B810
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
};
extern "C" const void *const __identifier("??_7Rva00484F5D@@6BMiBase1@@@")[];
extern "C" const void *const __identifier("??_7Rva00484EF4@@6B@")[];
// The retail table at RVA 0x0086FFFC: 2 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
int __cdecl _purecall(void);
}
extern const void *const g_0086FFFC[2] = {
	(const void *)&__identifier("_purecall"), // slot 0 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 1 0x0003B810
};

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

// Constructor-only base view: the explicit native table stores below retain
// construction state while the complete DamagerModule class is recovered.
class __declspec(novtable) Rva00588FFA : public BehaviorModule
{
public:
	Rva00588FFA(Thing *thing, const ModuleData *data);

private:
	const void *m_10; // +0x10, init g_0086FFFC then overwritten ??_7Rva00484EF4@@6B@
	int m_14; // +0x14, and-zeroed
};

Rva00588FFA::Rva00588FFA(Thing *thing, const ModuleData *data)
	: BehaviorModule(thing, data)
{
	*(volatile unsigned *)&m_10 = (unsigned)g_0086FFFC;
	_ReadWriteBarrier();
	m_14 = 0;
	*(const void **)this = g_008700C4;
	*(const void **)((char *)this + 0x0C) = __identifier("??_7Rva00484F5D@@6BMiBase1@@@");
	*(const void **)((char *)this + 0x10) = __identifier("??_7Rva00484EF4@@6B@");
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
