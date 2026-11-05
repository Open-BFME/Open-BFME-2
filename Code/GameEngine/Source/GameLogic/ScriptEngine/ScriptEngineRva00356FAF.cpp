// cl: /DNDEBUG /MD
// ?rva00356FAF@ScriptEngine@@QAEXH@Z @0x00356FAF 45B via unlock callee evidence
// Evidence: calls rowed ScriptEngine::rva00203FA8 0x00203FA8; prev ScriptEngine TU; clears +0x1A114/+0x1A11C.
#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::rva00356FAF(int arg)
{
	rva00203FA8(arg);
	if (m_conditionObject == (Object *)arg)
		m_conditionObject = 0;
	if (m_callingObject == (Object *)arg)
		m_callingObject = 0;
}
