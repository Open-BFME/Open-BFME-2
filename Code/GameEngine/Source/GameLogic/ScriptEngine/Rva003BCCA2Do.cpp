// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCCA2Do@@YAXXZ @0x003BCCA2 36B: free check GlobalData byte +0x11CB then Display slot 0x150 with (10000,1).
// Evidence: retail mov eax,[0xDFE758]=TheWritableGlobalData cmp [eax+0x11CB],0 jne ret; mov ecx,[0xDFE9D8]=TheDisplay mov eax,[ecx] push 1 push 0x2710 call [eax+0x150]; caller 0x003CDC74; neighbours Rva003BCBC7Set Rva003BCCC6Do same dir.
class GlobalData
{
public:
	char m_pad[0x11CB];
	unsigned char m_flag11CB;
};
extern GlobalData *TheWritableGlobalData;

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
    virtual void s78();
    virtual void s79();
    virtual void s80();
    virtual void s81();
    virtual void s82();
    virtual void s83();
    virtual void slot84(int a, int b);
};
extern Display *TheDisplay;

void __cdecl Rva003BCCA2Do()
{
	if (TheWritableGlobalData->m_flag11CB != 0)
		return;
	TheDisplay->slot84(10000, 1);
}
