// ?ParseConditionDataChunk@Condition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.99 date=2026-10-05
// ?ParseConditionDataChunk@Condition@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// cl: /Ireference/shims/bfme2_ascii /Gy /DNDEBUG /MD
// BFME1 donor 6583b3c1: Condition_ParseConditionDataChunk_Thunk.cpp.
// Target callback registered as Condition by OrCondition parser 3B7587.
// BFME2 layout 50 bytes, template bound CA, internal key +10, two flags
// at +4C/+4D, and versions 2/6 parameter repairs are read from native709.
// ParameterChangesVer2 values verified in target data at RVA9C10DC.
// Shared 24-byte Template and 12-byte remapper emitted before the parser
// retain native caller register usage; /Gy makes these common copies.
//
// Template::getParameterType 0x003B27A3 (24 bytes), ScriptAction::setActionType
// 0x003B4343 and Condition::setConditionType 0x003B4A94 (137 bytes each) share
// this unit as they shared retail's Scripts.cpp: all three callers keep the new
// parameter pointer in edx across getParameterType, which cl only does when that
// callee was compiled earlier in the same TU, so one unit must own the callee.
// BFME1 donor Scripts.cpp setActionType/setConditionType: free the old
// parameters, store the type, look the template up through the pinned
// ScriptEngine::getActionTemplate 0x00203926 / getConditionTemplate 0x00203941
// and new one Parameter per template slot. Retail deltas: the delete inlines to
// releaseBuffer 0x00036410 plus ::operator delete (not a pooled deleteInstance).
// ZH Template::getParameterType with DEBUG_CRASH compiled out (/DNDEBUG)
// returns Parameter::INT (0) out of range, matching retail xor eax,eax.

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"


class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00333B02 { public: void rva00333B02(AsciiString); };
class Rva0034FF50 { public: __declspec(noinline) void checkAndSet(); int m_val0; };
void Rva0034FF50::checkAndSet() { if (m_val0 == 15) m_val0 = 61; }

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
};

class DataChunkInput
{
public:
	Int readInt();
	NameKeyType readNameKey();
	DataChunkVersionType getChunkVersion();
	Bool atEndOfChunk();
};

class Parameter
{
public:
	enum ParameterType
	{
		INT = 0,
		REAL = 1,
		BOOLEAN = 8,
		AI_MOOD = 20,
		OBJECT_TYPE = 0x0f,
		SIDE = 0x0b,
		SURFACES_ALLOWED = 0x25,
		TEMPLATE_REMAP_TYPE = 0x3d
	};

	Parameter(ParameterType type, Int value = 0) throw();

	static Parameter *ReadParameter(DataChunkInput &file);

	void deleteInstance() { this->~Parameter(); ::operator delete(this); }

	__forceinline ParameterType getParameterType() const
	{
		return m_paramType;
	}

	Int getInt() const { return m_int; }

	__forceinline void friend_setString(AsciiString text)
	{
		((Rva00333B02 *)this)->rva00333B02(text);
	}
	__forceinline void friend_setParameterType(ParameterType type)
	{
		((Rva0034FF50 *)this)->checkAndSet();
	}

private:
	ParameterType m_paramType;
	bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	Coord3D m_coord;
	struct ObjectStatusMask
	{
		__forceinline ObjectStatusMask() : m_low(0), m_high(0) {}
		unsigned int m_low;
		unsigned int m_high;
	} m_objectStatus;
};

class Template
{
public:
	__declspec(dllimport) __forceinline Int getNumParameters() const { return m_numParameters; }
	__declspec(noinline) Parameter::ParameterType getParameterType(Int index) const;
	char m_prefix[0x0C];
	AsciiString m_internalName;
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Parameter::ParameterType m_parameters[12];
};
Parameter::ParameterType Template::getParameterType(Int index) const
{
	if (index >= 0 && index < m_numParameters) return m_parameters[index];
	return (Parameter::ParameterType)0;
}
class ActionTemplate : public Template {};
class ConditionTemplate : public Template {};
class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(Int type) throw();
	const ConditionTemplate *getConditionTemplate(Int type) throw();
};

extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum ScriptActionType
	{
		NO_OP = 5,
		NUM_ITEMS = 0x257
	};
	ScriptAction() throw();
	void setActionType(ScriptActionType type);

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

protected:
	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);

private:
	void *m_vtable; // +0x00
	Int m_actionType; // +0x04
	Int m_numParms; // +0x08
	Parameter *m_parms[MAX_PARMS]; // +0x0C
	ScriptAction *m_nextAction; // +0x3C
	Bool m_hasWarnings; // +0x40
	Bool m_active; // +0x41
	Int m_bfmeActionTail; // +0x44
};

void ScriptAction::setActionType(ScriptActionType type)
{
	Int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_actionType = type;
	const ActionTemplate *pTemplate = TheScriptEngine->getActionTemplate(m_actionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}

#include "../../../Include/Common/MemoryPoolObject.h"

class Condition : public MemoryPoolObject
{
public:
	virtual ~Condition();

	enum ConditionType
	{
		CONDITION_FALSE = 0,
		SKIRMISH_SPECIAL_POWER_READY = 0x55,
		NUM_ITEMS = 0xca
	};

	Condition() throw();

	void setConditionType(ConditionType type);

	static Bool __cdecl ParseConditionDataChunk(DataChunkInput &file,
		DataChunkInfo *info, void *userData);

	__forceinline ConditionType getConditionType() const
	{
		return m_conditionType;
	}

	__forceinline Condition *getNext() const
	{
		return m_nextAndCondition;
	}

	__forceinline Int getNumParameters() const
	{
		return m_numParms;
	}

	__forceinline void setNextCondition(Condition *condition)
	{
		m_nextAndCondition = condition;
	}

private:
	ConditionType m_conditionType;
	Int m_numParms;
	Parameter *m_parms[12];
	Condition *m_nextAndCondition;
	Int m_hasWarnings;
	Int m_customData;
	unsigned int m_customFrame;
	Bool m_flag4C;
	Bool m_flag4D;
	char m_pad[2];
};

class OrCondition
{
public:
	__forceinline Condition *getFirstAndCondition() const
	{
		return m_firstAnd;
	}

	__forceinline void setFirstAndCondition(Condition *condition)
	{
		m_firstAnd = condition;
	}

private:
	void *m_vtable;
	OrCondition *m_nextOr;
	Condition *m_firstAnd;
};

void Condition::setConditionType(ConditionType type)
{
	Int i;
	for (i = 0; i < m_numParms; i++) {
		if (m_parms[i])
			m_parms[i]->deleteInstance();
		m_parms[i] = 0;
	}
	m_conditionType = type;
	const ConditionTemplate *pTemplate = TheScriptEngine->getConditionTemplate(m_conditionType);
	m_numParms = pTemplate->getNumParameters();
	for (i = 0; i < m_numParms; i++) {
		m_parms[i] = new Parameter(pTemplate->getParameterType(i));
	}
}

ScriptAction *ScriptAction::ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	ScriptAction *pScriptAction = new ScriptAction;

	pScriptAction->m_actionType = file.readInt();

	const ActionTemplate *at = TheScriptEngine->getActionTemplate(pScriptAction->m_actionType);
	if (info->version >= 2) {
		NameKeyType key = file.readNameKey();
		Bool match = false;
		if (at) {
			if (at->m_internalNameKey == key) {
				match = true;
			} else if (pScriptAction->m_actionType == 0x181 &&
				(at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				 at->m_internalName.compare("BUILD_BASE_BUILDING_PER_TACTIC") == 0)) {
				match = true;
			}
		}
		if (!match && pScriptAction->m_actionType == 0x181) {
			AsciiString name = TheNameKeyGenerator->keyToName(key);
			if (name.compare("BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				name.compare("BUILD_BASE_BUILDING_WITH_TACTIC") == 0) {
				match = true;
			}
		}
		if (!match) {
			Int i;
			for (i = 0; i < ScriptAction::NUM_ITEMS; i++) {
				at = TheScriptEngine->getActionTemplate(i);
				if (key == at->m_internalNameKey) {
					match = true;
					pScriptAction->m_actionType = i;
					break;
				}
			}
			if (!match) {
				pScriptAction->m_actionType = ScriptAction::NO_OP;
				pScriptAction->m_numParms = 0;
			}
		}
	}

	pScriptAction->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pScriptAction->m_numParms; i++) {
		Parameter *parameter = Parameter::ReadParameter(file);
		pScriptAction->m_parms[i] = parameter;
		if (parameter->getParameterType() == Parameter::OBJECT_TYPE && at->getNumParameters() > i &&
			at->getParameterType(i) == 0x3d)
			parameter->friend_setParameterType(Parameter::TEMPLATE_REMAP_TYPE);
	}

	if (info->version >= 3)
		pScriptAction->m_active = file.readInt() != 0;
	else
		pScriptAction->m_active = true;

	// heal old files.
	switch (pScriptAction->getActionType()) {
		case 0x1b2:
		case 0x1b3:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter((Parameter::ParameterType)0x34, 1);
			}
			break;
		case 0xff:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = pScriptAction->m_parms[0];
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
				((Rva00333B02 *)pScriptAction->m_parms[0])->rva00333B02("<This Player>");
			}
			break;
		case 0x24:
			if (pScriptAction->m_numParms == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0xfe:
			if (pScriptAction->m_numParms == 1) {
				Bool flank = pScriptAction->m_parms[0]->getInt() != 0;
				if (pScriptAction->m_parms[0])
					pScriptAction->m_parms[0]->deleteInstance();
				pScriptAction->m_numParms = 0;
				if (flank)
					pScriptAction->m_actionType = 0x102;
			}
			break;
		case 0x2d:
		case 0x2e:
			if (pScriptAction->m_numParms >= 2 && pScriptAction->m_parms[1]->getParameterType() == Parameter::INT) {
				pScriptAction->m_parms[1] = new Parameter(Parameter::AI_MOOD, pScriptAction->m_parms[1]->getInt());
			}
			break;
		case 0x5d:
		case 0x94:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0x69:
		case 0x95:
		case 0xe9:
		case 0xea:
			if (pScriptAction->getNumParameters() == 0) {
				pScriptAction->m_numParms = 1;
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0x55:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 1);
				break;
			}
		case 0x1a:
		case 0x1b:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
			}
			break;
		case 0x0e:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x12:
		case 0x13:
		case 0x78:
		case 0x79:
		case 0x154:
		case 0x15a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
			}
			break;
		case 0xd2:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			} else if (pScriptAction->getNumParameters() == 4) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[4] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x52:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x7a:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::REAL);
			}
			break;
		case 0xb9:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x11:
		case 0x186:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL);
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL);
			} else if (pScriptAction->getNumParameters() == 5) {
				pScriptAction->m_numParms = 6;
				pScriptAction->m_parms[5] = new Parameter(Parameter::REAL, 0);
			}
			break;
	}

	if (at->getNumParameters() != pScriptAction->getNumParameters()) {
		pScriptAction->m_actionType = ScriptAction::NO_OP;
		pScriptAction->m_numParms = 0;
	}
	return pScriptAction;
}

static int ParameterChangesVer2[] =
{
	7, 17, 18, 41, 40, 42, 43, -1
};

Bool __cdecl Condition::ParseConditionDataChunk(DataChunkInput &file,
	DataChunkInfo *info, void *userData)
{
	Condition *pCondition = new Condition;
	OrCondition *pOr = (OrCondition *)userData;
	pCondition->m_conditionType = (ConditionType)file.readInt();
	const ConditionTemplate *ct =
		TheScriptEngine->getConditionTemplate(pCondition->m_conditionType);
	Bool match = false;
	if (info->version >= 4)
	{
		NameKeyType key = file.readNameKey();
		Int i;
		if (ct && ct->m_internalNameKey == key)
			match = true;
		if (!match) {
		for (i = 0; i < Condition::NUM_ITEMS; ++i)
		{
			ct = TheScriptEngine->getConditionTemplate(i);
			if (key == ct->m_internalNameKey)
			{
				pCondition->m_conditionType = (ConditionType)i;
				match = true; break;
			}
		}
		}
	}
	pCondition->m_numParms = file.readInt();
	Int i;
	for (i = 0; i < pCondition->m_numParms; ++i)
	{
		Parameter *parameter = Parameter::ReadParameter(file);
		pCondition->m_parms[i] = parameter;
		if (parameter->getParameterType() != Parameter::OBJECT_TYPE)
			continue;
		if (ct->getNumParameters() > i &&
			ct->getParameterType(i) == Parameter::TEMPLATE_REMAP_TYPE)
		{
			parameter->friend_setParameterType(Parameter::TEMPLATE_REMAP_TYPE);
		}
	}
	if (info->version >= 5)
	{
		pCondition->m_flag4C = file.readInt() != 0;
		pCondition->m_flag4D = file.readInt() != 0;
	}
	else
	{
		pCondition->m_flag4C = true;
		pCondition->m_flag4D = false;
	}
	if (!match)
	{
		ct = TheScriptEngine->getConditionTemplate(CONDITION_FALSE);
		pCondition->m_conditionType = CONDITION_FALSE;
		while (pCondition->m_numParms > 0)
		{
			--pCondition->m_numParms;
			Parameter *parameter = pCondition->m_parms[pCondition->m_numParms];
			if (parameter)
				delete parameter;
		}
	}

	if (file.getChunkVersion() < 2)
	{
		for (Int j = 0; ParameterChangesVer2[j] != -1; ++j)
		{
			if (pCondition->m_conditionType == (ConditionType)ParameterChangesVer2[j])
			{
				pCondition->m_parms[pCondition->m_numParms] =
					new Parameter(Parameter::SURFACES_ALLOWED, 3);
				pCondition->m_numParms = 3;
			}
		}
	}
	else if (file.getChunkVersion() < 6)
	{
		for (Int j = 0; ParameterChangesVer2[j] != -1; ++j)
		{
			if (pCondition->m_conditionType == (ConditionType)ParameterChangesVer2[j])
			{
				delete pCondition->m_parms[pCondition->m_numParms-1];
				pCondition->m_parms[pCondition->m_numParms-1] = new Parameter(Parameter::SURFACES_ALLOWED, 0);
			}
		}
	}
	switch (pCondition->getConditionType())
	{
		case SKIRMISH_SPECIAL_POWER_READY:
			if (pCondition->m_numParms == 1)
			{
				pCondition->m_numParms = 2;
				pCondition->m_parms[1] = pCondition->m_parms[0];
				pCondition->m_parms[0] = new Parameter(Parameter::SIDE, 0);
				((Rva00333B02 *)pCondition->m_parms[0])->rva00333B02(AsciiString("<This Player>"));
			}
			break;
	}
	if (ct->getNumParameters() != pCondition->m_numParms)
	{
		ct = TheScriptEngine->getConditionTemplate(CONDITION_FALSE);
		pCondition->m_conditionType = CONDITION_FALSE;
		while (pCondition->m_numParms > 0)
		{
			--pCondition->m_numParms;
			Parameter *parameter = pCondition->m_parms[pCondition->m_numParms];
			if (parameter)
				delete parameter;
		}
	}
	Condition *pLast = pOr->getFirstAndCondition();
	while (pLast && pLast->getNext())
		pLast = pLast->getNext();
	if (pLast)
		pLast->setNextCondition(pCondition);
	else
		pOr->setFirstAndCondition(pCondition);
	return true;
}
