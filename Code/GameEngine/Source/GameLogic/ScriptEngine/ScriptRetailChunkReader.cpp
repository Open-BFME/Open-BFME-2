// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BF1f989 ScriptsParseActionDataChunkThunk and ZH Scripts.cpp source guide.
#define NULL 0

class DataChunkInput;
struct DataChunkInfo;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
struct Rva003B65Header;
int rva003B5EA5(int, int, Rva003B65Header *);

class ScriptAction
{
public:
	static bool ParseActionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
    static bool ParseActionFalseDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

	ScriptAction *getNext(void) const { return m_nextAction; }
	void setNextAction(ScriptAction *pAct) { m_nextAction = pAct; }

protected:
	// Defined elsewhere; retail reaches it through the link thunk at 0x0001720B.
	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData) { return (ScriptAction *)rva003B5EA5((int)&file, (int)info, (Rva003B65Header *)userData); }

private:
	unsigned char _bfme_head[0x3C];
	ScriptAction *m_nextAction;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
public:
	ScriptAction *getAction(void) const { return m_action; }
    ScriptAction *getActionFalse(void) const { return m_actionFalse; }
	void setAction(ScriptAction *pAct) { m_action = pAct; }
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
