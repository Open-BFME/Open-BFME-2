// cl: /MD
// StrategicHUD::HUD::Show @0x0042D5DD 85B (WorldBuilder name, StrategicHUD.cpp line
// 462; state 0 shows the level via 0x002224FE, WB AptPlayer::ShowLevel, then 1;
// states 3..4 start _fadeIn and go to 2): Apt fade-state update via rowed Rva00516F21Invoke 0x00516F21 (SetState/_fadeIn) or rowed AptPlayer 0x002224FE on the manager at 0x00DFE4CC. Evidence: count at inner +8 selecting Invoke path (3-4) or setter path (0); strings verified; REL32s to rowed callees.
#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

void Rva00516F21Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const char *value);

#include "../../../Libraries/Source/Apt/AptPlayerClass.h"

struct Rva0042D5DDInner
{
	char m_pad00[4];
	void *m_level;
	int m_08;
};

namespace StrategicHUD
{
class HUD
{
public:
	void Show();
private:
	Rva0042D5DDInner *m_impl;
};
}

void StrategicHUD::HUD::Show()
{
	int state = m_impl->m_08;
	if (state != 0) {
		if (state > 2 && state <= 4) {
			Rva00516F21Invoke((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_impl->m_level, "SetState", "_fadeIn");
			m_impl->m_08 = 2;
		}
		return;
	}
	((AptPlayer *)(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))->ShowLevel((int)m_impl->m_level);
	m_impl->m_08 = 1;
}
