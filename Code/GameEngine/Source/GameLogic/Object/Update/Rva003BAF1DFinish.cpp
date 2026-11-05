// stlport
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD
#include "GameLogic/ScriptActionsBFME2.h"
// ?Rva003BAF1D@ScriptActions@@QAEXMMMM@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BAF1D@ScriptActions@@QAEXMMMM@Z @0x003BAF1D 120B: ScriptActions member four floats normalizing
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

#include "GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003BAF1D(float a0, float a1, float a2, float a3)
{
	float base = TheTacticalView->getAngle();
	float f3 = a3 * 1000.0f;
	float f2 = a2 * 1000.0f;
	int i1 = (int)(a1 * 1000.0f);
	float k = normalizeAngle(a0 * 0.017453292f - base) * 0.15915494f;
	TheTacticalView->rotateCamera(k, i1, false, f2, f3);
}

// Member ABI proved at each native executeAction3CA4BE call site: ECX=this.
// Canonical ScriptActions owner; address-derived verbs remain uncertain.
