// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?getUiText@Parameter@@QBE?AVAsciiString@@XZ, retail 0x003B4B1D (1954B plus
// the 78-entry jump table that follows it). Callers: Condition::getUiText
// 0x003B5BA4 and ScriptAction::getUiText 0x003B54DC.
//
// Target facts: the parameter type is the first dword (switch limit 0x4D) and
// the layout reads +0x08 int, +0x0C real, +0x10 name (the ScriptConditions
// Parameter view); the case numbers below are read from the retail jump table
// and the format strings from the case bodies. Donor facts: Zero Hour's
// Parameter::getUiText (Scripts.cpp, reference revision in
// Scripts.cpp's draft) gives the statement order, the "???" empty-name
// substitute and the format strings; WorldBuilder's debug copy
// (0x00AAB4D0, Scripts.cpp:3203..3357) names the function. The case names in
// the comments are Zero Hour's; BFME 2 inserts one type at 29 and adds the
// types from 41 on, so the numbers are target facts and the names are
// donor-carried. The `"..???"` literals that end in a trigraph (`??'`, `??)`)
// are the retail bytes `?^` and `?]`.
#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(int bit);	// 0x00306218
};

class Parameter
{
public:
	AsciiString getUiText() const;
	void getCoord3D(Coord3D *pos) const;	// 0x003B27BB

private:
	int m_paramType;
	int m_pad04;
	int m_int;
	float m_real;
	AsciiString m_string;
};

// EmotionNames and the read-only TheStanceNames table have real data owners.
// The other tables below are this TU's copies of the retail contents.
extern const char *EmotionNames[];
extern const char *const TheStanceNames[];

struct BorderColor
{
	const char *m_colorName;
	unsigned int m_color;
};

static const BorderColor BORDER_COLORS[] =
{
	{ "Orange", 0xFFFF8700 },
	{ "Green", 0xFF00FF00 },
	{ "Blue", 0xFF0000FF },
	{ "Cyan", 0xFF00FFFF },
	{ "Magenta", 0xFFFF00FF },
	{ "Yellow", 0xFFFFFF00 },
	{ "Purple", 0xFF9E00FF },
	{ "Pink", 0xFFFF8670 }
};

static const char *BuildableStatusNames[] = { "Yes", "Ignore_Prerequisites", "No", "Only_By_AI" };
static const char *Surfaces[] = { "GROUND", "WATER", "CLIFF", "AIR", "RUBBLE", "OBSTACLE", "IMPASSABLE", "DEEP_WATER", "WALL_RAILING" };
static const char *ShakeIntensities[] = { "Subtle", "Normal", "Strong", "Severe", "Cine_Extreme", "Cine_Insane" };
static const char *SplinePathPadNames[] = { "Closed", "Opened", "Periodic" };

struct RGBBytes
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

AsciiString Parameter::getUiText() const
{
	AsciiString uiText;
	AsciiString uiString = m_string;
	if (uiString.isEmpty())
		uiString = "???";

	Coord3D pos;
	switch (m_paramType)
	{
		default:
			break;
		case 12:	// SOUND
		case 59:
			uiText.format("Sound '%s'", uiString.str());
			break;
		case 2:		// SCRIPT
			uiText.format("Script '%s'", uiString.str());
			break;
		case 13:	// SCRIPT_SUBROUTINE
			uiText.format("Subroutine '%s'", uiString.str());
			break;
		case 28:	// ATTACK_PRIORITY_SET
			uiText.format("Attack priority set '%s'", uiString.str());
			break;
		case 7:		// WAYPOINT
			uiText.format("Waypoint '%s'", uiString.str());
			break;
		case 24:	// WAYPOINT_PATH
			uiText.format("Waypoint Path '%s'", uiString.str());
			break;
		case 64:
			uiText.format("camera animation '%s'", uiString.str());
			break;
		case 51:
			uiText.format("Camera '%s'", uiString.str());
			break;
		case 9:		// TRIGGER_AREA
			uiText.format(" area '%s'", uiString.str());
			break;
		case 39:	// COMMAND_BUTTON
			uiText.format("Command button: '%s'", uiString.str());
			break;
		case 40:	// FONT_NAME
			uiText.format("Font: '%s'", uiString.str());
			break;
		case 25:	// LOCALIZED_TEXT
			uiText.format("Localized String: '%s'", uiString.str());
			break;
		case 10:	// TEXT_STRING
			uiText.format("String: '%s'", uiString.str());
			break;
		case 3:		// TEAM
			uiText.format("Team '%s'", uiString.str());
			break;
		case 55:
			uiText.format("TeamRef '%s'", uiString.str());
			break;
		case 14:	// UNIT
			uiText.format("Unit '%s'", uiString.str());
			break;
		case 54:
			uiText.format("UnitRef '%s'", uiString.str());
			break;
		case 26:	// BRIDGE
			uiText.format("Bridge '%s'", uiString.str());
			break;
		case 17:	// ANGLE
			uiText.format("%.2f degrees", m_real * (180 / 3.14159265f));
			break;
		case 52:	// PERCENT
			uiText.format("%.2f%%", m_real * 100.0f);
			break;
		case 16:	// COORD3D
			getCoord3D(&pos);
			uiText.format("(%.2f,%.2f,%.2f)", pos.x, pos.y, pos.z);
			break;
		case 27:	// KIND_OF_PARAM
			if (m_int >= 0 && m_int < 218)
				uiText.format("Kind is '%s'", KindOfMaskType::getNameFromSingleBit(m_int));
			else
				uiText.format("Kind is '???'");
			break;
		case 11:	// SIDE
			uiText.format("Player '%s'", uiString.str());
			break;
		case 0:		// INT
			uiText.format(" %d ", m_int);
			break;
		case 8:		// BOOLEAN
			uiText += (m_int ? "TRUE" : "FALSE");
			break;
		case 1:		// REAL
			uiText.format("%.2f", m_real);
			break;
		case 19:	// RELATION
			uiText.format("Relation '%s'", uiString.str());
			break;
		case 5:		// FLAG
			uiText.format("Flag named '%s'", uiString.str());
			break;
		case 6:		// COMPARISON
			switch (m_int) {
				case 0: uiText.format("Less Than"); break;
				case 1: uiText.format("Less Than or Equal"); break;
				case 2: uiText.format("Equal To"); break;
				case 3: uiText.format("Greater Than or Equal To"); break;
				case 4: uiText.format("Greater Than"); break;
				case 5: uiText.format("Not Equal To"); break;
			}
			break;
		case 57:
			switch (m_int) {
				case 0: uiText.format("Add"); break;
				case 1: uiText.format("Subtract"); break;
				case 2: uiText.format("Multiply"); break;
				case 3: uiText.format("Divide"); break;
			}
			break;
		case 20:	// AI_MOOD
			switch (m_int) {
				case -3: uiText.format("Peaceful"); break;
				case -2: uiText.format("Sleep"); break;
				case -1: uiText.format("Passive"); break;
				case 0: uiText.format("Normal"); break;
				case 1: uiText.format("Alert"); break;
				case 2: uiText.format("Aggressive"); break;
			}
			break;
		case 56:
			switch (m_int) {
				case 0: uiText.format("near"); break;
				case 1: uiText.format("far"); break;
			}
			break;
		case 30:	// RADAR_EVENT_TYPE
			switch (m_int) {
				case 0: uiText.format("Information"); break;
				case 1: uiText.format("Construction"); break;
				case 2: uiText.format("Upgrade"); break;
				case 3: uiText.format("Under Attack"); break;
				case 4: uiText.format("Infiltration"); break;
				case 5: uiText.format("Banner"); break;
			}
			break;
		case 44:	// COLOR
			uiText.format(" R:%d G:%d B:%d ", (m_int&0x00ff0000)>>16, (m_int&0x0000ff00)>>8, (m_int&0x000000ff) );
			break;
		case 31:	// SPECIAL_POWER
			uiText.format("Special power '%s'", uiString.str());
			break;
		case 32:	// SCIENCE
			uiText.format("Science '%s'", uiString.str());
			break;
		case 50:	// SCIENCE_AVAILABILITY
			uiText.format("Science availability '%s'", uiString.str());
			break;
		case 33:	// UPGRADE
			uiText.format("Upgrade '%s'", uiString.str());
			break;
		case 34:	// COMMANDBUTTON_ABILITY
		case 42:	// COMMANDBUTTON_ALL_ABILITIES
			uiText.format("Ability '%s'", uiString.str());
			break;
		case 45:	// EMOTICON
			uiText.format("Emoticon '%s'", uiString.str());
			break;
		case 35:	// BOUNDARY
			uiText.format("Boundary %s", BORDER_COLORS[m_int % 8].m_colorName);
			break;
		case 36:	// BUILDABLE
			if (m_int >= 0 && m_int < 4)
				uiText.format("Buildable (%s)", BuildableStatusNames[m_int]);
			else
				uiText.format("Buildable (???)");
			break;
		case 37:	// SURFACES_ALLOWED
			if (m_int >= 0 && m_int < 9)
				uiText.format("Surfaces Allowed: %s", Surfaces[m_int]);
			else
				uiText.format("Surfaces Allowed: ???");
			break;
		case 38:	// SHAKE_INTENSITY
			if (m_int > 0 && m_int < 6)
				uiText.format("Shake Intensity: %s", ShakeIntensities[m_int]);
			else
				uiText.format("Shake Intensity: ???");
			break;
		case 41:	// OBJECT_STATUS
			if (m_string.isEmpty())
				uiText.format("Object Status is '???'");
			else
				uiText.format("Object Status is '%s'", m_string.str());
			break;
		case 47:	// FACTION_NAME
			uiText.format("Faction Name: %s", uiString.str());
			break;
		case 53:
		{
			const char *name = "???";
			if (m_int > 0 && m_int <= 3)
				name = SplinePathPadNames[m_int - 1];
			uiText.format("Spline Path Pad: %s", name);
			break;
		}
		case 49:	// REVEALNAME
			uiText.format("Reveal Name: %s", uiString.str());
			break;
		case 46:	// OBJECT_PANEL_FLAG
			uiText.format("Object Flag: %s", uiString.str());
			break;
		case 58:
			uiText.format("ModelCondition State: %s", uiString.str());
			break;
		case 60:
			uiText.format("Reverb Room Type: %s", uiString.str());
			break;
		case 63:
			if (m_int >= 0 && m_int < 12)
				uiText.format("Emotion: %s", EmotionNames[m_int]);
			else
				uiText = "Emotion: ???";
			break;
		case 68:
			if (m_int >= 0 && m_int < 6)
				uiText.format("Stance: %s", TheStanceNames[m_int]);
			else
				uiText = "Stance: ???";
			break;
		case 66:
			uiText.format("'%s'", uiString.str());
			break;
		case 67:
			uiText.format("ThreatFinder: %s", uiString.str());
			break;
		case 76:
			uiText.format("EVA Event: %s", uiString.str());
			break;
		case 4:		// COUNTER
		case 15:	// OBJECT_TYPE
		case 18:	// TEAM_STATE
		case 21:	// DIALOG
		case 22:	// MUSIC
		case 23:	// MOVIE
		case 43:	// SKIRMISH_WAYPOINT_PATH
		case 48:	// OBJECT_TYPE_LIST
		case 61:
		case 62:
		case 77:
			uiText.format("'%s'", uiString.str());
			break;
	}
	return uiText;
}
