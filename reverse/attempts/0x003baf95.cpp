// ?Rva003BAF95@@YGXMMMM@Z
// partial score=0.88 date=2026-10-05
// cl: /O1 /arch:SSE
// ?Rva003BAF95@@YGXMMMM@Z @0x003BAF95 83B: free stdcall 4-float script action scaling three args and forwarding to TacticalView slot 0xcc.
// Evidence: ret 16 four float args; mov ecx [0xDFEA3C TheTacticalView]; movss xmm0 [0xBBE358]; fld/fstp passthrough plus two movss scales and one cvttss2si int; push 1; call [eax+0xcc]; caller 0x003CAEEE.

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
	virtual void s51(float a, int b, int c, float d, float e);
};

extern TacticalView *TheTacticalView;

// ?Rva003BAF95@@YGXMMMM@Z present-unmatched
void __stdcall Rva003BAF95(float a0, float a1, float a2, float a3)
{
	TacticalView *tv = TheTacticalView;
	tv->s51(a0, (int)(a1 * g_00BBE358), 1, a2 * g_00BBE358, a3 * g_00BBE358);
}
