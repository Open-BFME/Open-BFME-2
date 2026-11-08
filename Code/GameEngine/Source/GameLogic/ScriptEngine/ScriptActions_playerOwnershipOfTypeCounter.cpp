// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ScriptActions::rva003C5F1B, retail 0x003C5F1B (337B; ret 0x14).
// Target identity: executeAction cases 422 and 522 call it, passing the
// action, its parameters 0..2 and true / false; initActionTemplates names
// those templates SET_PLAYER_OWNERSHIP_OF_TYPE_COUNTER and
// SET_PLAYER_OWNERSHIP_OF_TYPE_COUNTER_INCLUDE_DEAD. WorldBuilder's twin
// (wb 0x01017B90) is unnamed, so the method keeps its address name.
// Target body: when the action's cached frame (ScriptAction+0x44, field44) equals
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
class ModuleData;
class Drawable;

// Native 0x00376C50 is the existing 82-byte RET8 provider below. Its
// receiver reads the same name-vector prefix at +8/+0xC. Both vector views
// use STLport's begin/end/storage words and four-byte trivial elements:
// the first receives ThingFactory pointers; the second is resized with zeros.
// ModuleData/Drawable are the provider's physical fold names, not recovered
// identities for the templates and integer counters used by this caller.
class Rva00376C50Owner
{
public:
	unsigned int rva00376C50(_STL::vector<const ModuleData *> &found,
		_STL::vector<Drawable *> &slots);
};

#include "../../../Include/GameLogic/ScriptParameter.h"

#include "../../../Include/GameLogic/ScriptAction.h"

#include "../../../Include/GameLogic/ObjectTypesClass.h"

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

#include "../../../Include/Common/Player.h"

#include "../../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

int __cdecl Rva003BD46ESum(void *range);

#include "../../../Include/GameLogic/ScriptCounter.h"

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/ScriptActionsBFME2.h"

void ScriptActions::rva003C5F1B(ScriptAction *pAction, Parameter *pTypeParm, Parameter *pPlayerParm, Parameter *pCounterParm, bool ignoreDead)
{
	if (TheScriptEngine->m_frameObjectCountChanged == (unsigned int)pAction->field44)
		return;

	_STL::vector<int> counts;
	_STL::vector<const ThingTemplate *> templates;

	ObjectTypesTemp types;
	Script_objectTypesFromParam(pTypeParm, types.m_types);

	int numObjs = (int)((Rva00376C50Owner *)types.m_types)->rva00376C50(
		(_STL::vector<const ModuleData *> &)templates,
		(_STL::vector<Drawable *> &)counts);
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
	pAction->field44 = TheScriptEngine->m_frameObjectCountChanged;
}

// The retail call in this body reads 0x00376C50, an address the ledger already
// carries as ?rva00376C50@Rva00376C50Owner@@QAEIAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@AAV?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@3@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?prepForPlayerCounting@ObjectTypes@@QAEHAAV?$vector@PBVThingTemplate@@V?$allocator@PBVThingTemplate@@@_STL@@@_STL@@AAV?$vector@HV?$allocator@H@_STL@@@3@@Z=?rva00376C50@Rva00376C50Owner@@QAEIAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@AAV?$vector@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@3@@Z")
