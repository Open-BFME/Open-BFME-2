// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BBE44Set@@YGX_NH@Z @0x003BBE44 77B leaf caller 0x003CC2BA globals 0xDFEA3C slots 0xB4 0xBC 0xB0 0xC0
// Evidence: TheTacticalView virtual calls with 1 1 and (v, 1/-1); else-branch checks s44==1.
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
	virtual void s41();
	virtual void s42();
	virtual void s43();
	virtual int s44();
	virtual void s45(int v);
	virtual void s46();
	virtual void s47(int v);
	virtual void s48(int a, int b);
};
extern TacticalView *TheTacticalView;
void __stdcall Rva003BBE44Set(bool flag, int v)
{
	if (flag)
	{
		TheTacticalView->s45(1);
		TheTacticalView->s47(1);
		TheTacticalView->s48(v, 1);
	}
	else
	{
		if (TheTacticalView->s44() == 1)
			TheTacticalView->s48(v, -1);
	}
}
