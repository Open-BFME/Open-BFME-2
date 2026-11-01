// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX -Ireference/open-bfme-1/game/GameEngine/Source/Common /ICode/GameEngine/Include /I. /Ireference/shims/bfme2_ascii
//
// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E237, 84 bytes. Dedicated TU: the factory news 0xA8, runs the
// declared-only ctor (pinned at 0x49780A, donor-backed BattlePlanUpdate body
// banked as a 0.88 partial against MSVC7.1 scheduling walls), then feeds the
// new data plus the class parse proc (present-unmatched at 0x49861A, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0xA4 pad). Recipe:
// BoredUpdateModuleDataFriendNew.cpp. Class identity is the BFME1
// BattlePlanUpdate donor (BattlePlanUpdate.cpp ctor plus 30-field table at
// 0x00C4FF58) in the BattlePlanUpdate file-unit. The same-named proc row at
// 0x4CBBB4 covers a single SoundUpgrade field and is left for fleet consensus.
// stlport
#include "Common/BfmeAudioEventPrefix136.h"

class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	static void parseAudioEventRTS(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseSpecialPowerTemplate(INI *ini, void *instance, void *store, const void *userData);
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class ModuleData;
class INI;
class MultiIniFieldParse;
class SpecialPowerTemplate;
enum MaxHealthChangeType { MAX_HEALTH_TYPE_DUMMY=0 };

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

struct BattlePlanUpdateModuleData
{
public:
	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

public:
	unsigned int m_unused04;						// +0x04 retail never stores
	const SpecialPowerTemplate *m_specialPowerTemplate;				// +0x08
	unsigned int m_bombardmentPlanAnimationFrames;	// +0x0C
	unsigned int m_holdTheLinePlanAnimationFrames;	// +0x10
	unsigned int m_searchAndDestroyPlanAnimationFrames; // +0x14
	unsigned int m_transitionIdleFrames;			// +0x18
	OpaqueRefElement4 m_bombardmentUnpackName;			// +0x1C
	OpaqueRefElement4 m_bombardmentPackName;				// +0x20
	AsciiString m_bombardmentMessageLabel;			// +0x24
	OpaqueRefElement4 m_bombardmentAnnouncementName;		// +0x28
	OpaqueRefElement4 m_searchAndDestroyUnpackName;		// +0x2C
	OpaqueRefElement4 m_searchAndDestroyIdleName;			// +0x30
	OpaqueRefElement4 m_searchAndDestroyPackName;			// +0x34
	AsciiString m_searchAndDestroyMessageLabel;		// +0x38
	OpaqueRefElement4 m_searchAndDestroyAnnouncementName;	// +0x3C
	OpaqueRefElement4 m_holdTheLineUnpackName;			// +0x40
	OpaqueRefElement4 m_holdTheLinePackName;				// +0x44
	AsciiString m_holdTheLineMessageLabel;			// +0x48
	OpaqueRefElement4 m_holdTheLineAnnouncementName;		// +0x4C
	unsigned int m_battlePlanParalyzeFrames;		// +0x50
	Rva0024C7B3Member m_validMemberKindOf;			// +0x54
	Rva0024C7B3Member m_invalidMemberKindOf;		// +0x70
	float m_holdTheLineArmorDamageScalar;			// +0x8C
	float m_searchAndDestroySightRangeScalar;		// +0x90
	float m_strategyCenterSearchAndDestroySightRangeScalar; // +0x94
	bool m_strategyCenterSearchAndDestroyDetectsStealth; // +0x98
	float m_strategyCenterHoldTheLineMaxHealthScalar; // +0x9C
	MaxHealthChangeType m_strategyCenterHoldTheLineMaxHealthChangeType; // +0xA0 (PRESERVE_RATIO == 1)
	AsciiString m_visionObjectName;					// +0xA4
};

// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BattlePlanUpdateModuleData::friend_newModuleData(INI *ini)
{
	BattlePlanUpdateModuleData *data = new BattlePlanUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BattlePlanUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};
extern const FieldParse g_battlePlanUpdateFieldParseTable[];

void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);

// Zero Hour's BodyModule.h TheMaxHealthChangeTypeNames, a per-unit static
// list with no terminator (retail's copy here: .data 0x00DCB3FC, three names
// followed directly by the next list).
static const char *TheMaxHealthChangeTypeNames[] =
{
	"SAME_CURRENTHEALTH", "PRESERVE_RATIO", "ADD_CURRENT_HEALTH_TOO"
};

// The BattlePlanUpdate module data field table (.rdata 0x00C4FF58, 28
// entries read from retail); no unit defined it, so its only user does.
extern const FieldParse g_battlePlanUpdateFieldParseTable[] =
{
	{ "SpecialPowerTemplate", INI::parseSpecialPowerTemplate, 0, 0x8 },
	{ "BombardmentPlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0xC },
	{ "HoldTheLinePlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "SearchAndDestroyPlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "TransitionIdleTime", INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "BombardmentPlanUnpackSoundName", INI::parseAudioEventRTS, 0, 0x1C },
	{ "BombardmentPlanPackSoundName", INI::parseAudioEventRTS, 0, 0x20 },
	{ "BombardmentMessageLabel", INI::parseAsciiString, 0, 0x24 },
	{ "BombardmentAnnouncementName", INI::parseAudioEventRTS, 0, 0x28 },
	{ "SearchAndDestroyPlanUnpackSoundName", INI::parseAudioEventRTS, 0, 0x2C },
	{ "SearchAndDestroyPlanIdleLoopSoundName", INI::parseAudioEventRTS, 0, 0x30 },
	{ "SearchAndDestroyPlanPackSoundName", INI::parseAudioEventRTS, 0, 0x34 },
	{ "SearchAndDestroyMessageLabel", INI::parseAsciiString, 0, 0x38 },
	{ "SearchAndDestroyAnnouncementName", INI::parseAudioEventRTS, 0, 0x3C },
	{ "HoldTheLinePlanUnpackSoundName", INI::parseAudioEventRTS, 0, 0x40 },
	{ "HoldTheLinePlanPackSoundName", INI::parseAudioEventRTS, 0, 0x44 },
	{ "HoldTheLineMessageLabel", INI::parseAsciiString, 0, 0x48 },
	{ "HoldTheLineAnnouncementName", INI::parseAudioEventRTS, 0, 0x4C },
	{ "ValidMemberKindOf", Rva002567EAParse, 0, 0x54 },
	{ "InvalidMemberKindOf", Rva002567EAParse, 0, 0x70 },
	{ "BattlePlanChangeParalyzeTime", INI::parseDurationUnsignedInt, 0, 0x50 },
	{ "HoldTheLinePlanArmorDamageScalar", INI::parseReal, 0, 0x8C },
	{ "SearchAndDestroyPlanSightRangeScalar", INI::parseReal, 0, 0x90 },
	{ "StrategyCenterSearchAndDestroySightRangeScalar", INI::parseReal, 0, 0x94 },
	{ "StrategyCenterSearchAndDestroyDetectsStealth", INI::parseBool, 0, 0x98 },
	{ "StrategyCenterHoldTheLineMaxHealthScalar", INI::parseReal, 0, 0x9C },
	{ "StrategyCenterHoldTheLineMaxHealthChangeType", INI::parseIndexList, TheMaxHealthChangeTypeNames, 0xA0 },
	{ "VisionObjectName", INI::parseAsciiString, 0, 0xA4 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *f, unsigned int extraOffset);
};

// ?buildFieldParse@BattlePlanUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0049861A (17B)
void __declspec(noinline) BattlePlanUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_battlePlanUpdateFieldParseTable, 0);
}

