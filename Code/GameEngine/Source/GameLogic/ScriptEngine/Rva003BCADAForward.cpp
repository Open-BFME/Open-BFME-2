// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCADAForward@@YAXXZ @0x003BCADA 14B: script forwards to TheTacticalView slot 0xa0.
// Evidence: mov ecx,[0xDFEA3C]=TheTacticalView mov eax,[ecx] jmp [eax+0xa0]; caller 0x003CD771; sibling Rva003BBE91Set same TheTacticalView virtual shape.
class TacticalView
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
	virtual void s34();
	virtual void s35();
	virtual void s36();
	virtual void s37();
	virtual void s38();
	virtual void s39();
	virtual void s40();
};
extern TacticalView *TheTacticalView;

void __cdecl Rva003BCADAForward()
{
	TheTacticalView->s40();
}
