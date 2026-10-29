// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
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
// The rowed mode gate 0x001DCD1C (GameLogicModeGateChecks.cpp) is visible here
// as an inline COMDAT copy: knowing it leaves TheGameLogic alone, cl keeps the
// pointer in EDI across the call and the delay in EBX, as retail does, from the
// natural TheGameLogic reads.

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
extern int BfmeLogicFramesPerSecond;

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

#include "../../../Include/GameLogic/ScriptEngine.h"

inline bool GameLogic::rva001DCD1C(void)
{
	return m_110 == 8 || (m_110 == 9 && m_114 != 3);
}

void ScriptEngine::rva0020A586(void *script, void *name)
{
	if (!rva00203F0E(script))
		return;
	((AsciiStringVector *)&g_00DFE174)->push_back(*(const AsciiString *)name);
	ScriptScheduleView *view = (ScriptScheduleView *)script;
	int delay = view->m_delay;
	if (delay > 0) {
		if (!TheGameLogic->rva001DCD1C())
			view->m_frameToEvaluate = TheGameLogic->getFrame() + delay * BfmeLogicFramesPerSecond;
		else
			view->m_frameToEvaluate = TheLivingWorldLogic->m_frame + delay;
	}
	if (view->m_sequential)
		executeSequentialScript((Script *)script, *(const AsciiString *)name);
	else
		executeScript((Script *)script, *(const AsciiString *)name);
}
