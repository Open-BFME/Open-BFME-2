// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ScriptEngine::evaluateAndProgressAllSequentialScripts, retail 0x0020C83F
// (1379B).
//
// Identity (target): WorldBuilder twin 0xB40860 carries the name
// ScriptEngine::evaluateAndProgressAllSequentialScripts and ScriptEngine.cpp
// (assert line 3699). Callees from the WB call list, each read at the retail
// REL32: cleanupSequentialScript 0x00204733 (five sites), findObjectByID,
// Object/Team getControllingPlayer, AI::createGroup, getTeamAsAIGroup,
// AIGroup::isIdle 0x0036DF4D, the AIGroup helpers 0x0036E0B6, 0x0036E2E2 and
// 0x0036E0E3, the scope guard Rva002048A2 (ctor 0x002048A2, dtor 0x002048EC),
// the mode masks 0x003B2832 / 0x00203693, executeActions 0x0020C5C7,
// ScriptAction::getUiText, AppendDebugMessage and appendSequentialScript.
// Donor: Zero Hour ScriptEngine.cpp evaluateAndProgressAllSequentialScripts
// (spin count, the skirmish/contained waits, the debug message, the idle and
// dead checks). BFME2 differences read from WB and retail only:
//   * the int at +0x1C is decremented around every call that may change
//     m_sequentialScripts, and end() is re-read after it;
//   * no isSkirmishAIPlayer filter on m_currentPlayer (+0x1A130);
//   * the frames-to-wait gate sets or clears an AI flag (+0x3DA) and the
//     group helper 0x0036E2E2, and treats AI byte +0x3CA / 0x0036E0B6 as busy;
//   * a mode-mask test before the action (WB's failing branch is debug-only),
//     a fifth wait action 0x1F1 on ScriptConditions slot 17, executeActions
//     with the script and its name, and the scope guard on +0x1A10C;
//   * a dead group is not cleaned up when its team is the current player's
//     default team (Player +0x2EC, PlayerSetDefaultTeam.cpp).
// Field and helper names without a donor stay address-derived.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef int Int;
typedef bool Bool;

class Team;
class Player;
class Object;
class Parameter;
class ScriptAction;
class SequentialScript;

// Declared ahead of the other classes: declared last, cl 13.10 evaluates the
// mode-mask test's engine operand before the action's, retail's reverse.
class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);
	int rva00203693();	// 0x00203693, current mode mask
	void appendSequentialScript(const SequentialScript *scriptToSequence);
	void evaluateAndProgressAllSequentialScripts();

protected:
	typedef SequentialScript **VecSequentialScriptPtrIt;

	// STLport vector<SequentialScript *> view.
	class VecSequentialScriptPtr
	{
	public:
		VecSequentialScriptPtrIt begin() { return m_start; }
		VecSequentialScriptPtrIt end() { return m_finish; }

	private:
		VecSequentialScriptPtrIt m_start;
		VecSequentialScriptPtrIt m_finish;
		VecSequentialScriptPtrIt m_endOfStorage;
	};

	VecSequentialScriptPtrIt cleanupSequentialScript(VecSequentialScriptPtrIt it, Bool cleanDanglers, Bool removeEntry);
	void executeActions(ScriptAction *pActionHead, void *a, void *b);

	char m_pad0[0x10];
	VecSequentialScriptPtr m_sequentialScripts;	// +0x10
	Int m_bfme1C;	// +0x1C
	char m_pad20[0x1A10C - 0x20];
	AsciiString m_1A10C;	// +0x1A10C
	char m_pad1A110[0x1A118 - 0x1A110];
	Team *m_conditionTeam;	// +0x1A118
	Object *m_conditionObject;	// +0x1A11C
	char m_pad1A120[0x1A130 - 0x1A120];
	Player *m_currentPlayer;	// +0x1A130
};


class Player
{
public:
	char m_pad[0x2EC];
	Team *m_defaultTeam;	// +0x2EC
};

class Parameter;

class ScriptAction
{
public:
	Int getActionType() const { return m_actionType; }
	Parameter *getParameter(Int ndx) const
	{
		if (ndx >= 0 && ndx < m_numParms)
			return m_parms[ndx];
		return 0;
	}
	ScriptAction *getNext() const { return m_nextAction; }
	void setNextAction(ScriptAction *pAct) { m_nextAction = pAct; }
	AsciiString getUiText();
	int rva003B2832();	// 0x003B2832, action template's mode mask

private:
	char m_unknown0[4];
	Int m_actionType;		// +0x04
	Int m_numParms;			// +0x08
	Parameter *m_parms[12];	// +0x0C
	ScriptAction *m_nextAction;	// +0x3C
};

class Script
{
public:
	ScriptAction *getAction() const { return m_action; }

private:
	char m_unknown0[0x34];
	ScriptAction *m_action;	// +0x34
};

class SequentialScript
{
public:
	virtual ~SequentialScript();

	Team *m_teamToExecOn;	// +0x04
	ObjectID m_objectID;	// +0x08
	AsciiString m_bfmeScriptScope;	// +0x0C
	AsciiString m_bfmeScriptName;	// +0x10
	Script *m_scriptToExecuteSequentially;	// +0x14
	Int m_currentInstruction;	// +0x18
	Int m_timesToLoop;	// +0x1C
	Int m_framesToWait;	// +0x20
	Bool m_dontAdvanceInstruction;	// +0x24
	SequentialScript *m_nextScriptInSequence;	// +0x28
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<110>
{
public:
	virtual Bool isIdle() const;	// +0x1B8
	char m_pad04[0x3CA - 4];
	Bool m_3CA;	// +0x3CA
	char m_pad3CB[0x3DA - 0x3CB];
	Bool m_3DA;	// +0x3DA, script tracker (+0x3D0) flag
};

class Object
{
public:
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAIUpdateInterface() { return m_ai; }
	const AsciiString &getName() const { return m_name; }
	Bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	char m_pad0[0x88];
	AsciiString m_name;		// +0x88
	char m_pad8C[0x258 - 0x8C];
	AIUpdateInterface *m_ai;	// +0x258
	char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;	// +0x438
};

extern GameLogic *TheGameLogic;

class AIGroup
{
public:
	Bool isIdle() const;
	Bool rva0036E0B6() const;	// 0x0036E0B6, a member's AI byte +0x3CA set
	void rva0036E2E2(Bool b);	// 0x0036E2E2, sets each member's AI +0x3DA
	Bool rva0036E0E3();			// 0x0036E0E3, every member effectively dead
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad[0x14];
	AsciiString m_name;	// +0x14
};

class Team
{
public:
	const AsciiString &getName() const
	{
		return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getName();
	}
	Player *getControllingPlayer() const;
	void getTeamAsAIGroup(AIGroup *group);

private:
	char m_pad[0x30];
	TeamPrototype *m_proto;	// +0x30
};

class ScriptConditionsInterface
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
	virtual void slot14();
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *pSkirmishPlayerParm, Parameter *pTeamParm, Parameter *pCommandButtonParm, Bool allReady);	// +0x3C
	virtual Bool evaluateTeamIsContained(Parameter *pTeamParm, Bool allContained);	// +0x40
	virtual Bool slot17(Parameter *pParm);	// +0x44
};
extern ScriptConditionsInterface *TheScriptConditions;

// Restores the engine's scope string (+0x1A10C) when it goes out of scope.
struct Rva002048A2
{
	virtual ~Rva002048A2();
	AsciiString m_str;
	AsciiString *m_alias;
	Rva002048A2(AsciiString *a1, const AsciiString &a2);
};

#define MAX_SPIN_COUNT 20

#define CLEANUP_SEQUENTIAL_SCRIPT(cleanDanglers) \
	{ \
		--m_bfme1C; \
		it = cleanupSequentialScript(it, cleanDanglers, true); \
		lastIt = m_sequentialScripts.end(); \
		++m_bfme1C; \
	}

void ScriptEngine::evaluateAndProgressAllSequentialScripts()
{
	VecSequentialScriptPtrIt it, lastIt;
	lastIt = m_sequentialScripts.end();
	++m_bfme1C;

	Int spinCount = 0;
	for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); /* empty */) {
		if (it == lastIt) {
			++spinCount;
		} else {
			spinCount = 0;
		}

		if (spinCount > MAX_SPIN_COUNT) {
			++it;
			continue;
		}

		lastIt = it;

		Bool itAdvanced = false;

		SequentialScript *seqScript = (*it);
		if (seqScript == 0) {
			CLEANUP_SEQUENTIAL_SCRIPT(false);
			continue;
		}

		Team *team = seqScript->m_teamToExecOn;
		Object *obj = TheGameLogic->findObjectByID(seqScript->m_objectID);
		if (!(obj || team)) {
			CLEANUP_SEQUENTIAL_SCRIPT(false);
			itAdvanced = true;
			continue;
		}
		m_currentPlayer = 0;
		if (obj) {
			m_currentPlayer = obj->getControllingPlayer();
		} else if (team) {
			m_currentPlayer = team->getControllingPlayer();
		}

		AIUpdateInterface *ai = obj ? obj->getAIUpdateInterface() : 0;
		AIGroup *aigroup = (team ? TheAI->createGroup() : 0);
		if (aigroup) {
			team->getTeamAsAIGroup(aigroup);
		}

		if (ai || aigroup) {
			Bool advance = true;
			if (seqScript->m_framesToWait > 0) {
				advance = false;
				if (ai)
					ai->m_3DA = true;
				if (aigroup)
					aigroup->rva0036E2E2(true);
			} else if (seqScript->m_framesToWait <= 0) {
				if (ai) {
					if (!ai->isIdle() || ai->m_3CA)
						advance = false;
					ai->m_3DA = false;
				}
				if (aigroup) {
					if (!aigroup->isIdle() || aigroup->rva0036E0B6())
						advance = false;
					aigroup->rva0036E2E2(false);
				}
			}

			if (advance) {
				Bool displayMessage = true;

				if (seqScript->m_dontAdvanceInstruction) {
					seqScript->m_dontAdvanceInstruction = false;
					displayMessage = false;
				} else {
					++seqScript->m_currentInstruction;
				}

				AsciiString msg = "Advancing SeqScript '";
				msg.concat(seqScript->m_bfmeScriptName);
				msg.concat("' on ");
				AsciiString name;
				if (team) name = team->getName();
				if (obj) name = obj->getName();
				msg.concat(name);
				msg.concat(" -- ");

				int instruction = seqScript->m_currentInstruction;
				ScriptAction *action = seqScript->m_scriptToExecuteSequentially->getAction();
				while (action && instruction) {
					--instruction;
					action = action->getNext();
				}

				if (action) {
					Rva002048A2 scope(&m_1A10C, seqScript->m_bfmeScriptScope);
					m_conditionTeam = team;
					m_conditionObject = obj;
					seqScript->m_framesToWait = -1;

					ScriptAction *nextAction = action->getNext();
					action->setNextAction(0);
					if ((action->rva003B2832() & rva00203693()) == 0) {
						// WB reports the action as unusable in this mode (debug only).
					} else if (action->getActionType() == 0x107) {
						if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(0, action->getParameter(1), action->getParameter(2), true)) {
							seqScript->m_dontAdvanceInstruction = true;
						}
					} else if (action->getActionType() == 0x108) {
						if (!TheScriptConditions->evaluateSkirmishCommandButtonIsReady(0, action->getParameter(1), action->getParameter(2), false)) {
							seqScript->m_dontAdvanceInstruction = true;
						}
					} else if (action->getActionType() == 0x11B) {
						if (TheScriptConditions->evaluateTeamIsContained(action->getParameter(0), true)) {
							seqScript->m_dontAdvanceInstruction = true;
						}
					} else if (action->getActionType() == 0x11C) {
						if (TheScriptConditions->evaluateTeamIsContained(action->getParameter(0), false)) {
							seqScript->m_dontAdvanceInstruction = true;
						}
					} else if (action->getActionType() == 0x1F1) {
						if (!TheScriptConditions->slot17(action->getParameter(0))) {
							seqScript->m_dontAdvanceInstruction = true;
						}
					} else {
						executeActions(action, seqScript->m_scriptToExecuteSequentially, &seqScript->m_bfmeScriptName);
					}

					if (displayMessage) {
						msg.concat(action->getUiText());
						AppendDebugMessage(msg, false);
					} else {
						msg.clear();
					}

					action->setNextAction(nextAction);

					if (seqScript->m_dontAdvanceInstruction) {
						++it;
						itAdvanced = true;
						continue;
					}

					if (ai && ai->isIdle()) {
						itAdvanced = true;
					} else if (team) {
						aigroup = (team ? TheAI->createGroup() : 0);
						team->getTeamAsAIGroup(aigroup);
					}

					if (aigroup && aigroup->isIdle()) {
						itAdvanced = true;
					}

					if (itAdvanced) {
						if (obj && obj->isEffectivelyDead()) {
							CLEANUP_SEQUENTIAL_SCRIPT(true);
							continue;
						}

						if (aigroup && aigroup->rva0036E0E3()) {
							Bool keep = false;
							if (team && m_currentPlayer && team == m_currentPlayer->m_defaultTeam)
								keep = true;
							if (!keep)
								CLEANUP_SEQUENTIAL_SCRIPT(true);
							continue;
						}
					}
				} else {
					if (seqScript->m_timesToLoop != 0) {
						if (seqScript->m_timesToLoop != -1) {
							--seqScript->m_timesToLoop;
						}

						seqScript->m_framesToWait = -1;
						Int ndx = it - m_sequentialScripts.begin();
						--m_bfme1C;
						appendSequentialScript(seqScript);
						lastIt = m_sequentialScripts.end();
						++m_bfme1C;
						it = m_sequentialScripts.begin() + ndx;
					}

					CLEANUP_SEQUENTIAL_SCRIPT(false);
					itAdvanced = true;
				}
			} else if (seqScript->m_framesToWait > 0) {
				--seqScript->m_framesToWait;
			}
		}

		if (!itAdvanced) {
			++it;
		}
	}
	m_currentPlayer = 0;
	--m_bfme1C;
}
