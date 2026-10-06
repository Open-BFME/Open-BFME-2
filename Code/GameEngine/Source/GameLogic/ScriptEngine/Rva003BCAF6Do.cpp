// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCAF6Do@@YGXPAVParameter@@MMM@Z @0x003BCAF6 65B: script TerrainLogic slot 0x88 then TacticalView slot 0xa8.
// Evidence: mov ecx,[0xDFEC50]=TheTerrainLogic push [esp+4] call [eax+0x88] fld [esp+8] mov ecx,[0xDFEA3C]=TheTacticalView mov edx,[ecx] sub esp,0xc fstp [esp+8] add eax,0xc fld [esp+0x18] fstp [esp+4] fld [esp+0x1c] fstp [esp] push eax call [edx+0xa8] ret 0x10; caller 0x003CD7C5; sibling Rva003BC33DDo same TerrainLogic float slot shape.
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
	virtual void s29();
	virtual void s30();
	virtual void s31();
	virtual void s32();
	virtual void s33();
	virtual void *s34(Parameter *p);
};
extern TerrainLogic *TheTerrainLogic;

class TacticalView
{
public:
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual void t19();
	virtual void t20();
	virtual void t21();
	virtual void t22();
	virtual void t23();
	virtual void t24();
	virtual void t25();
	virtual void t26();
	virtual void t27();
	virtual void t28();
	virtual void t29();
	virtual void t30();
	virtual void t31();
	virtual void t32();
	virtual void t33();
	virtual void t34();
	virtual void t35();
	virtual void t36();
	virtual void t37();
	virtual void t38();
	virtual void t39();
	virtual void t40();
	virtual void t41();
	virtual void t42(void *a, float b, float c, float d);
};
extern TacticalView *TheTacticalView;

void __stdcall Rva003BCAF6Do(Parameter *param, float f2, float f3, float f4)
{
	void *res = TheTerrainLogic->s34(param);
	TheTacticalView->t42((char *)res + 12, f4, f3, f2);
}
