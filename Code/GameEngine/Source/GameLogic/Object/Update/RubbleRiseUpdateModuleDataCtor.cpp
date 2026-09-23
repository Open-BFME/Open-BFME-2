// cl: /O1 /GX /MD /DNDEBUG /arch:SSE
//
// ??0RubbleRiseUpdateModuleData@@QAE@XZ, retail 0x00256653 (163 bytes).
// RubbleRise ModuleData default ctor: trivial virtual base (vptr 0x00BF3B40
// installs automatically) plus DieMuxData member at +0x08 built through the
// rowed 0x004CE534 body (spelled here as its default ctor via the alias pin;
// StructureCollapse precedent), two four-element 0xC member arrays (OCL/FX
// vectors at +0x58/+0x88) built through the rowed ehvec iterator at
// 0x00629512 (opaque element ctor/dtor keep the frame while the element
// addresses stay DIR32 slots the patcher copies from retail), the scalar
// cadence from the rowed parse table 0x00C52960 (min/max rise 0, min burst
// 9999, big burst 0, damping/height/shudder 0.0; max burst is INI-only so
// never stored), and the count loop (ocl/fx counts at +0xB8/+0xC8 set to 1,
// which /O1 merges into the paired store with the pushed-4/pop-edx bound).
// Size 0xD8 matches the rowed factory 0x002566F6.

class DieMuxData
{
public:
	DieMuxData();

private:
	unsigned char m_bytes[0x30];
};

class RubbleOCLVec
{
public:
	RubbleOCLVec();
	~RubbleOCLVec();

private:
	unsigned char m_data[0x0C];
};

class RubbleFXVec
{
public:
	RubbleFXVec();
	~RubbleFXVec();

private:
	unsigned char m_data[0x0C];
};

class RubbleRiseBase
{
public:
	virtual ~RubbleRiseBase();

private:
	unsigned char m_pad04[4];
};

enum
{
	RUBBLE_PHASE_COUNT = 4,
};

class RubbleRiseUpdateModuleData : public RubbleRiseBase
{
public:
	RubbleRiseUpdateModuleData();
	virtual ~RubbleRiseUpdateModuleData();

private:
	DieMuxData m_dieMuxData; // +0x08
	int m_minRubbleRiseDelay; // +0x38
	int m_maxRubbleRiseDelay; // +0x3C
	int m_minBurstDelay; // +0x40
	int m_maxBurstDelay; // +0x44, INI-only, never stored here
	int m_bigBurstFrequency; // +0x48
	float m_rubbleRiseDamping; // +0x4C
	float m_rubbleHeight; // +0x50
	float m_maxShudder; // +0x54
	RubbleOCLVec m_ocls[RUBBLE_PHASE_COUNT]; // +0x58
	RubbleFXVec m_fxs[RUBBLE_PHASE_COUNT]; // +0x88
	unsigned int m_oclCount[RUBBLE_PHASE_COUNT]; // +0xB8
	unsigned int m_fxCount[RUBBLE_PHASE_COUNT]; // +0xC8
};

// ??0RubbleRiseUpdateModuleData@@QAE@XZ @0x256653
RubbleRiseUpdateModuleData::RubbleRiseUpdateModuleData()
{
	m_minRubbleRiseDelay = 0;
	m_maxRubbleRiseDelay = 0;
	m_minBurstDelay = 9999;
	m_maxShudder = 0.0f;
	m_rubbleRiseDamping = 0.0f;
	m_bigBurstFrequency = 0;
	m_rubbleHeight = 0.0f;
	for (int i = 0; i < RUBBLE_PHASE_COUNT; ++i)
	{
		m_oclCount[i] = 1;
		m_fxCount[i] = 1;
	}
}
