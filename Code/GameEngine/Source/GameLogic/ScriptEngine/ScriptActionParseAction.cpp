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

AsciiString KEYNAME(NameKeyType key);

#include "../../../Include/Common/DataChunkInfo.h"

#include "../../../Include/Common/DataChunk.h"

#include "../../../Include/Common/GameEngine.h"
extern GameEngine *TheGameEngine;

static inline void yieldToOS(void)
{
	Sleep(0);
	if (TheGameEngine)
		TheGameEngine->serviceWindowsOS();
}

#include "../../../Include/GameLogic/ScriptParameter.h"

// Retail 0x003B333A (55 B), the row this unit owns.
Parameter::Parameter(ParameterType type, Int val) :
	m_paramType(type),
	m_initialized(false),
	m_int(val),
	m_real(0.0f),
	m_cachedPlayerMask(0),
	m_objectID(0)
{
	m_coord.x = 0.0f;
	m_coord.y = 0.0f;
	m_coord.z = 0.0f;
}

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

enum { MAX_PARMS = 12 };

#include "../../../Include/GameLogic/ScriptAction.h"

// ScriptAction::ParseAction is rowed at 0x003B5EA5 in Rva003b6d92Finish.cpp; this
// unit no longer carries a second (inline) copy of it.

