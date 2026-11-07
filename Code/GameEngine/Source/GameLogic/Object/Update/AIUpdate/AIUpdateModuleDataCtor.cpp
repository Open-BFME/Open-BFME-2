// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
//
// ??0AIUpdateModuleData@@QAE@XZ at retail 0x0058925D (58B). AIUpdateModuleData
// derives from the canonical ModuleData (eight bytes: vptr and module tag)
// and adds nothing to its 31-slot interface, so the compiler installs
// retail's table 0xC70220 at +0. Members: an int zero at +8, an
// InitiateVoiceEntry pair at +0xC built through the pinned 0x4CEE6E fold,
// and a false byte at +0x14. ModuleData's out-of-line virtual destructor
// (rowed 0x0049B47C) arms the single EH state. ALL-INIT-LIST law: the +8
// zero in the init list reproduces retail order (and-8 above the vtable
// store and the member call); the same zero in the body sinks below the
// call. Row supersedes the pin (Dozer calls this base).

#include "../../../../../Include/Common/ModuleData.h"

struct InitiateVoiceEntry
{
	InitiateVoiceEntry();
	int m_a;
	int m_b;
};

class AIUpdateModuleData : public ModuleData
{
public:
	AIUpdateModuleData();
	virtual ~AIUpdateModuleData();

private:
	int m_unused08; // +8
	InitiateVoiceEntry m_voice; // +0xC
	bool m_unused14; // +0x14
};

// ??0AIUpdateModuleData@@QAE@XZ @0x58925D
AIUpdateModuleData::AIUpdateModuleData()
	: m_unused08(0)
	, m_voice()
{
	m_unused14 = false;
}
