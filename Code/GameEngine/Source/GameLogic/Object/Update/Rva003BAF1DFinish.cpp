// ?Rva003BAF1D@@YGXMMMM@Z
// cl: /O1 /arch:SSE
// ?Rva003BAF1D@@YGXMMMM@Z @0x003BAF1D 120B: free stdcall four floats normalizing
// deg-to-rad minus TacticalView slot 0x100 base then scaling to slot 0xcc.
// Evidence: ret 16; mov ecx [TheTacticalView] call [eax+0x100]; fld [esp+4]
// fmul [RADS] fsub normalizeAngle row; fmul [g_00C1FE40]; movss+mulss scales plus
// cvtt int plus push 0; call [eax+0xcc]; caller 0x003CAEA3.
//
// The deg-to-rad product and the normalizeAngle call must stay fused into a
// single expression: naming the result `n` first makes MSVC 7.1 materialize the
// call's float return through xmm0, which forces the subsequent scale into SSE
// (mov ecx,[scale] / mulss) where retail keeps the whole tail on the x87 stack
// (fmul dword ptr ds:scale). Fusing them leaves the call's return on the FP
// stack so the scale is an x87 memory multiply, which is what retail emits.
// The x87 scale literal is 0.15915494f (180/pi, radians per degree) read from
// the retail constant at RVA 0x0081FE40; the bank guessed 1000.0f there, which
// still matched byte-for-byte under DIR32 copying but failed the float-ref gate.
float __cdecl normalizeAngle(float v);

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
	virtual void s51(float k, int i1, int i2, float f1, float f2);
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
	virtual float s64();
};
extern TacticalView *TheTacticalView;

void __stdcall Rva003BAF1D(float a0, float a1, float a2, float a3)
{
	float base = TheTacticalView->s64();
	float f3 = a3 * 1000.0f;
	float f2 = a2 * 1000.0f;
	int i1 = (int)(a1 * 1000.0f);
	float k = normalizeAngle(a0 * 0.017453292f - base) * 0.15915494f;
	TheTacticalView->s51(k, i1, 0, f2, f3);
}
