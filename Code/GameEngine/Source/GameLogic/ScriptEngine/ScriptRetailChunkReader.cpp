// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// platformsdk
// BF1f989 ScriptsParseActionDataChunkThunk and ZH Scripts.cpp source guide.

#include <windows.h>

#include "../../../Include/GameLogic/ScriptAction.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
public:
	ScriptAction *getAction(void) const { return m_action; }
    ScriptAction *getActionFalse(void) const { return m_actionFalse; }
	__declspec(dllimport) __forceinline void setAction(ScriptAction *pAct) { m_action = pAct; }
    void setActionFalse(ScriptAction *pAct) { m_actionFalse = pAct; }

private:
	unsigned char _bfme_head[0x34];
	ScriptAction *m_action;
    ScriptAction *m_actionFalse;
};

bool ScriptAction::ParseActionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Script *pScript = (Script *)userData;

	ScriptAction	*pScriptAction = ParseAction(file, info, userData);

	ScriptAction *pLast = pScript->getAction();
	while (pLast && pLast->getNext())
	{
		pLast = pLast->getNext();
	}

	if (pLast)
	{
		pLast->setNextAction(pScriptAction);
	}
	else
	{
		pScript->setAction(pScriptAction);
	}
	return true;
}

bool ScriptAction::ParseActionFalseDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Script *pScript = (Script *)userData;

	ScriptAction	*pScriptAction = ParseAction(file, info, userData);

	ScriptAction *pLast = pScript->getActionFalse();
	while (pLast && pLast->getNext())
	{
		pLast = pLast->getNext();
	}

	if (pLast)
	{
		pLast->setNextAction(pScriptAction);
	}
	else
	{
		pScript->setActionFalse(pScriptAction);
	}
	return true;
}
