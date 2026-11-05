// cl: /DNDEBUG /MD
//
// ?getActionTemplate@ScriptEngine@@QAEPBVActionTemplate@@H@Z,
// retail 0x00203926, 27 bytes. Dedicated TU.
//
// Table lookup for the action writer (0x3B3DFF calls it with TheScriptEngine
// at 0xDFE16C and the action type): 0x257 entries of 128 bytes at this+0x20.
// Out-of-range indexes clamp to entry 0 (retail xors to zero then shares the
// shift-and-lea tail, so the caller-side null test is dead). Pure arithmetic
// with no callees. Name and Int parameter follow the Zero Hour ScriptEngine.h
// declaration; the table shape is retail-measured.

#include "../../../Include/GameLogic/ScriptEngine.h"

// ?getActionTemplate@ScriptEngine@@QAEPBVActionTemplate@@H@Z
const ActionTemplate *ScriptEngine::getActionTemplate(int actionType)
{
	int index = actionType;
	if (index < 0 || index >= 0x257)
		index = 0;
	// The canonical header keeps both template tables opaque at +0x1C.
	return reinterpret_cast<const ActionTemplate *>(m_opaque1C + 4 + index * 128);
}
