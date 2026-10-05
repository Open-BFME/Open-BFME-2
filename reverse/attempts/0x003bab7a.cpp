// ?Rva003BAB7A@@YGXMMMM@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /arch:SSE
// ?Rva003BAB7A@@YGXMMMM@Z @0x003BAB7A 81B: free stdcall 4 floats; TheTacticalView slot 0xec with (a1, int(a2*s), a3*s, a4*s) scaled by g_00BBE358.
// Evidence: ret 0x10; fld [esp+4]; movss xmm0 [0xBBE358]; movss xmm1 [esp+0x10]; mulss; push ecx twice then movss fill; cvttss2si edx; push edx/ecx; fstp [esp]; call [eax+0xec]; caller 0x003CAC0A.

extern float g_00BBE358;

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
	virtual void s57();
	virtual void s58();
	virtual void s059(float a1, int a2, float a3, float a4);
};

extern TacticalView *TheTacticalView;

// ?Rva003BAB7A@@YGXMMMM@Z present-unmatched
void __stdcall Rva003BAB7A(float a1, float a2, float a3, float a4)
{
	float s = g_00BBE358;
	float f4 = a4;
	float f3 = a3;
	float f2 = a2;
	TheTacticalView->s059(a1, (int)(f2 * s), f3 * s, f4 * s);
}
