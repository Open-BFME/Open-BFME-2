// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// INI::parseMiscAudio @0x001ED6EE (30B): Zero Hour INIMiscAudio.cpp's
// body. Identity from the INI block table: the "MiscAudio" token's entry
// names this address. TheAudio's friend_getMiscAudio is virtual in BFME 2
// (vtable slot +0x13C) where ZH had it non-virtual; the block fills it from
// MiscAudio's field-parse table 0x00BDF2D0.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

#include "../../../Include/Common/INI/INI.h"

struct MiscAudio
{
	static const FieldParse m_fieldParseTable[];
};
extern "C" {
void __identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x007DF2D0: 61 entries and the null terminator; every parser is a rowed code owner.
const FieldParse MiscAudio::m_fieldParseTable[62] = {
	{ "RadarNotifyHarvesterUnderAttackSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "RadarNotifyStructureUnderAttackSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "RadarNotifyInfiltrationSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "RadarNotifyOnlineSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "RadarNotifyOfflineSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "GenericRadarEvent", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "BeaconPlacedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "BeaconPlacementFailed", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "DefectorTimerTickSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "DefectorTimerDingSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "AllCheerSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "NoCanDoSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
	{ "StealthDiscoveredSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "StealthNeutralizedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "MoneyDepositSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "MoneyWithdrawSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "BuildingDisabled", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
	{ "BuildingReenabled", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x44 },
	{ "VehicleDisabled", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "VehicleReenabled", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
	{ "SplatterVehiclePilotsBrain", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
	{ "CrateHeal", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
	{ "CrateShroud", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
	{ "CrateFreeUnit", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5C },
	{ "CrateMoney", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
	{ "UnitPromoted", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
	{ "RepairSparks", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
	{ "EnterCloseCombat", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x6C },
	{ "ExitCloseCombat", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x70 },
	{ "IncomingChatNotification", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x74 },
	{ "PrivateMessageNotification", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x78 },
	{ "BuddyMessageNotification", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x7C },
	{ "EnabledHotKeyPressed", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x80 },
	{ "DisabledHotKeyPressed", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x84 },
	{ "DisabledButtonClicked", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x88 },
	{ "LowLODShellMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8C },
	{ "HighLODShellMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x90 },
	{ "ScoreScreenMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x94 },
	{ "ShellMapLoadMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x98 },
	{ "FullScreenSubMenuMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x9C },
	{ "SaveFileLoadMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
	{ "CreditsMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA4 },
	{ "VolumeSampleMusic", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB0 },
	{ "VolumeSampleSoundFX", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA8 },
	{ "VolumeSampleVoice", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xAC },
	{ "VolumeSampleAmbient", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB4 },
	{ "VolumeSampleMovie", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xB8 },
	{ "MissionBriefingCharacterClick", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xBC },
	{ "ComboBoxClick", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC0 },
	{ "GameSpyCommunicatorOpen", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC4 },
	{ "RIFThingTemplateReloadedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC8 },
	{ "RIFObjectsRefreshedSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xCC },
	{ "FastForwardModeOn", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD0 },
	{ "FastForwardModeOff", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD4 },
	{ "RallyPointSet", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD8 },
	{ "UnableToSetRallyPoint", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xDC },
	{ "PlanningModeOrderGiven", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE0 },
	{ "BuildingPlacementSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE4 },
	{ "BadBuildingPlacementSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE8 },
	{ "WallPlacementSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xEC },
	{ "TargetObjectWithSpecialPowerSound", (FieldParseProc)&__identifier("?parseAudioEventRTS@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xF0 },
	{ 0, 0, 0, 0 }
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void
	v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual
	void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void
	v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual
	void v18(); virtual void v19(); virtual void v20(); virtual void v21();
	virtual void v22(); virtual void v23(); virtual void v24(); virtual void
	v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual
	void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34(); virtual void v35(); virtual void
	v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual
	void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void
	v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual
	void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void
	v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual
	void v62(); virtual void v63(); virtual void v64(); virtual void v65();
	virtual void v66(); virtual void v67(); virtual void v68(); virtual void
	v69(); virtual void v70(); virtual void v71(); virtual void v72(); virtual
	void v73(); virtual void v74(); virtual void v75(); virtual void v76();
	virtual void v77(); virtual void v78();
	virtual MiscAudio *friend_getMiscAudio(void);   // +0x13C
};

extern AudioManager *TheAudio;

void INI::parseMiscAudio(INI *ini)
{
	ini->initFromINI(TheAudio->friend_getMiscAudio(), MiscAudio::m_fieldParseTable);
}
