// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?HidePlayerName@BattlePromptPlayerTabsMovieClip@StrategicHUD@@QAEXXZ @ 0x005FE047 66B
// First-fire guard at +0x34 with player-name fallback and APT Fire for SetPlayerNameVisibility.
// Evidence: refcount inc at +0x34 with jne return; bool false at ebp-1 from al; holder at +8 with +8 name or g_Rva0107301CEmptyString; level at +4; Fire 0x005277D9 row with TheRva00222A8BTarget and string literal; callers 0x005FE140 0x005FE1EA 0x005FE6A4; precedent Rva005F921FButton.cpp holder+8-empty pattern.
#include "unicode_string.h"
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);
struct Rva005FDF1COuter;
int __cdecl Rva0057A9B7Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);
void __cdecl Rva005FDF1CSet(int level, Rva005FDF1COuter *outer, const UnicodeString &text);

struct Rva005FE047Holder
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005FE122Record
{
	char m_pad[8];
	UnicodeString m_text;
};

namespace StrategicHUD {
class BattlePromptPlayerTabsMovieClip;
}

class StrategicHUD::BattlePromptPlayerTabsMovieClip
{
public:
	void HidePlayerName();
	void ShowPlayerName();
	void DoSelectTab(int newTab);
	void rva005FE1D7(int newTab);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005FE047Holder *m_holder08;
	char m_pad0C[0x24 - 0x0C];
	int m_tab24;
	Rva005FE122Record *m_array28;
	char m_pad2C[0x34 - 0x2C];
	int m_count34;
};

void StrategicHUD::BattlePromptPlayerTabsMovieClip::HidePlayerName()
{
	if (m_count34++ != 0)
		return;
	bool flag = false;
	const char *name = m_holder08 ? (const char *)m_holder08 + 8 : "";
	Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, name, "SetPlayerNameVisibility", &flag);
}

void StrategicHUD::BattlePromptPlayerTabsMovieClip::ShowPlayerName()
{
	if (--m_count34 != 0)
		return;
	bool flag = true;
	const char *name = m_holder08 ? (const char *)m_holder08 + 8 : "";
	Rva005277D9Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, name, "SetPlayerNameVisibility", &flag);
}

void StrategicHUD::BattlePromptPlayerTabsMovieClip::DoSelectTab(int newTab)
{
	if (newTab == m_tab24)
		return;
	if (m_tab24 >= 0)
	{
		if (newTab < 0)
			HidePlayerName();
		const char *team = m_holder08 ? (const char *)m_holder08 + 8 : "";
		Rva0057A9B7Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetTabState", &m_tab24, (void *)"_deselect");
	}
	int old = m_tab24;
	m_tab24 = newTab;
	if (newTab < 0)
		return;
	const char *team = m_holder08 ? (const char *)m_holder08 + 8 : "";
	Rva0057A9B7Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level04, team, "SetTabState", &m_tab24, (void *)"_selected");
	if (old < 0)
		ShowPlayerName();
	Rva005FDF1CSet((int)m_level04, (Rva005FDF1COuter *)&m_holder08, m_array28[m_tab24].m_text);
}

void StrategicHUD::BattlePromptPlayerTabsMovieClip::rva005FE1D7(int newTab)
{
	if (newTab != m_tab24)
	{
		if (newTab == 0)
			HidePlayerName();
		else if (m_tab24 == 0)
			ShowPlayerName();
	}
	DoSelectTab(newTab);
}
