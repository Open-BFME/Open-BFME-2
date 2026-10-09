// cl: /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ??0TeamTemplateInfo@@QAE@PAVDict@@@Z @0x003A26E6 399B
// Donor TeamTemplateInfo constructor and current target loader/dtor establish
// Snapshot base; float member initializer preserves canonical Coord3D layout.
// evidence: vtable 0x00C1AE70 TeamTemplateInfo plus loadFromDict 0x0039FEBB plus 7x0x18 records plus 32 scripts plus counters plus 0.5f plus Dict arg
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Common/Snapshot.h"
struct TeamHomeLocation : Coord3D { TeamHomeLocation() { x=0.0f; y=0.0f; z=0.0f; } };

class Dict;
class Rva0039EA9C
{
public:
	Rva0039EA9C();
	~Rva0039EA9C();
private:
	int m_00;
	int m_04;
	int m_08;
	AsciiString m_0c;
	AsciiString m_10;
	int m_14;
};
class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();
private:
	unsigned char m_data[0x1C];
};
enum AttitudeType { AI_NORMAL = 0 };
enum VeterancyLevel { LEVEL_REGULAR = 0 };
enum { MAX_GENERIC_SCRIPTS = 32 };
class TeamTemplateInfo : public Snapshot
{
public:
	TeamTemplateInfo(Dict *dict);
	virtual ~TeamTemplateInfo();
	void loadFromDict(Dict *dict);
protected: virtual void crc(Xfer*); virtual void xfer(Xfer*); virtual void loadPostProcess();
public:
	Rva0039EA9C m_unitsInfo[7];
	int m_numUnitsInfo;
	TeamHomeLocation m_homeLocation;
	bool m_hasHomeLocation;
	AsciiString m_scriptOnCreate;
	AsciiString m_teamEventsList;
	AsciiString m_scriptOnIdle;
	int m_initialIdleFrames;
	AsciiString m_scriptOnEnemySighted;
	AsciiString m_scriptOnAllClear;
	AsciiString m_scriptOnUnitDestroyed;
	AsciiString m_scriptOnDestroyed;
	float m_destroyedThreshold;
	bool m_isAIRecruitable;
	bool m_isBaseDefense;
	bool m_isPerimeterDefense;
	bool m_automaticallyReinforce;
	bool m_transportsReturn;
	bool m_avoidThreats;
	bool m_attackCommonTarget;
	int m_maxInstances;
	int m_productionPriority;
	int m_productionPrioritySuccessIncrease;
	int m_productionPriorityFailureDecrease;
	AttitudeType m_initialTeamAttitude;
	AsciiString m_transportUnitType;
	AsciiString m_startReinforceWaypoint;
	bool m_teamStartsFull;
	bool m_transportsExit;
	VeterancyLevel m_veterancy;
	AsciiString m_productionCondition;
	bool m_executeActions;
	AsciiString m_teamGenericScripts[MAX_GENERIC_SCRIPTS];
	int m_unknown198;
	int m_teamType;
	int m_unknown1A0;
	int m_unknown1A4;
	int m_unknown1A8;
	int m_unknown1AC;
	int m_unknown1B0;
	Rva0024C7B3Member m_counters1B4;
	Rva0024C7B3Member m_counters1D0;
};
TeamTemplateInfo::TeamTemplateInfo(Dict *dict)
	: m_numUnitsInfo(0)
	, m_homeLocation()
	, m_hasHomeLocation(false)
	, m_initialIdleFrames(0)
	, m_destroyedThreshold(0.5f)
	, m_isAIRecruitable(false)
	, m_isBaseDefense(false)
	, m_isPerimeterDefense(false)
	, m_automaticallyReinforce(false)
	, m_transportsReturn(false)
	, m_avoidThreats(false)
	, m_attackCommonTarget(false)
	, m_maxInstances(1)
	, m_productionPriority(0)
	, m_productionPrioritySuccessIncrease(0)
	, m_productionPriorityFailureDecrease(0)
	, m_initialTeamAttitude(AI_NORMAL)
	, m_teamStartsFull(false)
	, m_transportsExit(false)
	, m_veterancy(LEVEL_REGULAR)
	, m_executeActions(false)
	, m_unknown198(-1)
	, m_teamType(0)
	, m_unknown1A0(-1)
	, m_unknown1A4(-1)
	, m_unknown1A8(1)
	, m_unknown1AC(-1)
	, m_unknown1B0(0)
{
	loadFromDict(dict);
}
