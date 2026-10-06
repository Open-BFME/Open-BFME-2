// ?Rva003BBB51Set@@YGX_N@Z
// partial score=0.7027 date=2026-10-06
// ?Rva003BBB51Set@@YGX_N@Z
// partial score=0.92 date=2026-10-01
// cl: /O1 /G7
// ?Rva003BBB51Set@@YGX_N@Z @0x003BBB51 45B leaf caller 0x003CBF4F globals TheDisplay TheWritableGlobalData slot 0x138 bytes 0xBE8 0xBEA
// Evidence: cmp byte [esp+4],0 mov ecx,[TheDisplay] mov edx,[TheWritableGlobalData] mov eax,[ecx] je select 0xBE8 else 0xBEA push edx call [eax+0x138] ret 4.
class Display
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
	virtual void s44();
	virtual void s45();
	virtual void s46();
	virtual void s47();
	virtual void s48();
	virtual void s49();
	virtual void s50();
	virtual void s51();
	virtual void s52();
	virtual void s53();
	virtual void s54();
	virtual void s55();
	virtual void s56();
	virtual void s57();
	virtual void s58();
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62();
	virtual void s63();
	virtual void s64();
	virtual void s65();
	virtual void s66();
	virtual void s67();
	virtual void s68();
	virtual void s69();
	virtual void s70();
	virtual void s71();
	virtual void s72();
	virtual void s73();
	virtual void s74();
	virtual void s75();
	virtual void s76();
	virtual void s77();
	virtual void s78(bool);
};
extern Display *TheDisplay;
class GlobalData
{
public:
	char m_pad[0xBE8];
	bool m_be8;
	bool m_be9;
	bool m_bea;
};
extern GlobalData *TheWritableGlobalData;
// ?Rva003BBB51Set@@YGX_N@Z present-unmatched
void __stdcall Rva003BBB51Set(bool b)
{
	Display *d = TheDisplay;
	GlobalData *gd = TheWritableGlobalData;
	d->s78(b ? gd->m_bea : gd->m_be8);
}
