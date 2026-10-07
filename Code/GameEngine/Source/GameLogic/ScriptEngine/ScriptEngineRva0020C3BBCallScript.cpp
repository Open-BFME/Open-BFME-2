// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Os
//
// ?rva0020C3BB@ScriptEngine@@QAEXPAVScriptAction@@@Z @0x0020C3BB 524B: the
// script-call action; ?rva0020C140@ScriptEngine@@QAEXABVAsciiString@@0PAVTeam@@@Z
// @0x0020C140 635B: its scoped sibling taking explicit scope name, script name
// and calling team (below the first body). Takes the name from the action's first parameter, looks
// it up as a script group and, failing that, as a single script, and runs a
// subroutine under the "current scope" latch (ScriptEngine +0x1A10C); a
// non-subroutine or missing name is reported through AppendDebugMessage.
//
// Donor (Open-BFME-1 ScriptEngineRva00343780.cpp, submodule 968ca36c): the
// control flow and the three report calls transfer as written. BFME 1 reads
// Script::isSubroutine at +0x17; BFME 2 reads +0x2A (target byte at 0x0020C418
// region: cmp byte ptr [edi+0x2A]). Every callee is named from this image:
// the by-value lookups are the 0x00204EBB / 0x00204F3B pair (resolve the name,
// look it up in the script list, copy the resolved name out), the list lookup
// is the thiscall twin at 0x00204E64, the scope latch is the Rva002048A2 class
// (ctor 0x002048A2, dtor 0x002048EC) and the debug-line join is the rowed
// Rva0032B389Join. BFME 1's own labels for these are not carried over.
#include "ascii_string.h"

class Rva00355950Arr;
struct Rva003412E0Node;
class ScriptList;
class Player;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_pad[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(int index) const
	{
		return index >= 0 && index < m_parameterCount ? m_parameters[index] : 0;
	}

private:
	void *m_vtable;
	int m_actionType;
	int m_parameterCount;
	Parameter *m_parameters[12];
	ScriptAction *m_nextAction;
};

class ScriptGroup
{
public:
	Rva003412E0Node *getScript() const
	{
		return *(Rva003412E0Node **)((const char *)this + 8);
	}
	bool isActive() const { return *(const unsigned char *)((const char *)this + 0x0C) != 0; }
	bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x0D) != 0; }
};

class Script
{
public:
	bool isSubroutine() const { return *(const unsigned char *)((const char *)this + 0x2A) != 0; }
};

// Scope latch: saves *a1 at +4, installs a2, restores on destruction.
struct Rva002048A2
{
	virtual ~Rva002048A2();
	AsciiString m_str;
	AsciiString *m_alias;
	Rva002048A2(AsciiString *a1, const AsciiString &a2);
};

// Calling-team latch (vtable g_00BE39EC): saves *alias at +4, installs the new
// team, restores on destruction. The destructor body is the 15-byte row at
// 0x00203CC7 (Rva00203CC7Dtor.cpp); retail inlines it at the normal exit and
// calls the row from the unwind funclet, which a definition here reproduces.
extern const void *const g_00BE39EC[];
struct Rva00203CC7
{
	void *m00;
	void *m04;
	void *m08;
	Rva00203CC7(Team **alias, Team *value)
	{
		m00 = (void *)g_00BE39EC;
		m04 = *alias;
		m08 = alias;
		*alias = value;
	}
	~Rva00203CC7()
	{
		void *next = m08;
		m00 = (void *)g_00BE39EC;
		*(void **)next = m04;
	}
};

class BfmeRoomZC
{
public:
	AsciiString m_name; // +0x00
};

// Base of the script-name lookups; both entries are rowed or pinned at their
// own addresses (see BfmeOwnZC_rva00204F3B.cpp for the 0x00204F3B body).
class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

class BfmeOwnZC : public Rva002046C0Owner
{
public:
	ScriptList *rva00204E64(const AsciiString &name);
	void *bfmeRunZC(BfmeRoomZC name, void *extra);
	void *rva00204EBB(BfmeRoomZC name, void *extra);
};

AsciiString Rva0032B389Join(const AsciiString &left, const AsciiString &right);

class ScriptEngine
{
public:
	void walkNamed(Rva00355950Arr *array, Rva003412E0Node *node, bool filter);
	void rva0020A586(void *object, void *slot);
	void AppendDebugMessage(const AsciiString &message, bool forcePause);
	void rva0020C3BB(ScriptAction *action);
	void rva0020C140(const AsciiString &scopeName, const AsciiString &scriptName, Team *pThisTeam);
};

#define RVA0020C3BB_REPORT(NAME, HEADLINE) \
	do { \
		AppendDebugMessage(AsciiString(HEADLINE), false); \
		AppendDebugMessage(Rva0032B389Join(canonical, NAME), false); \
	} while (0)

// ?rva0020C3BB@ScriptEngine@@QAEXPAVScriptAction@@@Z
void ScriptEngine::rva0020C3BB(ScriptAction *action)
{
	BfmeOwnZC *lookup = (BfmeOwnZC *)this;
	AsciiString name = action->getParameter(0)->getString();
	AsciiString canonical;
	ScriptGroup *group = (ScriptGroup *)lookup->rva00204EBB(*(BfmeRoomZC *)&name, &canonical);
	if (group)
	{
		if (group->isSubroutine())
		{
			if (group->isActive())
			{
				Rva00355950Arr *array = (Rva00355950Arr *)lookup->rva00204E64(canonical);
				if (array)
				{
					Rva002048A2 restore((AsciiString *)((char *)this + 0x1A10C), canonical);
					walkNamed(array, group->getScript(), false);
				}
			}
		}
		else
		{
			RVA0020C3BB_REPORT(name,
				"***Attempting to call script that is not a subroutine:***");
		}
	}
	else
	{
		Script *script = (Script *)lookup->bfmeRunZC(*(BfmeRoomZC *)&name, &canonical);
		if (script)
		{
			if (script->isSubroutine())
			{
				Rva002048A2 restore((AsciiString *)((char *)this + 0x1A10C), canonical);
				rva0020A586(script, &name);
			}
			else
			{
				RVA0020C3BB_REPORT(name,
					"***Attempting to call script that is not a subroutine:***");
			}
		}
		else
		{
			RVA0020C3BB_REPORT(name, "***Script not defined:***");
		}
	}
}

#define RVA0020C140_REPORT(HEADLINE) 	do { 		AppendDebugMessage(AsciiString(HEADLINE), false); 		AppendDebugMessage(Rva0032B389Join(canonical, scriptName), false); 	} while (0)

// ?rva0020C140@ScriptEngine@@QAEXABVAsciiString@@0PAVTeam@@@Z
void ScriptEngine::rva0020C140(const AsciiString &scopeName, const AsciiString &scriptName, Team *pThisTeam)
{
	if (((const StringBase<char> &)scriptName).isEmpty())
		return;
	if (((const StringBase<char> &)scriptName).compare("<none>") == 0)
		return;

	BfmeOwnZC *lookup = (BfmeOwnZC *)this;
	Player *savedPlayer = *(Player **)((char *)this + 0x1A130);
	Team **callingTeam = (Team **)((char *)this + 0x1A110);
	Rva00203CC7 callingTeamLatch(callingTeam, pThisTeam);
	Rva002048A2 scope((AsciiString *)((char *)this + 0x1A10C), scopeName);
	Team *activeTeam = *callingTeam;
	*(Team **)((char *)this + 0x1A118) = 0;
	*(Player **)((char *)this + 0x1A130) = 0;
	if (activeTeam)
		*(Player **)((char *)this + 0x1A130) = activeTeam->getControllingPlayer();

	AsciiString canonical;
	ScriptGroup *group = (ScriptGroup *)lookup->rva00204EBB(*(BfmeRoomZC *)&scriptName, &canonical);
	if (group)
	{
		if (group->isSubroutine())
		{
			if (group->isActive())
			{
				Rva00355950Arr *array = (Rva00355950Arr *)lookup->rva00204E64(canonical);
				if (array)
				{
					Rva002048A2 restore((AsciiString *)((char *)this + 0x1A10C), canonical);
					walkNamed(array, group->getScript(), false);
				}
			}
		}
		else
		{
			RVA0020C140_REPORT("***Attempting to call script that is not a subroutine:***");
		}
	}
	else
	{
		Script *script = (Script *)lookup->bfmeRunZC(*(BfmeRoomZC *)&scriptName, &canonical);
		if (script)
		{
			if (script->isSubroutine())
			{
				Rva002048A2 restore((AsciiString *)((char *)this + 0x1A10C), canonical);
				rva0020A586(script, (void *)&scriptName);
			}
			else
			{
				RVA0020C140_REPORT("***Attempting to call script that is not a subroutine:***");
			}
		}
		else
		{
			RVA0020C140_REPORT("***Script not defined:***");
		}
	}

	*(Player **)((char *)this + 0x1A130) = savedPlayer;
}
