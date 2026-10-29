// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCAA1Set@ScriptActions@@QAEXM@Z @0x003BCAA1 57B: script float sets TheGameLogic+0xa0 scaled or -1.
// Evidence: xorps xmm0 comiss xmm0,[esp+4] jbe else mov eax,[0xDFE78C]=TheGameLogic or [eax+0xa0],-1 jmp ret; else cvtsi2ss xmm0,[0xDBA4E4]=BfmeLogicFramesPerSecond mulss xmm0,[esp+4] mov ecx,[TheGameLogic] cvttss2si eax,xmm0 mov [ecx+0xa0],eax ret 4; caller 0x003CD7FB; sibling doNamedSetStoppingDistance same comiss movss stdcall float shape.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// The canonical GameLogic header pads over this script-state field; the
// store goes through a view of the real TheGameLogic.
struct GameLogicScriptStateView
{
	char m_pad[0xA0];
	int m_A0;
};
extern int BfmeLogicFramesPerSecond;

void ScriptActions::Rva003BCAA1Set(float f)
{
	if (0.0f > f)
		((GameLogicScriptStateView *)TheGameLogic)->m_A0 |= -1;
	else
		((GameLogicScriptStateView *)TheGameLogic)->m_A0 = (int)((float)BfmeLogicFramesPerSecond * f);
}
