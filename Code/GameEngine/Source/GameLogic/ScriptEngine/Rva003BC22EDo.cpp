// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BC22EDo@@YGXMMM@Z @0x003BC22E 43B: script move camera via TacticalView slot 0xe4 with 3 floats.
// Evidence: fld [esp+0xc] mov ecx,[0xFEA3C]=TheTacticalView mov eax,[ecx] sub esp,0xc fstp [esp+8] fld [esp+0x14] fstp [esp+4] fld [esp+0x10] fstp [esp] call [eax+0xe4] ret 0xc; caller 0x003CC91A; sibling Rva003E7FD5 same TacticalView dummy pattern.
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
    virtual void slot57(float a, float b, float c);
};
extern TacticalView *TheTacticalView;

void __stdcall Rva003BC22EDo(float a, float b, float c)
{
	TheTacticalView->slot57(a, b, c);
}
