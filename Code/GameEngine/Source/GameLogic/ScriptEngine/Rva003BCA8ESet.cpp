// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCA8ESet@ScriptActions@@QAEX_N@Z @0x003BCA8E 19B: script sets GameLogic +0x9b byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE78C]=TheGameLogic mov [ecx+0x9b],al ret 4; caller 0x003CD7E0; sibling Rva003BCA7BSet +0x9a same shape.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// The canonical GameLogic header pads over this script-state field; the
// store goes through a view of the real TheGameLogic.
struct GameLogicScriptStateView
{
	unsigned char m_pad[0x9b];
	unsigned char m_9b;
};

void ScriptActions::Rva003BCA8ESet(bool b)
{
	((GameLogicScriptStateView *)TheGameLogic)->m_9b = b;
}
