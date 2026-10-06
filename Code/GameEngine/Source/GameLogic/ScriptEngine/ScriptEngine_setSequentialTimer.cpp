// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?setSequentialTimer@ScriptEngine@@QAEXPAVObject@@H@Z at retail 0x00203FCF (51B).
// Donor: ZH GeneralsMD ScriptEngine.cpp:7840 setSequentialTimer(Object*,Int).
// Target evidence: caller ScriptActions::doNamedAttackAreaForSeconds at
// 0x003C8413; Object m_id at +0x74 (Object_setID.cpp target fact);
// m_sequentialScripts at +0x10; SequentialScript m_objectID at +8 and
// m_framesToWait at +0x20 with m_nextScriptInSequence at +0x28.
#include <vector>

typedef int ObjectID;

class Team;

class Object
{
public:
	int getID() const { return m_id; }

private:
	unsigned char m_pre[0x74]; // +0x00..0x74
	int m_id; // +0x74
};

class SequentialScript
{
public:
	virtual ~SequentialScript();

	Team *m_teamToExecOn; // +0x04
	int m_objectID; // +0x08
	char m_pad0C[0x20 - 0x0C]; // +0x0C..0x1F
	int m_framesToWait; // +0x20
	char m_pad24[0x28 - 0x24]; // +0x24..0x27
	SequentialScript *m_nextScriptInSequence; // +0x28
};

class ScriptEngine
{
protected:
	typedef std::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef VecSequentialScriptPtr::iterator VecSequentialScriptPtrIt;

	char m_pre[0x10];
	VecSequentialScriptPtr m_sequentialScripts; // +0x10

public:
	void setSequentialTimer(Object *obj, int frameCount);
	void setSequentialTimer(Team *team, int frameCount);
};

// ScriptEngine.cpp's singleton (Zero Hour: `ScriptEngine *TheScriptEngine = NULL;`).
// Matched references in 31 units place it at VA 0x00DFE16C, zero-filled .bss.
ScriptEngine *TheScriptEngine = NULL;

void ScriptEngine::setSequentialTimer(Object *obj, int frameCount)
{
	if (!obj)
		return;

	int id = obj->getID();
	for (VecSequentialScriptPtrIt it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); ++it) {
		SequentialScript *seqScript = (*it);
		if (!seqScript)
			continue;

		if (seqScript->m_objectID == id) {
			seqScript->m_framesToWait = frameCount;
			return;
		}
	}
}

void ScriptEngine::setSequentialTimer(Team *team, int frameCount)
{
	if (!team)
		return;

	for (VecSequentialScriptPtrIt it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); ++it) {
		SequentialScript *seqScript = (*it);
		if (!seqScript)
			continue;

		if (seqScript->m_teamToExecOn == team) {
			seqScript->m_framesToWait = frameCount;
			return;
		}
	}
}
