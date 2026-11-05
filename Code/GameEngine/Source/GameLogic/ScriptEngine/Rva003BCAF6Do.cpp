// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCAF6Do@ScriptActions@@QAEXPAVParameter@@MMM@Z @0x003BCAF6 65B: script TerrainLogic slot 0x88 then TacticalView slot 0xa8.
// Evidence: mov ecx,[0xDFEC50]=TheTerrainLogic push [esp+4] call [eax+0x88] fld [esp+8] mov ecx,[0xDFEA3C]=TheTacticalView mov edx,[ecx] sub esp,0xc fstp [esp+8] add eax,0xc fld [esp+0x18] fstp [esp+4] fld [esp+0x1c] fstp [esp] push eax call [edx+0xa8] ret 0x10; caller 0x003CD7C5; sibling doWaterChangeHeightOverTime same TerrainLogic float slot shape.
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
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void *s34(Parameter *p);
};
extern TerrainLogic *TheTerrainLogic;

#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003BCAF6Do(Parameter *param, float f2, float f3, float f4)
{
	void *res = TheTerrainLogic->s34(param);
	TheTacticalView->Add_Camera_Shake(*(const Coord3D *)((char *)res + 12), f4, f3, f2);
}
