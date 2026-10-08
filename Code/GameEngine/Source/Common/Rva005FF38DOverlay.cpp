// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetMouseOver (WorldBuilder name, line 212: SetSelectionOverlayState _over/_rollOut on change of +0x3D).
//
// was ?rva005FF38D@Rva005FF38D@@QAEX_N@Z @ 0x005FF38D 92B
// Guarded SetSelectionOverlayState via rowed AptCall 0x0050E9FE with _over else _rollOut.
// Evidence: caller jmp 0x005FF4D8; globals TheRva00222A8BTarget g_Rva0107301CEmptyString;
// strings SetSelectionOverlayState _over _rollOut; layout +4 level +8 team +0x3c guard +0x3d flag;
// precedent Rva005F086E 0x005F086E.
class Rva00222A8BTarget;

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FF38DTeam
{
	char m_pad[8];
	char m_name[1];
};

namespace StrategicHUD
{
class BattlePromptArmyPanelMovieClip
{
public:
	class Impl;
};
}
class StrategicHUD::BattlePromptArmyPanelMovieClip::Impl
{
public:
	void SetMouseOver(bool flag);
private:
	char m_pad0[4];
	void *m_level;
	Rva005FF38DTeam *m_team;
	char m_pad0C[48];
	bool m_guard3C;
	bool m_flag3D;
};

void StrategicHUD::BattlePromptArmyPanelMovieClip::Impl::SetMouseOver(bool flag)
{
	if (flag == m_flag3D)
		return;
	if (!m_guard3C) {
		const char *state = flag ? "_over" : "_rollOut";
		const char *prefix = m_team ? m_team->m_name : "";
		Rva0050E9FEAptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "SetSelectionOverlayState", &state);
	}
	m_flag3D = flag;
}
