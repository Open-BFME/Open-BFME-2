// ?Rva003BAC6D@@YGXMMMM@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /arch:SSE
// ?Rva003BAC6D@@YGXMMMM@Z @0x003BAC6D 93B: free stdcall 4-float script action scaling three args and deg-to-rad on first forwarding to TacticalView slot 0xf8.
// Evidence: ret 16 four float args; mov ecx [0xDFEA3C TheTacticalView]; movss xmm0 [0xBBE358]; three movss+mulss scales plus movss a0 mulss [RADS_PER_DEGREE] and one cvttss2si int; call [eax+0xf8]; caller 0x003CACEB.
extern float g_00BBE358;
extern "C" float RADS_PER_DEGREE;

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
	virtual void s59();
	virtual void s60();
	virtual void s61();
	virtual void s62(float a, int b, float c, float d);
};

extern TacticalView *TheTacticalView;

// ?Rva003BAC6D@@YGXMMMM@Z present-unmatched
void __stdcall Rva003BAC6D(float a0, float a1, float a2, float a3)
{
	float t3 = g_00BBE358 * a3;
	float t2 = g_00BBE358 * a2;
	int t1 = (int)(g_00BBE358 * a1);
	float t0 = RADS_PER_DEGREE * a0;
	TheTacticalView->s62(t0, t1, t2, t3);
}
