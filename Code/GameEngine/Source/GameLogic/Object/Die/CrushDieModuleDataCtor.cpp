// cl: /O1 /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS
//
// ??0CrushDieModuleData@@QAE@XZ, retail 0x002539B3, 81 bytes.
// CrushDie ModuleData default ctor over the pinned SEH intermediate base
// (??0Rva00253510@@QAE@XZ at 0x253510, shared with the Die family). The
// virtual base (KeepObjectDie/CreateObjectDieModuleDataCtor precedent)
// carries the vptr the compiler installs itself right after the base call;
// the DIR32 slot is patched from retail like any other vtable install, so
// no ??_7 pin is owed. The four crush-sound slots +0x38 are AudioEventRTS
// elements (BFME1 donor field m_crushSounds) built in place through the
// array-construction helper at 0x629512 (existing ??_L fold pins); the
// element setup/teardown addresses the helper takes (0x726BE6/0x50F149,
// both unidentified) are DIR32 slots the patcher copies from retail, and
// the rowed 64B AudioEventRTS ctor at 0x79514 plus 53B dtor at 0x793FA give
// the TU-local 4-byte element declaration its linkage while keeping it
// opaque here (opacity is load-bearing for the EH frame). Element size 4 is
// proven by the helper's size push. The four crush-sound percent slots
// +0x48 take 100 through the donor loop below, unrolled to stosd form.
// Size 0x58 (0x38 base + 16-byte sounds + 16-byte percents) matches the
// 0x253A27 factory news in the rowed CrushDieModuleDataFriendNew TU.
// Identity: ModuleFactory registers "CrushDie" to factory 0x253A27 which
// sole-calls this ctor (pin 3628, superseded by this row), plus the rowed
// crush-sound parse proc 0x253A05.

class AudioEventRTS
{
public:
	AudioEventRTS();
	~AudioEventRTS();

private:
	int m_data; // 4 bytes (retail element size); real layout unrecovered
};

class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

private:
	unsigned char m_pad[0x38 - 4];
};

enum
{
	CRUSH_COUNT = 4,
};

class CrushDieModuleData : public Rva00253510
{
public:
	CrushDieModuleData();

private:
	AudioEventRTS m_crushSounds[CRUSH_COUNT]; // +0x38
	int m_crushSoundPercent[CRUSH_COUNT]; // +0x48
};

// ??0CrushDieModuleData@@QAE@XZ @0x2539B3
CrushDieModuleData::CrushDieModuleData()
{
	for (int i = 0; i < CRUSH_COUNT; ++i)
		m_crushSoundPercent[i] = 100;
}

// ??1Rva00253510@@UAE@XZ present-unmatched
Rva00253510::~Rva00253510()
{
}
