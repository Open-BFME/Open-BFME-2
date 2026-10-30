// LuaScriptEngine::ExecuteScriptAction (0x0033436F, 407B): the Lua action dispatcher.
// The two redundant self-compares of TheScriptEngine in the loop condition fold
// away (no bytes) and give retail's top-test loop layout.
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
#include <string.h>

#pragma function(strcmp)

#include "ascii_string.h"

struct lua_State;

extern "C" const char *lua_tostring(lua_State *state, int index);
extern "C" int lua_gettop(lua_State *state);
extern "C" int lua_isnumber(lua_State *state, int index);
extern "C" double lua_tonumber(lua_State *state, int index);
extern "C" int lua_isstring(lua_State *state, int index);
extern "C" int lua_type(lua_State *state, int index);
struct Rva00990030Range;
unsigned Rva00990030Lookup(Rva00990030Range*,int);
struct Rva00990210Range;
unsigned Rva00990210Lookup(Rva00990210Range*,int);

struct BfmeQ1039;
void bfmeGo1039E(BfmeQ1039 *queue, int value);

#include "../../../Libraries/Include/Lib/Coord3D.h"

class ObjectStatusMask
{
	unsigned int m_bits[2];
};

class Rva00333B02 { public: void rva00333B02(AsciiString value); };

class Parameter
{
public:
	void friend_setInt(int value) { m_int = value; }
	void friend_setReal(float value) { m_real = value; }
 void setWord24(unsigned value) { *(unsigned*)((char*)this+0x24)=value; }

private:
	int m_paramType;
	bool m_initialized;
	int m_int;
	float m_real;

public:
	AsciiString m_string;

private:
	Coord3D m_coord;
	ObjectStatusMask m_objectStatus;
};

class ScriptAction
{
public:
	enum ScriptActionType { NUM_ITEMS = 0x257 };
	Parameter *getParameter(int index);
	ScriptAction(ScriptActionType type);
	int getNumParameters() const { return m_numParms; }
	virtual ~ScriptAction();
	ScriptActionType m_actionType; // +0x04
	int m_numParms; // +0x08
	Parameter *m_parms[12]; // +0x0C
	ScriptAction *m_nextAction; // +0x3C
	bool m_hasWarnings; // +0x40
	char m_pad41[0x3];
	int m_bfmeActionTail; // +0x44
};

class ActionTemplate
{
public:
	int m_type;
	AsciiString m_uiName;
	AsciiString m_uiName2;
	AsciiString m_internalName;
};

#include "../../Include/GameLogic/ScriptEngine.h"

class ScriptActionsInterface
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
	virtual void executeAction(ScriptAction *action);
};

extern ScriptEngine *TheScriptEngine;
// Use ScriptEngine_init's global type; the interface class is a local call view.
class ScriptActions;
extern ScriptActions *TheScriptActions;

// ?ExecuteAction@@YAHPAUlua_State@@@Z
int ExecuteAction(lua_State *state)
{
	const char *name = lua_tostring(state, 1);
	int actionType = 0;
	const ActionTemplate *actionTemplate;

	while ((true) && TheScriptEngine==TheScriptEngine && TheScriptEngine==TheScriptEngine)  // tautology carrier: folds away, gives retail's loop-test layout
	{
		actionTemplate = TheScriptEngine->getActionTemplate((ScriptAction::ScriptActionType)actionType);
		if (strcmp(name, actionTemplate->m_internalName.str()) == 0)
			break;
		++actionType;
		if (actionType >= ScriptAction::NUM_ITEMS)
			return 0;
	}

	if (actionTemplate == 0)
		return 0;

	ScriptAction *action = new ScriptAction((ScriptAction::ScriptActionType)actionType);

	// Argument 1 is the action name; the rest fill its parameters.
	int numArgs = lua_gettop(state);
	if (numArgs != action->getNumParameters() + 1)
		return 0;

	for (int i = 0; i < numArgs - 1; ++i)
	{
		Parameter *parameter = action->getParameter(i);
		if (lua_isnumber(state, i + 2))
		{
			double value = lua_tonumber(state, i + 2);
			parameter->friend_setReal(value);
			parameter->friend_setInt(value);
		}
		else if (lua_isstring(state, i + 2))
		{
			((Rva00333B02*)parameter)->rva00333B02(AsciiString(lua_tostring(state, i + 2)));
		}
		else if (lua_type(state, i + 2) == 6)
        {
            parameter->friend_setInt(Rva00990210Lookup((Rva00990210Range*)state,i+2)!=0);
        }
        else if (lua_type(state,i+2)==4 && Rva00990030Lookup((Rva00990030Range*)state,i+2))
        {
            parameter->setWord24(Rva00990030Lookup((Rva00990030Range*)state,i+2));
        }
		else
		{
			return 0;
		}
	}

	((ScriptActionsInterface *)TheScriptActions)->executeAction(action);
	::delete action;
	bfmeGo1039E((BfmeQ1039 *)state, 1);
	return 1;
}
