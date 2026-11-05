// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ScriptEngine::removeObjectTypes (retail 0x002046E4, 79 bytes) and
// ScriptEngine::cleanupSequentialScript (retail 0x00204733, 107 bytes), the
// two helpers ScriptEngine::reset calls on m_allObjectTypeLists (+0x1A4C8) and
// m_sequentialScripts (+0x10).
//
// Donors: ZH ScriptEngine.cpp and BFME1's matched removeObjectTypes, both
// protected members as in ZH. BFME2 differences read from retail:
//   * objects are released with ::delete (virtual destructor with flag 0, then
//     global operator delete) instead of deleteInstance();
//   * cleanupSequentialScript takes a third Bool that gates the erase, and
//     the early return for an empty slot also honours it.
// /Oy- is target evidence: both keep an ebp frame without EH, unlike the
// frame-omitting template tables.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <algorithm>
#include <vector>

#include "../../../Include/GameLogic/ObjectTypesClass.h"

class SequentialScript
{
public:
	virtual ~SequentialScript();


	char m_body[0x24];
	SequentialScript *m_nextScriptInSequence; // +0x28
};

#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptEngine::removeObjectTypes(ObjectTypes *typesToRemove)
{
	if (!typesToRemove)
		return;

	std::vector<ObjectTypes *>::iterator it = std::find(
		m_allObjectTypeLists.begin(), m_allObjectTypeLists.end(), typesToRemove);

	if (it == m_allObjectTypeLists.end())
		return;

	::delete typesToRemove;
	m_allObjectTypeLists.erase(it);
}

ScriptEngine::VecSequentialScriptPtrIt ScriptEngine::cleanupSequentialScript(VecSequentialScriptPtrIt it, bool cleanDanglers, bool removeEntry)
{
	SequentialScript *seqScript = (*it);
	if (!seqScript) {
		if (removeEntry) {
			return m_sequentialScripts.erase(it);
		}
		return it;
	}

	SequentialScript *scriptToDelete = seqScript;
	if (cleanDanglers) {
		while (seqScript) {
			scriptToDelete = seqScript;
			seqScript = seqScript->m_nextScriptInSequence;
			::delete scriptToDelete;
			scriptToDelete = 0;
		}
		(*it) = 0;
	} else {
		(*it) = scriptToDelete->m_nextScriptInSequence;
		::delete scriptToDelete;
		scriptToDelete = 0;
	}

	if ((*it) == 0 && removeEntry) {
		return m_sequentialScripts.erase(it);
	}

	return it;
}
