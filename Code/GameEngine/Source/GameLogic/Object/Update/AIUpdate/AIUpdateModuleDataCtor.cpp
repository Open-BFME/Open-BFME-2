// cl: /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ??0AIUpdateModuleData@@QAE@XZ at retail 0x0058925D (58B). The
// AIUpdateModuleData base is vtable 0xC70220 at +0, an int zero at +8, an
// InitiateVoiceEntry pair at +0xC built through the pinned 0x4CEE6E fold,
// and a false byte at +0x14; +4 is an unstored gap (DemoTrap law). The
// single EH state comes from an empty base with declared-only dtor (Topple
// pattern, zero emitted code). ALL-INIT-LIST law: the +8 zero in the init
// list reproduces retail order (and-8 above the vtable store and the member
// call); the same zero in the body sinks below the call. Row supersedes
// the pin (Dozer calls this base).
class EmptyBase
{
public:
	EmptyBase() {}
	~EmptyBase();
};

struct InitiateVoiceEntry
{
	InitiateVoiceEntry();
	int m_a;
	int m_b;
};

class AIUpdateModuleData : public EmptyBase
{
public:
	AIUpdateModuleData();

private:
	void *m_vtable; // +0
	int m_unused04; // +4
	int m_unused08; // +8
	InitiateVoiceEntry m_voice; // +0xC
	bool m_unused14; // +0x14
};

// ??0AIUpdateModuleData@@QAE@XZ @0x58925D
AIUpdateModuleData::AIUpdateModuleData()
	: m_vtable(reinterpret_cast<void *>(0x00C70220))
	, m_unused08(0)
	, m_voice()
{
	m_unused14 = false;
}
