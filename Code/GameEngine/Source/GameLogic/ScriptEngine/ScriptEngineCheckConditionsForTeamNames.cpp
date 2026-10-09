// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?checkConditionsForTeamNames@ScriptEngine@@QAEXPAVScript@@ABVAsciiString@@@Z, retail 0x002062A8 547B
// Evidence: warning string ***WARNING multiple non-singleton team conditions, TeamFactory findPrototype pin 0x39FE6C,
// resolveName row 0x2046C0, AppendDebugMessage row 0x205263, GameLogic gate 0x1DCD1C, GetGameLogicRandomValue row 0x233FF4,
// ScriptAction getParameter row 0x203553, caller 0x207C02. Donor: BFME1 ScriptEngineCheckConditionsForTeamNames.cpp.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
extern Int g_Va00DBA4E4;

class GameLogic
{
public:
	bool rva001DCD1C();
};
extern GameLogic *TheGameLogic;

class Parameter
{
public:
	enum ParameterType { TEAM = 3 };
	Int getParameterType() const { return m_type; }
	const AsciiString &getString() const { return m_string; }
private:
	Int m_type;
	Int m_initialized;
	Int m_integer;
	float m_real;
	AsciiString m_string;
};

class Condition;

class ScriptAction
{
public:
	Parameter *getParameter(Int ndx);
private:
	void *m_vtable;
	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[12];
};

class Condition
{
public:
	Int getNumParameters() const { return m_numParms; }
	Condition *getNext() const { return m_next; }
private:
	void *m_vtable;
	Int m_condType;
	Int m_numParms;
	Parameter *m_parms[12];
	Condition *m_next;
};

class OrCondition
{
public:
	OrCondition *getNextOrCondition() const { return m_nextOr; }
	Condition *getFirstAndCondition() const { return m_firstAnd; }
private:
	void *m_vtable;
	OrCondition *m_nextOr;
	Condition *m_firstAnd;
};

class Script
{
	friend class ScriptEngine; // Retail reads this view's +0x30 field inline.
public:
	Int getDelayEvalSeconds() const { return m_delay; }
	void setFrameToEvaluate(UnsignedInt f) { m_frame = f; }
private:
	char m_pad0[0x20];
	Int m_delay;
	char m_pad1[0x30 - 0x24];
	OrCondition *m_or;
	char m_pad2[0x3C - 0x34];
	UnsignedInt m_frame;
};

class TeamPrototype
{
private:
	char m_beforeFlags[0x18];
public:
	UnsignedInt m_flags;
private:
	char m_beforeMax[0x218 - 0x1C];
public:
	Int m_maxInstances;
};

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

class Rva0039FE6COwner
{
public:
	TeamPrototype *findPrototype(const AsciiString &normalized, const AsciiString &name);
};

class Rva002041E1
{
public:
	void rva002041FC(AsciiString s);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

struct AsciiStringDataLayout
{
	Int refs;
	unsigned short len;
	unsigned short cap;
	char data[1];
};

static __forceinline Bool isStringEmpty(const AsciiString &v)
{
	const AsciiStringDataLayout *d = *(const AsciiStringDataLayout **)&v;
	return d == 0 || d->len == 0;
}

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &msg, Bool force);
	void checkConditionsForTeamNames(Script *pScript, const AsciiString &scriptName);
};

void ScriptEngine::checkConditionsForTeamNames(Script *pScript, const AsciiString &scriptName)
{
	AsciiString singletonTeamName;
	AsciiString multiTeamName;

	Int delay = pScript->getDelayEvalSeconds();
	if (delay > 0) {
		if (!TheGameLogic->rva001DCD1C()) {
			pScript->setFrameToEvaluate(GetGameLogicRandomValue(0, g_Va00DBA4E4 * 2, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0xA7C));
		} else {
			pScript->setFrameToEvaluate(GetGameLogicRandomValue(0, delay, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\ScriptEngine\\ScriptEngine.cpp", 0xA81));
		}
	} else {
		pScript->setFrameToEvaluate(0);
	}

	for (OrCondition *pOr = pScript->m_or; pOr; pOr = pOr->getNextOrCondition()) {
		for (Condition *pCond = pOr->getFirstAndCondition(); pCond; pCond = pCond->getNext()) {
			for (Int i = 0; i < pCond->getNumParameters(); ++i) {
				if (((ScriptAction *)pCond)->getParameter(i)->getParameterType() != Parameter::TEAM)
					continue;
				AsciiString teamName = ((ScriptAction *)pCond)->getParameter(i)->getString();
				AsciiString canonical = ((Rva002046C0Owner *)this)->resolveName(teamName);
				TeamPrototype *proto = ((Rva0039FE6COwner *)TheTeamFactory)->findPrototype(canonical, teamName);
				if (proto == 0)
					continue;
				Bool singleton = (proto->m_flags & 1) != 0;
				if (proto->m_maxInstances < 2)
					singleton = true;
				if (singleton) {
					singletonTeamName = teamName;
				} else {
					if (isStringEmpty(multiTeamName)) {
						multiTeamName = teamName;
					} else if (multiTeamName.compare(teamName) != 0) {
						{
							AsciiString message("***WARNING: Script contains multiple non-singleton team conditions::***");
							AppendDebugMessage(message, false);
						}
						AppendDebugMessage(scriptName, false);
						AppendDebugMessage(multiTeamName, false);
						AppendDebugMessage(teamName, false);
					}
				}
			}
		}
	}

	if (isStringEmpty(multiTeamName)) {
		if (!isStringEmpty(singletonTeamName))
			((Rva002041E1 *)pScript)->rva002041FC(singletonTeamName);
	} else {
		((Rva002041E1 *)pScript)->rva002041FC(multiTeamName);
	}
}
