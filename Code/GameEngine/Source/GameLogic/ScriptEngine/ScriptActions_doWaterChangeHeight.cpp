// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doWaterChangeHeight@ScriptActions@@QAEXPAVParameter@@M@Z @0x003BC306 55B: script TerrainLogic slot 0x74 then slot 0x7c with floats.
// Evidence: mov ecx,[0xDFEC50]=TheTerrainLogic push [esp+4] mov eax,[ecx] call [eax+0x74] test eax je; mov ecx,[TheTerrainLogic] fld [0xC1FE44]=g_00C1FE44 mov edx,[ecx] push 1 push ecx push ecx fstp [esp+4] fld [esp+0x14] fstp [esp] push eax call [edx+0x7c] ret 8; caller 0x003CCFFF; sibling doUnitStopSequentialScript same stdcall shape.
#include "../../../Include/GameLogic/ScriptParameter.h"

class TerrainLogic
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void *s29(Parameter *p);
	virtual void s30();
	virtual void s31(void *a, float b, float c, int d);
};
extern TerrainLogic *TheTerrainLogic;
// g_00C1FE44 was the retail address alias (RVA 0x0081FE44) of the constant 999999.9f; the literal is the source.

void ScriptActions::doWaterChangeHeight(Parameter *param, float f)
{
	void *res = TheTerrainLogic->s29(param);
	if (res == 0)
		return;
	TheTerrainLogic->s31(res, f, 999999.9f, 1);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
