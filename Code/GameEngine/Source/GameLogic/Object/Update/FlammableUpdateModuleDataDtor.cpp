// cl: /O1 /GX /DNDEBUG /MD
//
// ??1FlammableUpdateModuleData@@UAE@XZ, retail 0x0048D075, 73 bytes.
// FlammableUpdateModuleData destructor: restores the own vtable 0x00C4C408,
// destroys the CameraMarker vector at +0x28 through the 0x48D003 body
// (pinned below; the rowed _Destroy at 0x48CE25 proves CameraMarker
// elements), releases the +0x18 burning-sound holder through the rowed
// Release_Ref at 0x50ED3 when non-null, then restores the Snapshot base
// vtable 0x00BBB554. The holder's inline dtor keeps Release_Ref
// throw()-declared so it stays EH-untracked; the vector is the only
// tracked member, giving states 1/0 exactly as retail. Shape follows the
// landed LargeGroupBonusUpdateModuleDataDtor (TU-local Snapshot with an
// inline BBB554-restoring dtor, empty derived body). Member names and
// offsets are the own INI table at 0x00C4C600 (BurnedDelay at +0x08
// through DamageType at +0x24, flags at +0x34..+0x3A, waters at
// +0x3C/+0x40/+0x44, PanicLocomotor at +0x48, CustomAnimAndDuration at
// +0x4C); the factory at 0x0024D068 news 0x58 and calls the 0x48D541 ctor.
// The parse proc at 0x739900 allocates the +0x18 holder (new + vtable
// install), which is why the dtor Releases instead of string-teardown.

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

inline Snapshot::~Snapshot()
{
	*(const void **)this = reinterpret_cast<const void *>(0x00BBB554);
}

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BurningSoundHolder
{
	~BurningSoundHolder()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	OpaqueRefCounted *m_ptr;
};

struct CameraMarkerVec
{
	~CameraMarkerVec();

	void *m_start;
	void *m_finish;
	void *m_end;
};

class FlammableUpdateModuleData : public Snapshot
{
public:
	virtual ~FlammableUpdateModuleData();

private:
	int m_unused04; // +0x04, retail never stores it
	int m_burnedDelay; // +0x08
	int m_aflameDuration; // +0x0C
	int m_aflameDamageDelay; // +0x10
	int m_aflameDamageAmount; // +0x14
	BurningSoundHolder m_burningSound; // +0x18
	float m_flameDamageLimit; // +0x1C
	int m_flameDamageExpiration; // +0x20
	int m_damageType; // +0x24
	CameraMarkerVec m_fireMarkers; // +0x28
	bool m_setBurnedStatus; // +0x34
	bool m_swapModelWhenAflame; // +0x35
	bool m_swapModelWhenQuenched; // +0x36
	bool m_swapTextureWhenAflame; // +0x37
	bool m_swapTextureWhenQuenched; // +0x38
	bool m_burnContained; // +0x39
	bool m_runToWater; // +0x3A
	float m_runToWaterDepth; // +0x3C
	float m_runToWaterSearchRadius; // +0x40
	float m_runToWaterSearchIncrement; // +0x44
	bool m_panicLocomotorWhileAflame; // +0x48
	int m_customAnimAndDuration; // +0x4C
	int m_unk50; // +0x50, no INI field
	int m_unk54; // +0x54, no INI field
};

// ??1FlammableUpdateModuleData@@UAE@XZ @0x0048D075
FlammableUpdateModuleData::~FlammableUpdateModuleData()
{
}
