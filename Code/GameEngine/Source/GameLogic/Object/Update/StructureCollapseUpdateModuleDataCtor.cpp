// cl: /O1 /GX /MD /DNDEBUG /arch:SSE
//
// ??0StructureCollapseUpdateModuleData@@QAE@XZ, retail 0x00256ACC (172 bytes).
// StructureCollapse ModuleData default ctor: trivial virtual base (vptr
// 0x00BF3E30 installs automatically) plus DieMuxData member at +0x08 built
// through the rowed 0x004CE534 body (spelled here as its default ctor via
// an alias pin; Rva00253510 precedent), two five-element 0xC member arrays
// (OCL/FX vectors) built through the rowed ehvec iterator at 0x00629512
// (CrushDie precedent: opaque element ctor/dtor keep the frame while the
// element addresses stay DIR32 slots the patcher copies from retail), the
// scalar cadence from the BFME1 donor (min/max collapse 0, min burst 9999,
// big burst 0, damping/shudder 0.0; max burst is INI-only so never stored),
// and the donor's count loop (ocl/fx counts at +0xCC/+0xE0 set to 1, which
// /O1 merges into the paired store with the pushed-5/pop-edx bound).
// DestroyObjectWhenDone (+0xF4) and CollapseHeight (+0xF8) zero-init per
// the rowed parse table 0x00C52790. Size 0xFC matches the rowed factory.

class DieMuxData
{
public:
	DieMuxData();

private:
	unsigned char m_bytes[0x30];
};

class CollapseOCLVec
{
public:
	CollapseOCLVec();
	~CollapseOCLVec();

private:
	unsigned char m_data[0x0C];
};

class CollapseFXVec
{
public:
	CollapseFXVec();
	~CollapseFXVec();

private:
	unsigned char m_data[0x0C];
};

class StructureCollapseBase
{
public:
	virtual ~StructureCollapseBase();

private:
	unsigned char m_pad04[4];
};

enum
{
	COLLAPSE_PHASE_COUNT = 5,
};

class StructureCollapseUpdateModuleData : public StructureCollapseBase
{
public:
	StructureCollapseUpdateModuleData();
	virtual ~StructureCollapseUpdateModuleData();

private:
	DieMuxData m_dieMuxData; // +0x08
	int m_minCollapseDelay; // +0x38
	int m_maxCollapseDelay; // +0x3C
	int m_minBurstDelay; // +0x40
	int m_maxBurstDelay; // +0x44, INI-only, never stored here
	int m_bigBurstFrequency; // +0x48
	float m_collapseDamping; // +0x4C
	float m_maxShudder; // +0x50
	CollapseOCLVec m_ocls[COLLAPSE_PHASE_COUNT]; // +0x54
	CollapseFXVec m_fxs[COLLAPSE_PHASE_COUNT]; // +0x90
	unsigned int m_oclCount[COLLAPSE_PHASE_COUNT]; // +0xCC
	unsigned int m_fxCount[COLLAPSE_PHASE_COUNT]; // +0xE0
	bool m_destroyObjectWhenDone; // +0xF4
	char m_padF5[3];
	float m_collapseHeight; // +0xF8
};

// ??0StructureCollapseUpdateModuleData@@QAE@XZ @0x256ACC
StructureCollapseUpdateModuleData::StructureCollapseUpdateModuleData()
{
	m_minCollapseDelay = 0;
	m_maxCollapseDelay = 0;
	m_minBurstDelay = 9999;
	m_maxShudder = 0.0f;
	m_collapseDamping = 0.0f;
	m_bigBurstFrequency = 0;
	m_destroyObjectWhenDone = false;
	m_collapseHeight = 0.0f;
	for (int i = 0; i < COLLAPSE_PHASE_COUNT; ++i)
	{
		m_oclCount[i] = 1;
		m_fxCount[i] = 1;
	}
}
