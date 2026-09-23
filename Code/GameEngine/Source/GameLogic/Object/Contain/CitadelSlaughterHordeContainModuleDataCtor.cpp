// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0CitadelSlaughterHordeContainModuleData@@QAE@XZ, retail 0x0048112F
// (155 bytes). Citadel slaughter-horde data over the pinned
// SlaughterHordeContain base ctor (0x48104D, factory news 0xEC):
// StatusForRingEntry at +0xEC resets through the rowed
// bitset<128>::reset at 0x0024CA24, ObjectToDestroyForRingEntry at +0xFC
// builds through the opaque 0x3623E5 pin, UpgradeForRingEntry at +0x100
// is an AsciiString vector through the rowed Vector_base at 0x00211E58,
// FXForRingEntry at +0x10C nulls, the +0xEC region memsets, and two 28B
// FixedStorage temps from the prototype at 0x00DFEFA4 feed the filter
// through the 0x362087 pin (ret 0x38). Own table 0x00848890 proves every
// field; the CitadelSlaughterHordeContain data factory at 0x0024C100
// news 0x110 and calls this ctor as sole caller. Shape follows
// RespawnBodyModuleDataCtor (virtual base plus virtual derived with
// declared-only dtors arms the EH states over the same temps; the
// compiler installs this TU's vtable through the ??_7 pin at 0x00C48E40,
// whose slot0 is the scalar-deleting dtor at 0x4811CA) over
// PassiveAreaEffectBehaviorModuleDataCtor (plain _STL::vector members
// plus inline-reset bitset wrapper sequencing the reset call in decl
// order among the member init calls).

#include <bitset>
#include <vector>
#include <string.h>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

// Inline wrapper ctor plus cast-reset for an init-phase bitset reset: it
// emits the bare reset call with zero construction overhead, sequenced in
// decl order among the member init calls (fleet Stealth lever).
struct StatusForRingEntryBits
{
	StatusForRingEntryBits() { ((_STL::bitset<128> *)m_words)->reset(); }
	unsigned long m_words[4]; // +0xEC, StatusForRingEntry bitset<128>
};

// Virtual base plus virtual derived with declared-only dtors (no code):
// the base contributes the vptr at +0 so the base call takes this with no
// displacement, and the derived vtable store lands mid-init through the
// ??_7 pin (RespawnBodyModuleDataCtor precedent).
class SlaughterHordeContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();

private:
	unsigned char m_pad[0xEC - 4]; // +0x04..+0xEB, real SlaughterHorde base
};

class CitadelSlaughterHordeContainModuleData : public SlaughterHordeContainModuleData
{
public:
	CitadelSlaughterHordeContainModuleData();
	virtual ~CitadelSlaughterHordeContainModuleData();

private:
	StatusForRingEntryBits m_statusForRingEntry; // +0xEC, StatusForRingEntry
	Rva003623E5Member m_objectToDestroy; // +0xFC, ObjectToDestroyForRingEntry
	_STL::vector<AsciiString> m_upgradeForRingEntry; // +0x100, UpgradeForRingEntry
	void *m_fxForRingEntry; // +0x10C, FXForRingEntry
};

// ??0CitadelSlaughterHordeContainModuleData@@QAE@XZ @0x48112F
CitadelSlaughterHordeContainModuleData::CitadelSlaughterHordeContainModuleData()
{
	m_fxForRingEntry = 0;
	memset(m_statusForRingEntry.m_words, 0, sizeof(m_statusForRingEntry.m_words));
	m_objectToDestroy.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
