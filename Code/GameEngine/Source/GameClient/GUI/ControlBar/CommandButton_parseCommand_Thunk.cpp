// cl: /DNDEBUG /MD /EHs-c-
// Lift CommandButton::parseCommand to clean C++.
//
// An INI name-to-index lookup: take the next token, walk a null-terminated table
// of names comparing case-insensitively, and store the matching index through the
// store pointer. A miss throws.
//
// The comparison goes through the import table -- MSVC hoists the slot into a
// register before the loop and calls through it -- and the retail binary imports
// _strcmpi, not _stricmp. Declaring the wrong one of that pair still builds and
// still byte-matches, because the slot address is a copied DIR32, so it has to
// be got right by reading the imports rather than by trusting the build.
//
// The throw is the same shape as ThingTemplate::parseAddModule: a variadic and
// therefore __cdecl constructor taking `this` as its first stack argument, and
// the exception type needs a declared copy constructor or MSVC builds the object
// and then copies it into a second slot instead of constructing it in place.

typedef int Int;

#include <string.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
#include "../../../../Include/Common/INI/FieldParse.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);		///< ILT thunk at 0x00850970
};

// BFME1 donor9e3be919 retains the table role/name; BFME2 native entries
// independently prove this 62-pointer table ending at its first nullDBFCE4.
// The provisional472B extent includes neighboring name arrays; only248B
// belong here. Native vocabulary is represented as a typed text aggregate
// plus eight shared literals. This grouping is an implementation choice,
// not a claim about original compiler-pooled literal ownership. Each field
// extent includes independently checked zero padding through the next text.
struct CommandNameVocabularyText {
    char CANCEL_NEIGHBORHOOD[20];
    char START_NEIGHBORHOOD_REPAIR[28];
    char SET_STANCE[12];
    char TOGGLE_STANCE[16];
    char POP_VISIBLE_COMMAND_RANGE[28];
    char PUSH_VISIBLE_COMMAND_RANGE[28];
    char DOZER_CONSTRUCT_CANCEL[24];
    char DOZER_CONSTRUCT[16];
    char HORDE_SET_FORMATION[20];
    char START_SELF_REPAIR[20];
    char CASTLE_UNPACK_EXPLICIT_OBJECT[32];
    char WAKE_AUTO_PICKUP[20];
    char TOGGLE_NO_AUTO_ACQUIRE[24];
    char MONSTERDOCK[12];
    char REVIVE[8];
    char TOGGLE_WEAPONSET[20];
    char TOGGLE_GATE[12];
    char OPEN_GATE[12];
    char CLOSE_GATE[12];
    char CREW_EVACUATE[16];
    char SPECIAL_POWER_TOGGLE[24];
    char HORDE_TOGGLE_FORMATION[24];
    char TOGGLE_WEAPON[16];
    char CASTLE_PACK[12];
    char CASTLE_UNPACK[16];
    char SPECIAL_POWER_FROM_COMMAND_CENTER[36];
    char CONVERT_TO_CARBOMB[20];
    char HIJACK_VEHICLE[16];
    char AUTOCAST_WEAPON[16];
    char SWITCH_WEAPON[16];
    char COMBATDROP[12];
    char PURCHASE_SCIENCE[20];
    char SPECIAL_POWER[16];
    char FIRE_WEAPON[12];
    char SET_RALLY_POINT[16];
    char BEACON_DELETE[16];
    char EXECUTE_UNUSED_01[20];
    char EVACUATE_CONTESTED[20];
    char EVACUATE[12];
    char EXIT_CONTAINER[16];
    char WAYPOINTS[12];
    char GUARD_FLYING_UNITS_ONLY[24];
    char GUARD_WITHOUT_PURSUIT[24];
    char GUARD[8];
    char ATTACK_MOVE[12];
    char CANCEL_UPGRADE[16];
    char CASTLE_UPGRADE[16];
    char OBJECT_UPGRADE[16];
    char CANCEL_UNIT_BUILD[20];
    char SECONDARY_UNIT_BUILD[24];
    char UNIT_BUILD[12];
    char FOUNDATION_CONSTRUCT_CANCEL[28];
    char FOUNDATION_CONSTRUCT[24];
};
extern const CommandNameVocabularyText gCommandNameVocabularyText = {
    "CANCEL_NEIGHBORHOOD", // VA 00C15B58
    "START_NEIGHBORHOOD_REPAIR", // VA 00C15B6C
    "SET_STANCE", // VA 00C15B88
    "TOGGLE_STANCE", // VA 00C15B94
    "POP_VISIBLE_COMMAND_RANGE", // VA 00C15BA4
    "PUSH_VISIBLE_COMMAND_RANGE", // VA 00C15BC0
    "DOZER_CONSTRUCT_CANCEL", // VA 00C15BDC
    "DOZER_CONSTRUCT", // VA 00C15BF4
    "HORDE_SET_FORMATION", // VA 00C15C04
    "START_SELF_REPAIR", // VA 00C15C18
    "CASTLE_UNPACK_EXPLICIT_OBJECT", // VA 00C15C2C
    "WAKE_AUTO_PICKUP", // VA 00C15C4C
    "TOGGLE_NO_AUTO_ACQUIRE", // VA 00C15C60
    "MONSTERDOCK", // VA 00C15C78
    "REVIVE", // VA 00C15C84
    "TOGGLE_WEAPONSET", // VA 00C15C8C
    "TOGGLE_GATE", // VA 00C15CA0
    "OPEN_GATE", // VA 00C15CAC
    "CLOSE_GATE", // VA 00C15CB8
    "CREW_EVACUATE", // VA 00C15CC4
    "SPECIAL_POWER_TOGGLE", // VA 00C15CD4
    "HORDE_TOGGLE_FORMATION", // VA 00C15CEC
    "TOGGLE_WEAPON", // VA 00C15D04
    "CASTLE_PACK", // VA 00C15D14
    "CASTLE_UNPACK", // VA 00C15D20
    "SPECIAL_POWER_FROM_COMMAND_CENTER", // VA 00C15D30
    "CONVERT_TO_CARBOMB", // VA 00C15D54
    "HIJACK_VEHICLE", // VA 00C15D68
    "AUTOCAST_WEAPON", // VA 00C15D78
    "SWITCH_WEAPON", // VA 00C15D88
    "COMBATDROP", // VA 00C15D98
    "PURCHASE_SCIENCE", // VA 00C15DA4
    "SPECIAL_POWER", // VA 00C15DB8
    "FIRE_WEAPON", // VA 00C15DC8
    "SET_RALLY_POINT", // VA 00C15DD4
    "BEACON_DELETE", // VA 00C15DE4
    "EXECUTE_UNUSED_01", // VA 00C15DF4
    "EVACUATE_CONTESTED", // VA 00C15E08
    "EVACUATE", // VA 00C15E1C
    "EXIT_CONTAINER", // VA 00C15E28
    "WAYPOINTS", // VA 00C15E38
    "GUARD_FLYING_UNITS_ONLY", // VA 00C15E44
    "GUARD_WITHOUT_PURSUIT", // VA 00C15E5C
    "GUARD", // VA 00C15E74
    "ATTACK_MOVE", // VA 00C15E7C
    "CANCEL_UPGRADE", // VA 00C15E88
    "CASTLE_UPGRADE", // VA 00C15E98
    "OBJECT_UPGRADE", // VA 00C15EA8
    "CANCEL_UNIT_BUILD", // VA 00C15EB8
    "SECONDARY_UNIT_BUILD", // VA 00C15ECC
    "UNIT_BUILD", // VA 00C15EE4
    "FOUNDATION_CONSTRUCT_CANCEL", // VA 00C15EF0
    "FOUNDATION_CONSTRUCT", // VA 00C15F0C
};
extern "C" const char BfmeParticleBoneNone[];
extern const char gCommandNamePlayerUpgrade[] = "PLAYER_UPGRADE";
extern const char gCommandNameStop[] = "STOP";
extern const char gCommandNameSell[] = "SELL";
extern const char gCommandNamePlaceBeacon[] = "PLACE_BEACON";
extern const char gCommandNameSpellBook[] = "SPELL_BOOK";
extern const char gCommandNameOneRing[] = "ONE_RING";
extern const char gCommandNameBloodthirsty[] = "BLOODTHIRSTY";
const char *TheCommandNames[] = {
    BfmeParticleBoneNone,
    gCommandNameVocabularyText.FOUNDATION_CONSTRUCT,
    gCommandNameVocabularyText.FOUNDATION_CONSTRUCT_CANCEL,
    gCommandNameVocabularyText.UNIT_BUILD,
    gCommandNameVocabularyText.SECONDARY_UNIT_BUILD,
    gCommandNameVocabularyText.CANCEL_UNIT_BUILD,
    gCommandNamePlayerUpgrade,
    gCommandNameVocabularyText.OBJECT_UPGRADE,
    gCommandNameVocabularyText.CASTLE_UPGRADE,
    gCommandNameVocabularyText.CANCEL_UPGRADE,
    gCommandNameVocabularyText.ATTACK_MOVE,
    gCommandNameVocabularyText.GUARD,
    gCommandNameVocabularyText.GUARD_WITHOUT_PURSUIT,
    gCommandNameVocabularyText.GUARD_FLYING_UNITS_ONLY,
    gCommandNameStop,
    gCommandNameVocabularyText.WAYPOINTS,
    gCommandNameVocabularyText.EXIT_CONTAINER,
    gCommandNameVocabularyText.EVACUATE,
    gCommandNameVocabularyText.EVACUATE_CONTESTED,
    gCommandNameVocabularyText.EXECUTE_UNUSED_01,
    gCommandNameVocabularyText.BEACON_DELETE,
    gCommandNameVocabularyText.SET_RALLY_POINT,
    gCommandNameSell,
    gCommandNameVocabularyText.FIRE_WEAPON,
    gCommandNameVocabularyText.SPECIAL_POWER,
    gCommandNameVocabularyText.PURCHASE_SCIENCE,
    gCommandNameVocabularyText.COMBATDROP,
    gCommandNameVocabularyText.SWITCH_WEAPON,
    gCommandNameVocabularyText.AUTOCAST_WEAPON,
    gCommandNameVocabularyText.HIJACK_VEHICLE,
    gCommandNameVocabularyText.CONVERT_TO_CARBOMB,
    gCommandNamePlaceBeacon,
    gCommandNameVocabularyText.SPECIAL_POWER_FROM_COMMAND_CENTER,
    gCommandNameVocabularyText.CASTLE_UNPACK,
    gCommandNameVocabularyText.CASTLE_PACK,
    gCommandNameVocabularyText.TOGGLE_WEAPON,
    gCommandNameVocabularyText.HORDE_TOGGLE_FORMATION,
    gCommandNameVocabularyText.SPECIAL_POWER_TOGGLE,
    gCommandNameSpellBook,
    gCommandNameOneRing,
    gCommandNameVocabularyText.CREW_EVACUATE,
    gCommandNameBloodthirsty,
    gCommandNameVocabularyText.CLOSE_GATE,
    gCommandNameVocabularyText.OPEN_GATE,
    gCommandNameVocabularyText.TOGGLE_GATE,
    gCommandNameVocabularyText.TOGGLE_WEAPONSET,
    gCommandNameVocabularyText.REVIVE,
    gCommandNameVocabularyText.MONSTERDOCK,
    gCommandNameVocabularyText.TOGGLE_NO_AUTO_ACQUIRE,
    gCommandNameVocabularyText.WAKE_AUTO_PICKUP,
    gCommandNameVocabularyText.CASTLE_UNPACK_EXPLICIT_OBJECT,
    gCommandNameVocabularyText.START_SELF_REPAIR,
    gCommandNameVocabularyText.HORDE_SET_FORMATION,
    gCommandNameVocabularyText.DOZER_CONSTRUCT,
    gCommandNameVocabularyText.DOZER_CONSTRUCT_CANCEL,
    gCommandNameVocabularyText.PUSH_VISIBLE_COMMAND_RANGE,
    gCommandNameVocabularyText.POP_VISIBLE_COMMAND_RANGE,
    gCommandNameVocabularyText.TOGGLE_STANCE,
    gCommandNameVocabularyText.SET_STANCE,
    gCommandNameVocabularyText.START_NEIGHBORHOOD_REPAIR,
    gCommandNameVocabularyText.CANCEL_NEIGHBORHOOD,
    0,
};


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	static void parseCommand(INI *, void *, void *, const void *);
};

// ?parseCommand@CommandButton@@SAXPAVINI@@PAX1PBX@Z
void CommandButton::parseCommand(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();

	Int index = 0;
	while (TheCommandNames[index])
	{
		if (_strcmpi(TheCommandNames[index], token) == 0)
		{
			*(Int *)store = index;
			return;
		}
		++index;
	}

	throw INIException(3, "Command '%s' not found", token);
}
