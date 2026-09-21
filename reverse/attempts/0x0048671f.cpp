// ??0RebuildHoleExposeDieModuleData@@QAE@XZ
// partial score=0.97 date=2026-09-21
// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0RebuildHoleExposeDieModuleData@@QAE@XZ, retail 0x0048671F, 38 bytes.
// Frameless ctor over the pinned SEH base (??0Rva00253510@@QAE@XZ at
// 0x253510, shared with the UpgradeDie family): base call, then the
// distinctive vtable literal 0x00C4AD40, then the and-zero of the HoleName
// word at +0x38, the float zeros of HoleMaxHealth at +0x3C and
// FadeInTimeSeconds at +0x40 (/arch:SSE keeps them as xorps plus movss),
// and the true byte at +0x44. Size 0x48 matches the 0x24CB18 factory news.
// Class identity is the rowed
// RebuildHoleExposeDieModuleData::buildFieldParse proc (HoleName plus
// HoleMaxHealth table 0x00C4AE00) beside the rowed RebuildHoleExposeDie
// pool key (0x486792) closing this cluster.

class Rva00253510
{
public:
	Rva00253510();
};

class RebuildHoleExposeDieModuleData : public Rva00253510
{
public:
	RebuildHoleExposeDieModuleData();

private:
	void *m_vtable; // +0 (explicit; no virtuals declared, so no vtable is emitted)
	unsigned char m_pad[0x34]; // +4..0x37 (BFME2 base runs 4 wider than BFME1's 0x34)
	int m_holeName; // +0x38 (name key data word)
	float m_holeMaxHealth; // +0x3C
	float m_fadeInTimeSeconds; // +0x40
	bool m_transferAttackers; // +0x44
};

// ??0RebuildHoleExposeDieModuleData@@QAE@XZ @0x48671F
RebuildHoleExposeDieModuleData::RebuildHoleExposeDieModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00C4AD40);
	m_holeName &= 0;
	m_holeMaxHealth = 0.0f;
	m_fadeInTimeSeconds = 0.0f;
	m_transferAttackers = true;
}
