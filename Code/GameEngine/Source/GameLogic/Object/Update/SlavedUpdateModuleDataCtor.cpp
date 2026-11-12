// cl: /Ireference/shims/bfme2_ascii /O1 /MD /DNDEBUG /arch:SSE
//
// ??0SlavedUpdateModuleData@@QAE@XZ, retail 0x002552D7, 105 bytes
// (frameless): compiler vtable store at +0 (pinned ??_7 at 0xBF34C0, slot0
// is the ??_G at 0x255FA5), then the ZH SlavedUpdate ranges in retail order
// with BFME2 deltas (LeashRange at +8 leads; GuardWanderRange at +0x10 and
// RepairRange at +0x28 are left unstored; WeldingSys/FXBone at +0x4C/+0x50
// are inline-ctor AsciiStrings; unknown BFME2 extras at +0x55/+0x58..0x6D
// ride as bfme-named members). The owning factory at 0x00255340 (news 0x70)
// is the sole caller; the pool key at 0x4A1875 names the class. Row
// supersedes the ctor pin.
#include "ascii_string.h"

// Retail's table holds ModuleData's 30 inherited slots after the deleting destructor.
#include "../../../../Include/Common/ModuleData.h"

class SlavedUpdateModuleData : public ModuleData
{
public:
	SlavedUpdateModuleData();
	virtual ~SlavedUpdateModuleData();

	// +0x04 is ModuleData's tag.
	int m_leashRange;
	int m_guardMaxRange;
	int m_guardWanderRange;
	int m_attackRange;
	int m_attackWanderRange;
	int m_scoutRange;
	int m_scoutWanderRange;
	int m_distToTargetToGrantRangeBonus;
	int m_repairRange;
	float m_repairMinAltitude;
	float m_repairMaxAltitude;
	float m_repairRatePerSecond;
	int m_repairWhenHealthBelowPercentage;
	int m_minReadyFrames;
	int m_maxReadyFrames;
	int m_minWeldFrames;
	int m_maxWeldFrames;
	AsciiString m_weldingSysName;
	AsciiString m_weldingFXBone;
	bool m_stayOnSameLayerAsMaster;
	bool m_dieOnMastersDeath;
	float m_guardPositionOffset;
	float m_bfme5C;
	float m_bfme60;
	int m_fadeOutRange;
	int m_fadeTime;
	bool m_markUnselectable;
	bool m_useSlaverAsControlForEvaObjectSightedEvents;
};

inline SlavedUpdateModuleData::SlavedUpdateModuleData()
	: m_leashRange(0)
	, m_guardMaxRange(0)
	, m_attackRange(0)
	, m_attackWanderRange(0)
	, m_scoutRange(0)
	, m_scoutWanderRange(0)
	, m_distToTargetToGrantRangeBonus(0)
	, m_repairMinAltitude(0.0f)
	, m_repairMaxAltitude(0.0f)
	, m_repairRatePerSecond(0.0f)
	, m_repairWhenHealthBelowPercentage(0)
	, m_minReadyFrames(0)
	, m_maxReadyFrames(0)
	, m_minWeldFrames(0)
	, m_maxWeldFrames(0)
	, m_stayOnSameLayerAsMaster(false)
	, m_dieOnMastersDeath(false)
	, m_guardPositionOffset(0.0f)
	, m_bfme5C(0.0f)
	, m_bfme60(0.0f)
	, m_fadeOutRange(0)
	, m_fadeTime(0)
	, m_markUnselectable(true)
	, m_useSlaverAsControlForEvaObjectSightedEvents(false)
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeSlavedUpdateModuleDataInlineAnchor@@YAXPAVSlavedUpdateModuleData@@@Z absent-from-retail
void _bfmeSlavedUpdateModuleDataInlineAnchor(SlavedUpdateModuleData *slavedUpdateModuleData)
{
    slavedUpdateModuleData->SlavedUpdateModuleData::SlavedUpdateModuleData();
}
#pragma inline_depth()
