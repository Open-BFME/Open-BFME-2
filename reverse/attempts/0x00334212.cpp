// ?EvaluateCondition@@YAHPAUlua_State@@@Z
// partial score=0.97 date=2026-10-06
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

struct Coord3D
{
	float x;
	float y;
	float z;
};

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

class ScriptAction { public: Parameter *getParameter(int index); };

class Condition
{
public:
	enum ConditionType { NUM_ITEMS = 0xCA };

	Condition(ConditionType type);
	virtual ~Condition();

	int getNumParameters() const { return m_numParms; }

	ConditionType m_actionType;
	int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAction;
	bool m_hasWarnings;
	int m_bfmeActionTail;
 int m_tail44, m_tail48, m_tail4c;
	
};

class ConditionTemplate
{
public:
	int m_type;
	AsciiString m_uiName;
	AsciiString m_uiName2;
	AsciiString m_internalName;
};

class ScriptEngine
{
public:
 const ConditionTemplate *getConditionTemplate(int type);
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
	virtual bool evaluateCondition(Condition *action);
};

extern ScriptEngine *TheScriptEngine;
extern ScriptConditionsInterface *TheScriptConditions;

// The target Condition view and the matched ScriptAction view share the
// vptr/action-type/count/parameter-array prefix; both parameter getters fold to
// the existing ScriptAction::getParameter owner at 0x00203553. Reuse that
// owner instead of pinning a second real name to the same address.
int EvaluateCondition(lua_State *state)
{
	const char *name = lua_tostring(state, 1);
	int actionType = 0;
	const ConditionTemplate *actionTemplate;

	for (;;)
	{
		actionTemplate = TheScriptEngine->getConditionTemplate((Condition::ConditionType)actionType);
		if (strcmp(name, actionTemplate->m_internalName.str()) == 0)
			break;
		++actionType;
		if (actionType >= Condition::NUM_ITEMS)
			return 0;
	}

	if (actionTemplate == 0)
		return 0;

	Condition *action = new Condition((Condition::ConditionType)actionType);

	// Argument 1 is the action name; the rest fill its parameters.
	int numArgs = lua_gettop(state);
	if (numArgs != action->getNumParameters() + 1)
		return 0;

	for (int i = 0; i < numArgs - 1; ++i)
	{
		Parameter *parameter = reinterpret_cast<ScriptAction *>(action)->getParameter(i);
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
		else if (lua_type(state, i + 2) == 1)
        {
            parameter->friend_setInt(0);
        }
		else
		{
			return 0;
		}
	}

	bool result = TheScriptConditions->evaluateCondition(action);
	::delete action;
	bfmeGo1039E((BfmeQ1039 *)state, result ? 1 : 0);
	return 1;
}
