// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// partial score=0.8102 date=2026-10-08
// cl: /O1 /Oy- /Ireference/shims/bfme2_ascii /G7 /arch:SSE /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine /DNDEBUG /MD /GX-
// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// readable ZH body: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
//
// BFME 2 target: 0x003B5EA5..0x003B65BF, 1818 bytes (Ghidra FUN_007b5ea5).
// Primary semantic donor: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptActionParseAction.cpp.
// Target evidence: Scripts.h literal, action template lookup, parameter reads,
// version-2 name migrations, and version-3 flag at action+0x41.
// Target adaptations: nonvirtual template lookup; 0x257 action bound; no OS yield;
// const-reference keyToName; known checkAndSet remap; native string setter.
// Partial: first 0x190 bytes exact; emitted 1814 versus 1818 bytes. Legacy-case
// block sharing and final by-value string temporary stack save still differ.
// Before landing, reconcile helper providers and preserve the existing 55-byte
// Parameter constructor: global /Oy- changes that constructor to 57 bytes.
// ReadParameter's 516-byte provider also remains unrowed.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void __cdecl operator delete(void *ptr);

typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

#include "ascii_string.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

private:
	friend class AsciiString;
	friend class Parameter;
	void releaseBuffer();
	char *m_data;
};


class NameKeyGenerator {
public:
 const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;
#define KEYNAME(key) TheNameKeyGenerator->keyToName(key)

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

class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void serviceWindowsOS();
};
extern GameEngine *TheGameEngine;

static inline void yieldToOS(void)
{
	Sleep(0);
	if (TheGameEngine)
		TheGameEngine->serviceWindowsOS();
}

// Parameter's by-value string setter (ZH friend_setString); the ledger names
// the body by address only, so Parameter reaches it through this empty base.
class Rva00333B02
{
public:
	void rva00333B02(AsciiString value);
};

class Rva0034FF50 { public: __declspec(noinline) void checkAndSet(); int m_val0; };
void Rva0034FF50::checkAndSet() { if (m_val0 == 15) m_val0 = 61; }

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

	Parameter(ParameterType type, Int val = 0);
	__forceinline ~Parameter() {}
	__forceinline void deleteInstance() { m_string.clear(); ::operator delete(this); }
	static Parameter *ReadParameter(DataChunkInput &file);

	ParameterType getParameterType() const { return m_paramType; }
	Int getInt() const { return m_int; }
	void friend_setParameterType(ParameterType type) { ((Rva0034FF50 *)this)->checkAndSet(); }

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
 Int getNumParameters() const { return m_numParameters; }
 __declspec(noinline) Parameter::ParameterType getParameterType(Int ndx) const;
 char m_head[0x08];
 AsciiString m_name;
 AsciiString m_internalName;
 NameKeyType m_internalNameKey;
 char m_middle[0x34];
 Int m_numParameters;
 Int m_parameters[12];
};
Parameter::ParameterType Template::getParameterType(Int ndx) const
{
 if(ndx>=0 && ndx<m_numParameters) return (Parameter::ParameterType)m_parameters[ndx];
 return Parameter::INT;
}
class ActionTemplate : public Template {};
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
	virtual ~ScriptAction();

protected:
public:
	ScriptAction();
protected:

	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);
	friend void bfmeEmitScriptActionParseAction(void);

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	Bool m_tail;
	Int m_bfmeActionTail;
};

// ?ParseAction@ScriptAction@@ present-unmatched
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
			AsciiString name = KEYNAME(key);
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
			at->getParameterType(i) == 0x3d) {
			parameter->friend_setParameterType((Parameter::ParameterType)0x3d);
		}
	}

	if (info->version >= 3)
		pScriptAction->m_tail = file.readInt() != 0;
	else
		pScriptAction->m_tail = true;
	// heal old files.
	switch (pScriptAction->getActionType()) {
		case 0x24:
			if (pScriptAction->m_numParms == 3) {
				pScriptAction->m_numParms = 4;
				pScriptAction->m_parms[3] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x2d:
		case 0x2e:
			if (pScriptAction->m_numParms >= 2 && pScriptAction->m_parms[1]->getParameterType() == Parameter::INT) {
				pScriptAction->m_parms[1] = new Parameter(Parameter::AI_MOOD, pScriptAction->m_parms[1]->getInt());
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
		case 0x0e:
			if (pScriptAction->getNumParameters() == 3) {
				pScriptAction->m_numParms = 5;
				pScriptAction->m_parms[3] = new Parameter(Parameter::REAL, 0);
				pScriptAction->m_parms[4] = new Parameter(Parameter::REAL, 0);
			}
			break;
		case 0x52:
			if (pScriptAction->getNumParameters() == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = new Parameter(Parameter::BOOLEAN, 0);
			}
			break;
		case 0x5d:
		case 0x94:
			if (pScriptAction->getNumParameters() == 2) {
				pScriptAction->m_numParms = 3;
				pScriptAction->m_parms[2] = new Parameter(Parameter::SIDE);
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
		case 0xfe:
			if (pScriptAction->m_numParms == 1) {
				Bool flank = pScriptAction->m_parms[0]->getInt() != 0;
				if (pScriptAction->m_parms[0]) pScriptAction->m_parms[0]->deleteInstance();
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
		case 0xff:
			if (pScriptAction->m_numParms == 1) {
				pScriptAction->m_numParms = 2;
				pScriptAction->m_parms[1] = pScriptAction->m_parms[0];
				pScriptAction->m_parms[0] = new Parameter(Parameter::SIDE);
				pScriptAction->m_parms[0]->rva00333B02("<This Player>");
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
	}

	if (at->getNumParameters() != pScriptAction->getNumParameters()) {
		pScriptAction->m_actionType = ScriptAction::NO_OP;
		pScriptAction->m_numParms = 0;
	}
	return pScriptAction;
}

// This TU must not strongly define ParseAction (Scripts.cpp owns the kept
// copy), but its body stages the future row and its Parameter uses emit the
// ledger row below, so the body stays inline and this anchor forces the
// select-any copy out.
// ?bfmeEmitScriptActionParseAction@@YAXXZ present-unmatched
void bfmeEmitScriptActionParseAction(void)
{
	DataChunkInput file;
	DataChunkInfo info;
	ScriptAction::ParseAction(file, &info, 0);
}

Parameter::Parameter(ParameterType type, Int val) :
 m_paramType(type), m_initialized(false), m_int(val), m_real(0.0f),
 m_objectStatus0(0),m_objectStatus1(0)
{
 m_coord.x=0.0f; m_coord.y=0.0f; m_coord.z=0.0f;
}
