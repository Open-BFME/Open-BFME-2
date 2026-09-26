// ??0BattlePlanUpdateModuleData@@QAE@XZ
// partial score=0.95 date=2026-09-26
// cl: /O1 /arch:SSE /DNDEBUG /MD

// ??0BattlePlanUpdateModuleData@@QAE@XZ at retail 0x0049780A (153 bytes).
// The module-data half of BattlePlanUpdate. StealthDetectorUpdateModuleDataCtor
// precedent: a real virtual class (compiler vtable store at +0 first, reloc
// filled from retail's 0x00C4FB00 by the gate; declared-only dtor so no dtor
// row is owed), a short scalar init-list, inline-ctor AsciiString members for
// the name slots (zero stores inline, no calls), and the two 0x1C KindOf
// masks at +0x54/+0x70 constructed implicitly through the shared memset
// helper at 0x24C7B3 (rowed, resolves direct). Retail keeps one zero (+0x50)
// between the first lea and its call, exactly like StealthDetector's +0x2C.
// Field identity is retail's own INI table at 0x00C4FF58 joined to the BFME1
// BattlePlanUpdate donor. The body holds the trailing strategy-center
// scalars: three 1.0f reals, the detects-stealth flag, max-health scalar,
// max-health-change-type and the vision name.
// SCORE 0.95 (146/153): prologue, all 19 zeros, both member calls and the
// float/bool/int tail stores are byte-exact; sole wall is the scheduler
// sinking the +0xA4 zero (mov [esi+0xA4],edi) plus pop edi to right after the
// 1.0f load instead of keeping them at the end. Refuted: init-list vision,
// volatile barrier (byte-identical, still sinks), /EHsc on/off, /G6,
// pointer-members (revives the lea hoist), explicit member inits.
class AsciiString
{
public:
	AsciiString() : m_data(0) {}

private:
	void *m_data;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

	unsigned char m_data[0x1C];
};

class BattlePlanUpdateModuleData
{
public:
	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();

private:
	unsigned int m_unused04;						// +0x04 retail never stores
	const void *m_specialPowerTemplate;				// +0x08
	unsigned int m_bombardmentPlanAnimationFrames;	// +0x0C
	unsigned int m_holdTheLinePlanAnimationFrames;	// +0x10
	unsigned int m_searchAndDestroyPlanAnimationFrames; // +0x14
	unsigned int m_transitionIdleFrames;			// +0x18
	AsciiString m_bombardmentUnpackName;			// +0x1C
	AsciiString m_bombardmentPackName;				// +0x20
	AsciiString m_bombardmentMessageLabel;			// +0x24
	AsciiString m_bombardmentAnnouncementName;		// +0x28
	AsciiString m_searchAndDestroyUnpackName;		// +0x2C
	AsciiString m_searchAndDestroyIdleName;			// +0x30
	AsciiString m_searchAndDestroyPackName;			// +0x34
	AsciiString m_searchAndDestroyMessageLabel;		// +0x38
	AsciiString m_searchAndDestroyAnnouncementName;	// +0x3C
	AsciiString m_holdTheLineUnpackName;			// +0x40
	AsciiString m_holdTheLinePackName;				// +0x44
	AsciiString m_holdTheLineMessageLabel;			// +0x48
	AsciiString m_holdTheLineAnnouncementName;		// +0x4C
	unsigned int m_battlePlanParalyzeFrames;		// +0x50
	Rva0024C7B3Member m_validMemberKindOf;			// +0x54
	Rva0024C7B3Member m_invalidMemberKindOf;		// +0x70
	float m_holdTheLineArmorDamageScalar;			// +0x8C
	float m_searchAndDestroySightRangeScalar;		// +0x90
	float m_strategyCenterSearchAndDestroySightRangeScalar; // +0x94
	bool m_strategyCenterSearchAndDestroyDetectsStealth; // +0x98
	float m_strategyCenterHoldTheLineMaxHealthScalar; // +0x9C
	int m_strategyCenterHoldTheLineMaxHealthChangeType; // +0xA0 (PRESERVE_RATIO == 1)
	const char *m_visionObjectName;					// +0xA4
};

BattlePlanUpdateModuleData::BattlePlanUpdateModuleData()
	: m_specialPowerTemplate( 0 )
	, m_bombardmentPlanAnimationFrames( 0 )
	, m_holdTheLinePlanAnimationFrames( 0 )
	, m_searchAndDestroyPlanAnimationFrames( 0 )
	, m_transitionIdleFrames( 0 )
	, m_battlePlanParalyzeFrames( 0 )
{
	m_holdTheLineArmorDamageScalar = 1.0f;
	m_searchAndDestroySightRangeScalar = 1.0f;
	m_strategyCenterSearchAndDestroySightRangeScalar = 1.0f;
	m_strategyCenterSearchAndDestroyDetectsStealth = true;
	m_strategyCenterHoldTheLineMaxHealthScalar = 1.0f;
	m_strategyCenterHoldTheLineMaxHealthChangeType = 1;
	m_visionObjectName = 0;
}
