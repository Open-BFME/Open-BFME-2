// ??0FlammableUpdateModuleData@@QAE@XZ
// partial score=0.93 date=2026-09-26
// cl: /O1 /EHsc /arch:SSE /G7 /DNDEBUG /MD
//
// ??0FlammableUpdateModuleData@@QAE@XZ, retail 0x0048D541, 203 bytes.
// FlammableUpdateModuleData constructor over the own INI table at
// 0x00C4C600 (BurnedDelay at +0x08 through DamageType at +0x24, flags at
// +0x34..+0x3A, waters at +0x3C/+0x40/+0x44, PanicLocomotor at +0x48,
// CustomAnimAndDuration at +0x4C). Layout and member names follow the
// landed FlammableUpdateModuleDataDtor TU: burning-sound holder at +0x18,
// CameraMarker vector at +0x28. The factory at 0x0024D068 news 0x58 and
// calls this constructor.
// The vtable word at +0x00 is an explicit first member (BannerCarrier
// precedent), so no vtable is emitted. The +0x04..+0x14 delay block is the
// BFME1 donor's FlammableUpdateModuleDataBase (m_moduleData plus the four
// delay ints, housed here as a member because the explicit vtable word
// occupies +0x00); its inline constructor zeroes the four delays while the
// module-data word stays untouched, and its declared-only destructor arms
// EH state 0. The holder and vector destructors stay declared-only, giving
// silent unwind levels 1 and 2, so the throwing erase call arms state 2.
// Defaults: flameDamageLimit 20.0f, flameDamageExpiration 5 *
// LogicFramesPerSecond, damageType 6, runToWaterDepth 0.0f,
// searchRadius 200.0f, searchIncrement 60.0f, setBurnedStatus true. The
// vector is built by the rowed 0x00211E58 base and cleared with (begin,
// end) erase; retail duplicates the +0x4C/+0x50/+0x54 stores around the
// erase call and the source keeps both.

#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

struct CameraMarkerVecAlloc
{
	CameraMarkerVecAlloc() {}
};

class CameraMarker;

struct CameraMarkerVec
{
	CameraMarkerVec(const CameraMarkerVecAlloc &) throw();
	~CameraMarkerVec();
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);

	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BurningSoundHolder
{
	~BurningSoundHolder();

	OpaqueRefCounted *m_ptr;
};

struct FlammableUpdateModuleDataBase
{
	FlammableUpdateModuleDataBase()
	{
		m_burnedDelay = 0;
		m_aflameDuration = 0;
		m_aflameDamageDelay = 0;
		m_aflameDamageAmount = 0;
	}
	~FlammableUpdateModuleDataBase();

	int m_moduleData; // +0x04, retail never stores it
	int m_burnedDelay; // +0x08
	int m_aflameDuration; // +0x0C
	int m_aflameDamageDelay; // +0x10
	int m_aflameDamageAmount; // +0x14
};

class FlammableUpdateModuleData
{
public:
	FlammableUpdateModuleData();

private:
	const void *m_vtable; // +0x00, retail 0x00C4C408
	FlammableUpdateModuleDataBase m_delays; // +0x04..+0x14
	BurningSoundHolder m_burningSound; // +0x18
	float m_flameDamageLimit; // +0x1C, 20.0f
	int m_flameDamageExpiration; // +0x20, 5 * LogicFramesPerSecond
	int m_damageType; // +0x24, 6
	CameraMarkerVec m_fireMarkers; // +0x28
	bool m_setBurnedStatus; // +0x34, true
	bool m_swapModelWhenAflame; // +0x35
	bool m_swapModelWhenQuenched; // +0x36
	bool m_swapTextureWhenAflame; // +0x37
	bool m_swapTextureWhenQuenched; // +0x38
	bool m_burnContained; // +0x39
	bool m_runToWater; // +0x3A
	float m_runToWaterDepth; // +0x3C, 0.0f
	float m_runToWaterSearchRadius; // +0x40, 200.0f
	float m_runToWaterSearchIncrement; // +0x44, 60.0f
	bool m_panicLocomotorWhileAflame; // +0x48
	int m_customAnimAndDuration; // +0x4C, -1
	int m_unk50; // +0x50, no INI field
	int m_unk54; // +0x54, no INI field
};

FlammableUpdateModuleData::FlammableUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4C408))
	, m_delays()
	, m_burningSound()
	, m_flameDamageLimit(20.0f)
	, m_flameDamageExpiration(LogicFramesPerSecond * 5)
	, m_damageType(6)
	, m_fireMarkers(CameraMarkerVecAlloc())
{
	m_setBurnedStatus = true;
	m_swapModelWhenAflame = false;
	m_swapModelWhenQuenched = false;
	m_swapTextureWhenAflame = false;
	m_swapTextureWhenQuenched = false;
	m_burnContained = false;
	m_runToWater = false;
	m_runToWaterDepth = 0.0f;
	m_runToWaterSearchRadius = 200.0f;
	m_runToWaterSearchIncrement = 60.0f;
	m_panicLocomotorWhileAflame = false;
	m_customAnimAndDuration = -1;
	m_unk50 = 0;
	m_unk54 = 0;
	m_fireMarkers.erase(m_fireMarkers.m_start, m_fireMarkers.m_finish);
	m_customAnimAndDuration = -1;
	m_unk50 = 0;
	m_unk54 = 0;
}
