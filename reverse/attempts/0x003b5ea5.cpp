// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.93 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /Oy- /G7 /arch:SSE /DNDEBUG /MD
// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// ScriptAction::ParseAction, retail 0x003B5EA5, 1818 bytes (WorldBuilder's
// Scripts.cpp, assert lines 4597..4829; registered by the action chunk
// parsers). Semantic donor: GeneralsMD ScriptEngine/Scripts.cpp
// ScriptAction::ParseAction, and ScriptActionParseAction.cpp, the sibling
// reconstruction of the other BFME2 build's 2545-byte ParseAction: the same
// heal-old-files case values (read off the retail compare tree here), the same
// 0x181 renamed-spelling checks. This build differs in the retail bytes:
// ScriptAction's ctor, Parameter's ctor, getActionTemplate and
// Template::getParameterType are out-of-line rowed calls, there is no
// Sleep/serviceWindowsOS yield, version >= 3 reads an extra active flag
// into +0x41, and OBJECT_TYPE parameters are retyped through 0x003B27F8.
// Case values come from the retail compare tree, not the ZH enum.
#include "ascii_string.h"

// Retail registers no unwind state for the copied key name: its literal
// compares cannot throw.
template<> int StringBase<char>::compare(const char *) const throw();
static inline int compareLiteral(const AsciiString &s, const char *literal)
{
	return ((const StringBase<char> *)&s)->compare(literal);
}

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

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
};

// Parameter's by-value string setter (ZH friend_setString); the ledger names
// the body by address only, so Parameter reaches it through this base.
class Rva00333B02
{
public:
	void rva00333B02(AsciiString value);
};

// 0x003B27F8: the OBJECT_TYPE -> object-type-list retype, called on the
// parameter (the ledger spells its class by the address of its template).
class Rva0034FF50
{
public:
	void checkAndSet();
};

class Parameter : public Rva00333B02
{
public:
	enum ParameterType
	{
		INT = 0,
		REAL = 1,
		BOOLEAN = 8,
		SIDE = 11,
		OBJECT_TYPE = 15,
		AI_MOOD = 20
	};

	Parameter(ParameterType type, Int val = 0) throw();
	void destroy() { m_string.~AsciiString(); }

	static Parameter *ReadParameter(DataChunkInput &file);

	ParameterType getParameterType() const { return m_paramType; }
	Int getInt() const { return m_int; }
	Rva0034FF50 *retyper() { return (Rva0034FF50 *)this; }

private:
	ParameterType m_paramType;
	Bool m_initialized;
	Int m_int;
	float m_real;
	AsciiString m_string;
	struct { float x, y, z; } m_coord;
	unsigned int m_objectStatus0;
	unsigned int m_objectStatus1;
};

class Template
{
public:
	Parameter::ParameterType getParameterType(Int ndx) const;
};

class ActionTemplate : public Template
{
public:
	Int getNumParameters() const { return m_numParameters; }

	char m_head[0x08];
	AsciiString m_name;
	AsciiString m_internalName;
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Int m_parameters[12];
};

class ScriptEngine
{
public:
	const ActionTemplate *getActionTemplate(Int type);
};
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class ScriptAction
{
public:
	enum { NO_OP = 5, NUM_ITEMS = 0x257 };
	ScriptAction() throw();
	virtual ~ScriptAction();

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

protected:
	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);

public:
	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	Bool m_active;
	Int m_bfmeActionTail;
};

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
			if (compareLiteral(name, "BUILD_BASE_BUILDING_PER_TACTICAL_MARKER") == 0 ||
				compareLiteral(name, "BUILD_BASE_BUILDING_WITH_TACTIC") == 0) {
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
			parameter->retyper()->checkAndSet();
	}

	if (info->version >= 3)
		pScriptAction->m_active = file.readInt() != 0;
	else
		pScriptAction->m_active = true;

	// heal old files.
	switch (pScriptAction->getActionType()) {
		case 0x24:
			if (pScriptAction->m_numParms == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x0e:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x2d:
		case 0x2e:
			if (pScriptAction->m_numParms >= 2 && pScriptAction->m_parms[1]->getParameterType() == Parameter::INT) {
				pScriptAction->m_parms[1] = new Parameter(Parameter::AI_MOOD, pScriptAction->m_parms[1]->getInt());
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
		case 0x55:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 1);
			}
			break;
		case 0x1a:
		case 0x1b:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[1] = new Parameter((Parameter::ParameterType)0x34, 0);
				pScriptAction->m_parms[2] = new Parameter((Parameter::ParameterType)0x34, 0);
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
		case 0x69:
		case 0x95:
		case 0xe9:
		case 0xea:
			if (pScriptAction->getNumParameters() == 0) {
				pScriptAction->m_numParms = 1;
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
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
		case 0x5d:
		case 0x94:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::SIDE);
			}
			break;
		case 0xfe:
			if (pScriptAction->m_numParms == 1) {
				Parameter *p0 = pScriptAction->m_parms[0];
				Bool flank = p0->getInt() != 0;
				if (p0) {
					p0->destroy();
					::operator delete(p0);
				}
				pScriptAction->m_numParms = 0;
				if (flank)
					pScriptAction->m_actionType = 0x102;
			}
			break;
		case 0x1b2:
		case 0x1b3:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter((Parameter::ParameterType)0x34, 1);
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
		case 0xff:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = pScriptAction->m_parms[0];
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
				pScriptAction->m_parms[0]->rva00333B02("<This Player>");
			}
			break;
	}

	if (at->getNumParameters() != pScriptAction->getNumParameters()) {
		pScriptAction->m_actionType = ScriptAction::NO_OP;
		pScriptAction->m_numParms = 0;
	}
	return pScriptAction;
}
