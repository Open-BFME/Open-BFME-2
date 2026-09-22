// cl: /O1 /MD /DNDEBUG /arch:SSE
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
class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class SlavedUpdateModuleData
{
public:
	SlavedUpdateModuleData();
	virtual ~SlavedUpdateModuleData();

	int m_unused04;
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
	bool m_bfme55;
	float m_bfme58;
	float m_bfme5C;
	float m_bfme60;
	int m_bfme64;
	int m_bfme68;
	bool m_bfme6C;
	bool m_bfme6D;
};

SlavedUpdateModuleData::SlavedUpdateModuleData()
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
	, m_bfme55(false)
	, m_bfme58(0.0f)
	, m_bfme5C(0.0f)
	, m_bfme60(0.0f)
	, m_bfme64(0)
	, m_bfme68(0)
	, m_bfme6C(true)
	, m_bfme6D(false)
{
}
