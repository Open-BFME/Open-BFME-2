// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0BloodthirstyUpdateModuleData@@QAE@XZ, retail 0x0044E2AC, 75 bytes. The
// rowed buildFieldParse proc registers the table at 0x00C3F120
// (SacrificeFilter at +8, ExperienceModifier at +0xC, InitiateVoice at
// +0x10), and the rowed BloodthirstyUpdate pool key at 0x44E07E ends where
// the proc begins, so this is the Bloodthirsty behavior's module data (the
// BFME1 BloodthirstyUpdateModuleDataConstructor file proves the class is a
// real Update ModuleData; the BFME2 body below diverged from that donor).
// The empty UpdateModuleData base (inline-empty ctor plus declared-only
// dtor) is load-bearing for the EH state machine (ToppleUpdateModuleDataCtor
// precedent): it advances the state to 0 with no emitted code. Layout past
// the base: explicit vtable slot at +0 (factory-TU precedent, assigned from
// the mem-init so the store leads), the sacrifice filter at +8 through the
// opaque 0x3623E5 pin (EnragedUpdateModuleDataCtor precedent: same mangled
// owner, 4 bytes of storage, declared dtor; the pin claims only the
// address), the experience modifier float at +0xC (1.0f literal, pools to
// 0x00BBB8D8), and the initiate-voice pair at +0x10 through the 0x4CEE6E
// pin (10-byte retail body sets -1 then 0; 42 member-position callers share
// the fold, SlotToLock precedent). The voice member stays trivially
// destructible so the base plus the filter bracket states 0/1 exactly as
// retail; a declared voice dtor would over-count a phantom state.

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();

	unsigned char m_data[4];
};

class InitiateVoiceEntry
{
public:
	InitiateVoiceEntry();

	int m_voiceIndex; // +0, -1
	int m_voiceFlags; // +4, 0
};

class UpdateModuleData
{
public:
	UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class BloodthirstyUpdateModuleData : public UpdateModuleData
{
public:
	BloodthirstyUpdateModuleData();

private:
	const void *m_vtable; // +0
	int m_unused04; // +4
	Rva003623E5Member m_sacrificeFilter; // +8
	float m_experienceModifier; // +0xC
	InitiateVoiceEntry m_initiateVoice; // +0x10
};

// ??0BloodthirstyUpdateModuleData@@QAE@XZ @0x44E2AC
BloodthirstyUpdateModuleData::BloodthirstyUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C3F160))
{
	m_experienceModifier = 1.0f;
}
