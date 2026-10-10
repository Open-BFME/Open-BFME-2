// ?rva0020A586@ScriptEngine@@QAEXPAX0@Z
// partial score=0.9 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0020A586@ScriptEngine@@QAEXPAX0@Z at 0x0020A586 121 bytes RET 8.
// Called by the rowed walkNamed (0x0020A775) with a script record and its
// scope-qualified name. Retail runs the rowed gate 0x00203F0E (inactive
// script / difficulty / future frame) and returns when it fails; otherwise
// it appends the name to the slow-script name vector at 0x00DFE174 (rowed
// vector<AsciiString>::push_back 0x0002DBE6). As in Zero Hour's
// ScriptEngine::executeScript it then schedules the next evaluation when the
// script's delay (+0x20) is positive: TheGameLogic's frame plus delay times
// the logic frame rate global 0x00DBA4E4 or, when the rowed GameLogic mode
// gate 0x001DCD1C holds, the living-world frame at +0xFC plus the delay;
// the result goes to +0x3C. The byte at +0x10 then selects the rowed
// executeSequentialScript (0x0020A073) over executeScript (0x00209E15).
// Field names for +0x10/+0x20/+0x3C are target-observed offsets only.
//
// NEAR (score ~0.9): only the delay/GameLogic registers are mirrored (ours
// delay edi and game ebx; retail delay ebx and game edi). Frame layout and
// the this spill to ebp-4 match. Survived: game local vs none; ternary;
// frame local; declaration order (top / game first / view first / game
// hoisted before the test or the push_back); const and register; nested gate;
// name reference local; self alias; free __forceinline helper (with and
// without the game argument); __forceinline GameLogic member view; operand
// orders; /G5 /G6 /G7 /arch:SSE /EHs /Os. class_gate silent.

#include "../../Common/GameLogicObjectLookupView.h"

class Script;
class AsciiString;

namespace _STL
{
template <class _Tp> class allocator;
template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &value);
};
}

typedef _STL::vector<AsciiString, _STL::allocator<AsciiString> > AsciiStringVector;

extern unsigned int g_00DFE174;
extern int g_Va00DBA4E4;

class LivingWorldLogic
{
public:
	unsigned char m_unknown00[0xfc];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct ScriptScheduleView
{
	unsigned char m_unknown00[0x10];
	bool m_sequential;
	unsigned char m_unknown11[0x20 - 0x11];
	int m_delay;
	unsigned char m_unknown24[0x3c - 0x24];
	unsigned int m_frameToEvaluate;
};

class ScriptEngine
{
public:
	bool rva00203F0E(void *script);
	void rva0020A586(void *script, void *name);
	void executeSequentialScript(Script *script, const AsciiString &name);
	void executeScript(Script *script, const AsciiString &name);
};

void ScriptEngine::rva0020A586(void *script, void *name)
{
	if (!rva00203F0E(script))
		return;
	((AsciiStringVector *)&g_00DFE174)->push_back(*(const AsciiString *)name);
	ScriptScheduleView *view = (ScriptScheduleView *)script;
	int delay = view->m_delay;
	if (delay > 0) {
		GameLogic *game = TheGameLogic;
		if (!game->rva001DCD1C())
			view->m_frameToEvaluate = game->getFrame() + delay * g_Va00DBA4E4;
		else
			view->m_frameToEvaluate = TheLivingWorldLogic->m_frame + delay;
	}
	if (view->m_sequential)
		executeSequentialScript((Script *)script, *(const AsciiString *)name);
	else
		executeScript((Script *)script, *(const AsciiString *)name);
}
