// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ScriptEngine::executeActions, retail 0x0020C5C7 (632B).
//
// Identity (target): WorldBuilder twin 0xB3D9F0 carries the name
// ScriptEngine::executeActions and the ScriptEngine.cpp path; its callees are
// named there (setCounter, setCounterToThreat, setSway, add/subCounter,
// setFlag, pause/restartTimer, setTimer, adjustTimer, enable/disableScript,
// callSubroutine, setFade, setPriorityThing/Kind/Default). Retail case values
// match Zero Hour's ScriptAction enum (SET_FLAG 1, SET_COUNTER 2, NO_OP 5,
// SET_TIMER 6, ENABLE_SCRIPT 8 ... SET_MILLISECOND_TIMER 0x14).
// Donor: Zero Hour ScriptEngine.cpp executeActions (switch order, the unused
// UnicodeString local, the TheScriptActions default). BFME2 additions read
// from target only: a mode-mask test (action 0x003B2832 against engine
// 0x00203693; WB's failing branch is a debug-only report) and the call
// 0x003B3D75 forwarding the two extra arguments, whose types are unknown, so
// they stay void* and the helpers keep address-derived names.
#include "unicode_string.h"

class ScriptAction
{
public:
	int getActionType() { return m_actionType; }
	ScriptAction *getNext() { return m_nextAction; }
	int rva003B2832();				// 0x003B2832, action template's mode mask
	void rva003B3D75(void *a, void *b);	// 0x003B3D75

private:
	char m_unknown0[4];
	int m_actionType;				// +0x04
	char m_unknown8[0x3c - 8];
	ScriptAction *m_nextAction;		// +0x3C
};

class ScriptActions
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void executeAction(ScriptAction *pAction);	// vtable +0x38
};

extern ScriptActions *TheScriptActions;

class ScriptEngine
{
public:
	void callSubroutine(ScriptAction *pAction);
	void setPriorityDefault(ScriptAction *pAction);
	int rva00203693();				// 0x00203693, current mode mask (2 or 1)

protected:
	void setSway(ScriptAction *pAction);
	void setCounter(ScriptAction *pAction, int mode, bool a, bool b);
	void setCounterToThreat(ScriptAction *pAction, bool b);
	void addCounter(ScriptAction *pAction);
	void subCounter(ScriptAction *pAction);
	void setFade(ScriptAction *pAction);
	void setFlag(ScriptAction *pAction, bool value);
	void pauseTimer(ScriptAction *pAction);
	void restartTimer(ScriptAction *pAction);
	void setTimer(ScriptAction *pAction, bool milisecondTimer, bool random);
	void adjustTimer(ScriptAction *pAction, bool milisecondTimer, bool add);
	void enableScript(ScriptAction *pAction);
	void disableScript(ScriptAction *pAction);
	void executeActions(ScriptAction *pActionHead, void *a, void *b);
	void setPriorityThing(ScriptAction *pAction);
	void setPriorityKind(ScriptAction *pAction);
};

void ScriptEngine::executeActions(ScriptAction *pActionHead, void *a, void *b)
{
	ScriptAction *pCurAction;
	UnicodeString uStr1;
	for (pCurAction = pActionHead; pCurAction; pCurAction = pCurAction->getNext()) {
		if ((pCurAction->rva003B2832() & rva00203693()) == 0)
			continue;
		pCurAction->rva003B3D75(a, b);
		switch (pCurAction->getActionType()) {
			default: if (TheScriptActions) TheScriptActions->executeAction(pCurAction); break;
			case 2: setCounter(pCurAction, 0, false, false); break;
			case 0x175: setCounter(pCurAction, 1, false, false); break;
			case 0x1FC: setCounter(pCurAction, 2, false, false); break;
			case 0x19F: setCounter(pCurAction, 0, false, true); break;
			case 0x1A0: setCounter(pCurAction, 1, false, true); break;
			case 0x176: setCounter(pCurAction, 0, true, false); break;
			case 0x1B7: setCounterToThreat(pCurAction, false); break;
			case 0x1B8: setCounterToThreat(pCurAction, true); break;
			case 0x67: setSway(pCurAction); break;
			case 15: addCounter(pCurAction); break;
			case 16: subCounter(pCurAction); break;
			case 1: setFlag(pCurAction, false); break;
			case 0x177: setFlag(pCurAction, true); break;
			case 0x98: pauseTimer(pCurAction); break;
			case 0x99: restartTimer(pCurAction); break;
			case 6: setTimer(pCurAction, false, false); break;
			case 0x14: setTimer(pCurAction, true, false); break;
			case 0x96: setTimer(pCurAction, false, true); break;
			case 0x97: setTimer(pCurAction, true, true); break;
			case 0x9A: adjustTimer(pCurAction, true, true); break;
			case 0x9B: adjustTimer(pCurAction, true, false); break;
			case 8: enableScript(pCurAction); break;
			case 9: disableScript(pCurAction); break;
			case 10: callSubroutine(pCurAction); break;

			case 0x7C:
			case 0x7D:
			case 0x7E:
			case 0x7F:
				setFade(pCurAction); break;

			case 0x84: setPriorityThing(pCurAction); break;
			case 0x85: setPriorityKind(pCurAction); break;
			case 0x86: setPriorityDefault(pCurAction); break;

			case 5: break;
		}
	}
}
