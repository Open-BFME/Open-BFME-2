// cl: /MD
// ?DoSetCurrentPhase@ChecklistUIImpl@StrategicHUD@@QAEXH@Z, retail 0x0057AB16 186B chain via 0x0057A9B7.
// Phase-index setter: mapped old/new via rowed Get 0x0057A3B2, fires inactive/active via 0x0057A9B7/0x00525338, then rowed Set 0x0057A685.
// Evidence: callees rowed Get plus Fire plus Set; strings SetPhaseIndicatorState _inactive _active literals; externs g_Rva0107301CEmptyString TheRva00222A8BTarget; prev 0x0057AAD5 next 0x0057AC27 same dir.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva0057A3B2Get(int val);
int __cdecl Rva0057A9B7Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);
int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);

struct Rva0057A685Team
{
	char m_pad[8];
	char m_name[1];
};
void __cdecl Rva0057A685Set(int level, Rva0057A685Team **ppTeam, int phase);

namespace StrategicHUD {
class ChecklistUIImpl;
}

class StrategicHUD::ChecklistUIImpl
{
public:
	void DoSetCurrentPhase(int index);
private:
	char m_pad00[8];
	int m_level08;
	Rva0057A685Team *m_team0C;
	char m_pad10[0x40 - 0x10];
	int m_40;
};

void StrategicHUD::ChecklistUIImpl::DoSetCurrentPhase(int index)
{
	if (index == m_40)
		return;
	int oldMapped = Rva0057A3B2Get(m_40);
	int newMapped = Rva0057A3B2Get(index);
	if (newMapped != oldMapped) {
		if (oldMapped >= 0) {
			const char *prefix = m_team0C ? m_team0C->m_name : "";
			Rva0057A9B7Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level08, prefix, "SetPhaseIndicatorState", &oldMapped, (void *)"_inactive");
		}
		if (newMapped >= 0) {
			const char *prefix = m_team0C ? m_team0C->m_name : "";
			Rva00525338Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level08, prefix, "SetPhaseIndicatorState", &newMapped, (void *)"_active");
		}
	}
	Rva0057A685Set(m_level08, &m_team0C, index);
	m_40 = *(volatile int *)&index;
}
