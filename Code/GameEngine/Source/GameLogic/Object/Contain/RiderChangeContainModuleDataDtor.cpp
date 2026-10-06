// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS
//
// ??1RiderChangeContainModuleData@@UAE@XZ, retail 0x0047EB36, 66 bytes.
// RiderChangeContain ModuleData dtor over the pinned SiegeEngine base
// (0x0047C9CB). Destroys the 8 RiderInfo slots at +0x1B8 (0x18-byte elements)
// through the rowed ehvec helper at 0x00629110, then calls the base dtor.
// Layout matches the verified ctor at 0x0047EABC in
// RiderChangeContainModuleDataCtor.cpp (array via 0x00629512, vtable 0x00C47B00
// at [esi], size 0x284 from factory 0x0024BD63). Called by the audited
// ??_G wrapper at 0x0047EB1A (slot 0 of vtable 0x00C47B00). No derived vptr
// store in retail, so the derived class is novtable (cf. HelixContainModuleDataDtor).
// BFME1 donor RiderChangeContainModuleDataDestructorThunk.cpp:68 diverges in
// layout; retail followed.

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

class SiegeEngineContainModuleData
{
public:
	SiegeEngineContainModuleData();
	virtual ~SiegeEngineContainModuleData();

private:
	unsigned char m_pad[0x1B8 - 4];
};

class __declspec(novtable) RiderChangeContainModuleData : public SiegeEngineContainModuleData
{
public:
	virtual ~RiderChangeContainModuleData();

private:
	RiderInfo m_riders[8]; // +0x1B8
	int m_scuttleFrames; // +0x278
	int m_scuttleState; // +0x27C
	unsigned char m_byte280; // +0x280
	unsigned char m_pad281[0x284 - 0x280 - 1];
};

RiderChangeContainModuleData::~RiderChangeContainModuleData()
{
}
