// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS
//
// ??0RiderChangeContainModuleData@@QAE@XZ, retail 0x0047EABC, 94 bytes.
// RiderChangeContain ModuleData default ctor over the pinned SiegeEngine
// base (0x47C927). The 8 RiderInfo slots at +0x1B8 are 0x18-byte elements
// with two AsciiString members (at +0 and +0x10, matching the 53B retail
// RiderInfo dtor at 0x47E3AC which tears both down via 0x36410 and the 10B
// ctor at 0x47E3A2 which nulls them); the array is built in place
// through the rowed ehvec helper at 0x629512. Trailing scuttle fields
// (+0x278 frames, +0x27C state TOPPLED=0, +0x280 byte) are zeroed; size
// 0x284 matches the 0x24BD63 factory news. Row supersedes the ctor pin.

#include "ascii_string.h"

struct RiderInfo
{
	AsciiString m_templateName; // +0
	int m_weaponSetFlag; // +4
	int m_modelConditionFlagType; // +8
	int m_objectStatusType; // +0xC
	AsciiString m_commandSet; // +0x10
	int m_locomotorSetType; // +0x14

	RiderInfo();
	~RiderInfo();
};

RiderInfo::RiderInfo()
{
}

RiderInfo::~RiderInfo()
{
}

class SiegeEngineContainModuleData
{
public:
	SiegeEngineContainModuleData();
	virtual ~SiegeEngineContainModuleData();

private:
	unsigned char m_pad[0x1B8 - 4];
};

class RiderChangeContainModuleData : public SiegeEngineContainModuleData
{
public:
	RiderChangeContainModuleData();
	virtual ~RiderChangeContainModuleData();

private:
	RiderInfo m_riders[8]; // +0x1B8
	int m_scuttleFrames; // +0x278
	int m_scuttleState; // +0x27C
	unsigned char m_byte280; // +0x280
	unsigned char m_pad281[0x284 - 0x280 - 1];
};

// ??0RiderChangeContainModuleData@@QAE@XZ @0x0047EABC
RiderChangeContainModuleData::RiderChangeContainModuleData()
{
	m_scuttleFrames = 0;
	m_scuttleState = 0;
	m_byte280 = 0;
}
