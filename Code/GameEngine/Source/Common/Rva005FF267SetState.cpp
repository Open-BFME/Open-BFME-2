// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF267@Rva005FF267@@QAEXH@Z @ 0x005FF267 69B
// Apt SetState via rowed AptCall 0x0050E9FE with team prefix or empty fallback and state table.
// Evidence: caller jmp 0x005FF4C0; globals TheRva00222A8BTarget g_Rva0107301CEmptyString;
// string SetState; layout +4 level +8 team +0x24 state matches StrategicHUD::BattlePromptArmyPanelMovieClip::Impl; precedent Rva005FFC26SetState.
class Rva00222A8BTarget;

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C7A49C[];

int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FF267Team
{
	char m_pad[8];
	char m_name[1];
};

class Rva005FF267
{
public:
	void rva005FF267(int state);
private:
	char m_pad0[4];
	void *m_level;
	Rva005FF267Team *m_team;
	char m_padC[24];
	int m_state;
};

void Rva005FF267::rva005FF267(int state)
{
	if (state == m_state)
		return;
	const char *prefix = m_team ? m_team->m_name : "";
	Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "SetState", &g_00C7A49C[state]);
	m_state = state;
}
