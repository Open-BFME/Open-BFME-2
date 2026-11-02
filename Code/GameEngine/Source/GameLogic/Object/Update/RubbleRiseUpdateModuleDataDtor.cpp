// cl: /GX /MD /DNDEBUG /Ireference/shims/moduledata
//
// ??1RubbleRiseUpdateModuleData@@UAE@XZ, retail 0x00256C5A, 86 bytes.
// Virtual dtor over vtable RVA 0x7F3B40 (VA 0xBF3B40, slot 0 deleting dtor
// at 0x00256C3E). Donor BFME1 RubbleRiseUpdateModuleDataDestructorThunk.cpp
// (dual 4-element 0x0C arrays). Same layout as the rowed ctor TU
// (RubbleRiseUpdateModuleDataCtor.cpp): Snapshot base at +0 (inline BBB554
// restore) and a pad word at +0x04, DieMuxData at +0x08 (trivial dtor), scalars to +0x58,
// OCL/FX 4x0xC arrays at +0x58/+0x88 via ehvec dtor 0x629110 (element
// 0x47fab3 BasicStringCharDtor_dup, count 4 size 0xC, states 1/0), counts
// at +0xB8/+0xC8. Empty body: the two reverse-order ??_M destroys plus the
// base restore are compiler-generated. No base call in retail (inline).
// Size 0xD8 matches the rowed factory 0x002566F6.

#include "Common/Snapshot.h"

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

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

enum
{
	RUBBLE_PHASE_COUNT = 4,
};

class __declspec(novtable) RubbleRiseUpdateModuleData : public Snapshot
{
public:
	virtual ~RubbleRiseUpdateModuleData();

private:
	unsigned int m_unused04; // +0x04
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

RubbleRiseUpdateModuleData::~RubbleRiseUpdateModuleData()
{
}
