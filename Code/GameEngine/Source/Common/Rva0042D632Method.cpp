// cl: /MD
// StrategicHUD::HUD::FadeOut @0x0042D632 74B (WorldBuilder name, StrategicHUD.cpp
// line 494): state switch on the Impl +8 driving Apt invokes; state 1 hides the
// level (0x0022277D, WB AptPlayer::HideLevel), state 2 starts _fadeOut.
// Evidence: rowed free invoke 0x00516F21 (strings SetState _fadeOut) plus pin 0x0022277D;
// caller 0x0042C39A; neighbours 0x0042D55B 0x0042D697.

class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")

void __cdecl Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);

struct Rva0042D632Inner
{
	char m_pad00[4];
	void *m_04;
	unsigned int m_08;
};

namespace StrategicHUD
{
class HUD
{
public:
	void FadeOut();
private:
	Rva0042D632Inner *m_impl;
};
}

void StrategicHUD::HUD::FadeOut()
{
	switch (m_impl->m_08)
	{
	case 1:
		TheRva00222A8BTarget->rva0022277D(reinterpret_cast<int>(m_impl->m_04));
		m_impl->m_08 = 0;
		break;
	case 2:
		Rva00516F21Invoke(TheRva00222A8BTarget, m_impl->m_04, "SetState", "_fadeOut");
		m_impl->m_08 = 3;
		break;
	}
}
