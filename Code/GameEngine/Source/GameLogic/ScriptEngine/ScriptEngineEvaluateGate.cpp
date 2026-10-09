// Retail203F0E rejects inactive scripts, unsupported difficulty, and future frames.
// The existing .94 bank supplies the target-derived offsets. The positive
// execution path ends with one true return, preserving native shared false
// branches instead of synthesizing SBB. The receiver and method remain neutral.
// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /arch:SSE
class Rva002A9BF2 { public: void *rva002A9BF2(); };
#include "../../Common/GameLogicObjectLookupView.h"
class Rva002BA8F1Logic { public: char m_pad00[0xF4]; unsigned int m_bitIndex; int m_padF8; unsigned int m_frame; };
extern GameLogic *TheGameLogic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define World ((Rva002BA8F1Logic *)TheLivingWorldLogic)
struct ScriptTimerArg { char m_pad00[0x2B]; unsigned char m_diff0; unsigned char m_diff1; unsigned char m_diff23; char m_pad2E[0x3C-0x2E]; unsigned int m_targetFrame; unsigned char m_enabled; char m_pad41[0x4C-0x41]; float m_zero; };
class ScriptEngine { public: bool rva00203F0E(void *arg); private: char m_pad00[0x1A130]; Rva002A9BF2 *m_player; char m_pad134[0x1A4C4-0x1A130-4]; int m_difficulty; };
bool ScriptEngine::rva00203F0E(void *p) {
	ScriptTimerArg *arg = (ScriptTimerArg *)p;
	arg->m_zero = 0.0f;
	if (arg->m_enabled == 0)
		return false;
	int diff = m_difficulty;
	if (m_player)
		diff = (int)m_player->rva002A9BF2();
	switch (diff) {
	case 0:
		if (arg->m_diff0 == 0)
			return false;
		break;
	case 1:
		if (arg->m_diff1 == 0)
			return false;
		break;
	case 2:
	case 3:
		if (arg->m_diff23 == 0)
			return false;
		break;
	default:
		break;
	}
    GameLogic *logic = TheGameLogic;
    if (!logic->rva001DCD1C())
    {
        if (logic->getFrame() < arg->m_targetFrame)
            return false;
    }
    else
    {
        unsigned int bit = World->m_bitIndex;
        unsigned int mask = 1u << (bit & 31);
        unsigned int *bits = (unsigned int *)((char *)arg + 0x24);
        if ((bits[bit >> 5] & mask) == 0)
            return false;
        if (World->m_frame < arg->m_targetFrame)
            return false;
    }
    return true;
}
