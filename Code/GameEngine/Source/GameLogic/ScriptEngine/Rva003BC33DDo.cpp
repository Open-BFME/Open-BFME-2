// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC33DDo@@YGXPAVParameter@@MMM@Z @0x003BC33D 63B: script TerrainLogic slot 0x74 then slot 0x80 with 3 floats.
// Evidence: mov ecx,[0xDFEC50]=TheTerrainLogic push [esp+4] mov eax,[ecx] call [eax+0x74] test eax je; fld [esp+0x10] mov ecx,[TheTerrainLogic] mov edx,[ecx] sub esp,0xc fstp [esp+8] fld [esp+0x18] fstp [esp+4] fld [esp+0x14] fstp [esp] push eax call [edx+0x80] ret 0x10; caller 0x003CD047; sibling Rva003BC306Do same slot 0x74 then float slot shape.
class Parameter
{
};

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
	virtual void s31();
	virtual void s32(void *a, float b, float c, float d);
};
extern TerrainLogic *TheTerrainLogic;

void __stdcall Rva003BC33DDo(Parameter *param, float f2, float f3, float f4)
{
	void *res = TheTerrainLogic->s29(param);
	if (res == 0)
		return;
	TheTerrainLogic->s32(res, f2, f3, f4);
}
