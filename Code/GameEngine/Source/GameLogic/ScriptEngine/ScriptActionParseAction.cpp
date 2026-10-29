// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Source/GameLogic/ScriptEngine /DNDEBUG /MD /EHsc
// platformsdk
// ?ParseAction@ScriptAction@@KAPAV1@AAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// readable ZH body: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
//
// BFME ScriptAction::ParseAction for retail 0x00358370 (2545 B: code, then the
// three switch jump tables and their index bytes, ending at the int3 pad).
// Identity: the reloc/export name, and ParseActionDataChunk (0x00358FE0) and
// its ParseActionFalseDataChunk twin call it through the link thunk.
//
// Differences from Zero Hour, all read off the retail bytes: plain operator
// new for the 0x48-byte action (inline protected ctor with the +0x44 tail) and
// for 0x28-byte Parameters; ScriptEngine::getActionTemplate is virtual slot
// 10; the version-2 name check also accepts the renamed
// BUILD_BASE_BUILDING_* spellings for action 0x181; a Sleep(0) /
// serviceWindowsOS yield after each phase; OBJECT_TYPE parameters are
// retyped to 0x3d where the template asks for it (same as
// Condition::ParseConditionDataChunk); and a BFME set of heal-old-files
// cases. Case values come from the retail jump tables, not the ZH enum, so
// they stay numeric. Parameter types up to AI_MOOD keep their ZH ordinals;
// 0x34 and 0x3d are left unnamed. The template retype re-reads the parameter
// type, which retail does; the barrier keeps that second read.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
typedef int Int;
typedef bool Bool;
typedef unsigned short DataChunkVersionType;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#include <windows.h>
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


AsciiString KEYNAME(NameKeyType key);

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	DataChunkVersionType version;
	Int dataSize;
public:
	~DataChunkInfo();
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
class Gen002E3FD0
{
public:
	void bfmeSet(AsciiString value);
};

class Parameter : public Gen002E3FD0
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
	static Parameter *ReadParameter(DataChunkInput &file);

	__declspec(dllimport) __forceinline ParameterType getParameterType() const { return m_paramType; }
	__declspec(dllimport) __forceinline Int getInt() const { return m_int; }
	__declspec(dllimport) __forceinline void friend_setParameterType(ParameterType type) { m_paramType = type; }

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

// Retail 0x003B333A (55 B), the row this unit owns.
Parameter::Parameter(ParameterType type, Int val) :
	m_paramType(type),
	m_initialized(false),
	m_int(val),
	m_real(0.0f),
	m_objectStatus0(0),
	m_objectStatus1(0)
{
	m_coord.x = 0.0f;
	m_coord.y = 0.0f;
	m_coord.z = 0.0f;
}

class ActionTemplate
{
public:
	Int getNumParameters() const { return m_numParameters; }
	Int getParameterType(Int ndx) const
	{
		if (ndx >= 0 && ndx < m_numParameters)
			return m_parameters[ndx];
		return 0;
	}

	char m_head[0x04];
	AsciiString m_name;
	AsciiString m_internalName;
	NameKeyType m_internalNameKey;
	char m_middle[0x34];
	Int m_numParameters;
	Int m_parameters[12];
};

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

class __declspec(novtable) ScriptAction
{
public:
	enum { NO_OP = 5, NUM_ITEMS = 0x21f };
	virtual ~ScriptAction();

protected:
	ScriptAction() :
		m_actionType(NO_OP),
		m_numParms(0),
		m_nextAction(0),
		m_hasWarnings(false),
		m_bfmeActionTail(0)
	{
		Int i;
		for (i = 0; i < MAX_PARMS; i++) {
			m_parms[i] = 0;
		}
	}

	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);
	friend void bfmeEmitScriptActionParseAction(void);

	Int getActionType() const { return m_actionType; }
	Int getNumParameters() const { return m_numParms; }

	Int m_actionType;
	Int m_numParms;
	Parameter *m_parms[MAX_PARMS];
	ScriptAction *m_nextAction;
	Bool m_hasWarnings;
	Int m_bfmeActionTail;
};

// ScriptAction::ParseAction is rowed at 0x003B5EA5 in Rva003b6d92Finish.cpp; this
// unit no longer carries a second (inline) copy of it.

