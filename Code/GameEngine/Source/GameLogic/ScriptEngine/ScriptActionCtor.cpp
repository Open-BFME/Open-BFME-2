// cl: /O1 /Oi /DNDEBUG /MD
// ??0ScriptAction@@QAE@XZ 0x003B2804 46B
// Evidence: vtable 0x81F3FC (ScriptAction per ScriptAction_getParameter);
// NO_OP=5 type, zero parms, null parms via rep stosd, null next, clear
// warnings, tail 1, zero tail; caller 0x003B5EA5.
#include <string.h>

typedef bool Bool;
typedef int Int;

enum { MAX_PARMS = 12 };

#include "../../../Include/GameLogic/ScriptParameter.h"

class ScriptAction
{
public:
	enum ScriptActionType { NO_OP = 5 };
	virtual ~ScriptAction();
	ScriptAction();
	ScriptAction(ScriptActionType type);
	void setActionType(ScriptActionType type);

private:
	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	unsigned char m_tail;
	char m_pad[2];
	Int m_bfmeTail;
};

ScriptAction::ScriptAction() :
	m_actionType(NO_OP),
	m_numParms(0),
	m_nextAction(0),
	m_hasWarnings(false),
	m_tail(1),
	m_bfmeTail(0)
{
	memset(m_parms, 0, sizeof(m_parms));
}

// ??0ScriptAction@@QAE@W4ScriptActionType@1@@Z present-unmatched
ScriptAction::ScriptAction(ScriptActionType type) :
	m_numParms(0),
	m_nextAction(0),
	m_hasWarnings(false),
	m_tail(1),
	m_bfmeTail(0)
{
	memset(m_parms, 0, sizeof(m_parms));
	setActionType(type);
}
