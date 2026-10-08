// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptActions::rva003C5F1B, retail 0x003C5F1B (337B; ret 0x14).
// Target identity: executeAction cases 422 and 522 call it, passing the
// action, its parameters 0..2 and true / false; initActionTemplates names
// those templates SET_PLAYER_OWNERSHIP_OF_TYPE_COUNTER and
// SET_PLAYER_OWNERSHIP_OF_TYPE_COUNTER_INCLUDE_DEAD. WorldBuilder's twin
// (wb 0x01017B90) is unnamed, so the method keeps its address name.
// Target body: when the action's cached frame (ScriptAction+0x44) equals
// TheScriptEngine's frame-object-count-changed stamp (+0x1A15C) nothing is
// recounted; otherwise the type parameter is parsed into an ObjectTypesTemp
// (ctor 0x003BA7FF) and the two STLport vectors filled by
// ObjectTypes::prepForPlayerCounting 0x00376C50, every non-null player of
// the player parameter's mask (rowed rva00357B82, getEachPlayerFromMask)
// counts with countObjectsByThingTemplate 0x002AB0C5 (ignoreDead from the
// case, ignoreUnderConstruction true) and the rowed sum 0x003BD46E, the
// total goes to the counter named by parameter 2 (pinned bfmeCounter
// 0x0020874B) and the action's frame is restamped. This is the shape of the
// rowed ScriptConditions::evaluatePlayerUnitCondition (0x003E9C3B).
// Retail keeps types.m_types in a register across the calls, which VC7.1
// does only with the ObjectTypesTemp ctor visible in this unit, and records
// EH states around the vectors' inline free() calls (/EHs).
#include <string.h>
#include <vector>
#include "ascii_string.h"

class ThingTemplate;

class Parameter
{
public:
	int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }
private:
	unsigned char m_beforeInt[8];
	int m_int;	// +0x08
	float m_real;	// +0x0C
	AsciiString m_string;	// +0x10
};

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	unsigned int getCustomFrame() const { return m_customFrame; }
	void setCustomFrame(unsigned int frame) { m_customFrame = frame; }
private:
	void *m_vtable;
	int m_actionType;	// +0x04
	int m_numParms;	// +0x08
	Parameter *m_parms[MAX_PARMS];	// +0x0C
	ScriptAction *m_nextAction;	// +0x3C
	bool m_hasWarnings;	// +0x40
	unsigned char m_tail;	// +0x41
	char m_pad[2];
	unsigned int m_customFrame;	// +0x44 (BFME2; the ctor zeroes it)
};

class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &templates, _STL::vector<int> &counts);
private:
	AsciiString m_listName; // +0x04
	_STL::vector<AsciiString> m_objectTypes; // +0x08
};

// Zero Hour's ScriptConditions.cpp helper, inline there; retail calls its one
// out-of-line copy (0x003BA7FF).
class ObjectTypesTemp
{
public:
	ObjectTypesTemp() : m_types(0)
	{
		m_types = new ObjectTypes;
	}
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};

void Script_objectTypesFromParam(Parameter *pTypeParm, ObjectTypes *outObjectTypes);

class Player
{
public:
	void countObjectsByThingTemplate(int numThingTemplates, const ThingTemplate *const *things, bool ignoreDead, int *counts, bool ignoreUnderConstruction) const;
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

int __cdecl Rva003BD46ESum(void *range);

struct ScriptCounter
{
	int m_value;
};

class ScriptEngine
{
public:
	int rva00357B82(Parameter *pPlayerParm);
	unsigned int getFrameObjectCountChanged() const { return m_frameObjectCountChanged; }
protected:
	ScriptCounter *bfmeCounter(AsciiString name);
	friend class ScriptActions;
private:
	unsigned char m_pad00[0x1A15C];
	unsigned int m_frameObjectCountChanged; // +0x1A15C
};
extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void rva003C5F1B(ScriptAction *pAction, Parameter *pTypeParm, Parameter *pPlayerParm, Parameter *pCounterParm, bool ignoreDead);
};

void ScriptActions::rva003C5F1B(ScriptAction *pAction, Parameter *pTypeParm, Parameter *pPlayerParm, Parameter *pCounterParm, bool ignoreDead)
{
	if (TheScriptEngine->getFrameObjectCountChanged() == pAction->getCustomFrame())
		return;

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	int numObjs = types.m_types->prepForPlayerCounting(templates, counts);
	if (numObjs == 0)
		return;

	int mask = TheScriptEngine->rva00357B82(pPlayerParm);
	int count = 0;
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer) {
			pPlayer->countObjectsByThingTemplate(numObjs, &(*templates.begin()), ignoreDead, &(*counts.begin()), true);
			count += Rva003BD46ESum(&counts);
		}
	}

	TheScriptEngine->bfmeCounter(pCounterParm->getString())->m_value = count;
	pAction->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
}
