// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/iniexception -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
//
// The DebugCommandMap block. It reads the entry name and throws it away, parses
// a full entry into a local, and then discards that too -- so in a release build
// the block validates its own syntax and stores nothing. The retail code really
// is this: getNextToken with the result unused, initFromINI into stack space,
// and two UnicodeString destructors on the way out.
//
// Field names and offsets are the retail table at 0x0110E570
// (docs/ini_schema.md). Nothing writes 0x00-0x07, so that stays a pad.
#include "PreRTS.h"
#include "Common/INI.h"

struct DebugCommandMapEntry
{
	char m_unknown00[ 0x08 ];		// 0x00  no INI field writes here
	Int m_key;						// 0x08  Key
	Int m_transition;				// 0x0c  Transition
	Int m_modifiers;				// 0x10  Modifiers
	Int m_useableIn;				// 0x14  UseableIn
	Int m_category;					// 0x18  Category
	UnicodeString m_description;	// 0x1c  Description
	UnicodeString m_displayName;	// 0x20  DisplayName

	static const FieldParse m_fieldParseTable[];
};

void parseDebugCommandMap( INI *ini )
{
	ini->getNextToken();

	DebugCommandMapEntry entry;
	ini->initFromINI( &entry, DebugCommandMapEntry::m_fieldParseTable );
}
