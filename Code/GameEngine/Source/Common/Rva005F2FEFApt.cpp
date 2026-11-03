// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005F2FEF@Rva005F2FEF@@QAEXABVUnicodeString@@@Z retail 0x005F2FEF 191B
// Evidence: SetMemberNameState _show plus APT:_level%u.%s_MemberName via rowed format 0x00038150 and pinned bfmeSetText 0x00225301; rowed compare 0x00006A7A set 0x00037150 release 0x00036410 AptCall 0x005FB5E6; globals 0x009FE4CC 0x007BAC1C; caller forwarder 0x005F3272; precedent Rva005F7670 UnitName show plus cached
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005F2FEFTeam
{
	char m_pad[8];
	char m_name[1];
};

// The Apt window manager's +0x318 mode (0: idle).
struct AptWindowManager
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

#include "../../Include/GameClient/ArmyDetailsMovieClip.h"
namespace StrategicHUD {
}

class StrategicHUD::ArmyDetailsMovieClip::Impl
{
public:
	void ShowMemberName(const UnicodeString &text);
	void rva005F2897();
	void HideMemberRank();
	void HideMemberRankProgress();
	void HideCommandPoints();
	void ShowMemberRank(int rank);
	void ShowMemberRankProgress(float progress);
	void ShowCommandPoints(int val);
	Impl(ArmyDetailsMovieClip *owner, int level, const AsciiString &name, int layout, bool backButtonVisible); // 0x005F39D6 (pinned)
	void OnBackButtonClicked(const char *path);
	void OnBackButtonRollOver(const char *path);
	void OnBackButtonRollOut(const char *path);
	void OnIconListBackgroundClicked(const char *path);
private:
	void *m_vtbl; // +0x00 (0x00879290)
	ArmyDetailsMovieClip *m_owner; // +0x04
	void *m_level08;
	Rva005F2FEFTeam *m_team0C;
	char m_pad10[0x48 - 0x10];
	UnicodeString m_cached48;
	int m_rank4C;
	char m_pad50[4];
	int m_cmdPts54;
	unsigned char m_flags58;
};

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberName(const UnicodeString &text)
{
	if (!(m_flags58 & 1)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetMemberNameState", "_show");
		m_flags58 |= 1;
	}
	if (text.compare(m_cached48) != 0) {
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberName", m_level08, team);
		g_bfmeAptWindowManager->bfmeSetText(key, text, false);
		m_cached48.set(text);
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::rva005F2897()
{
	if (m_flags58 & 1) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetMemberNameState", "_hide");
		m_flags58 &= ~1;
	}
	if (!m_cached48.isEmpty()) {
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberName", m_level08, team);
		g_bfmeAptWindowManager->bfmeSetText(key, UnicodeString::TheEmptyString, false);
		m_cached48.set(UnicodeString::TheEmptyString);
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideMemberRank()
{
	if (m_flags58 & 2) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetMemberRankState", "_hide");
		m_flags58 &= ~2;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideMemberRankProgress()
{
	if (m_flags58 & 4) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetMemberRankProgressBarState", "_hide");
		m_flags58 &= ~4;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideCommandPoints()
{
	if (m_flags58 & 8) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetCommandPointsState", "_hide");
		m_flags58 &= ~8;
	}
}

class Rva005F2A32
{
public:
	void HideMemberName();
	void rva005F2A3A();
	void rva005F2A42();
	void rva005F2A4A();
	void rva005F2F41(int rank);
	void rva005F2F49(float progress);
	void rva005F2F5C(int val);
	void rva005F3272(const UnicodeString &text);
private:
	char m_pad00[4];
	StrategicHUD::ArmyDetailsMovieClip::Impl *m_member04;
};

void Rva005F2A32::HideMemberName()
{
	m_member04->rva005F2897();
}

void Rva005F2A32::rva005F2A3A()
{
	m_member04->HideMemberRank();
}

void Rva005F2A32::rva005F2A42()
{
	m_member04->HideMemberRankProgress();
}

void Rva005F2A32::rva005F2A4A()
{
	m_member04->HideCommandPoints();
}

void Rva005F2A32::rva005F2F41(int rank)
{
	m_member04->ShowMemberRank(rank);
}

void Rva005F2A32::rva005F2F49(float progress)
{
	m_member04->ShowMemberRankProgress(progress);
}

void Rva005F2A32::rva005F2F5C(int val)
{
	m_member04->ShowCommandPoints(val);
}

void Rva005F2A32::rva005F3272(const UnicodeString &text)
{
	m_member04->ShowMemberName(text);
}

AsciiString Rva00222834Get(int val);
AsciiString Rva002228E8Get(float val);

__forceinline const char *GetStr005F2A52(const AsciiString &asciiString)
{
	char *stringData = *(char **)(void *)&asciiString;
	return stringData ? stringData + 8 : "";
}

int __cdecl Rva005F2A52AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, float *xPos, float *yPos)
{
	return target->rva00222B19(level, prefix, function, 3, GetStr005F2A52(Rva00222834Get(*pInt)), (void *)GetStr005F2A52(Rva002228E8Get(*xPos)), (void *)GetStr005F2A52(Rva002228E8Get(*yPos)), 0, 0);
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberRank(int rank)
{
	if (rank != m_rank4C) {
		UnicodeString rankText;
		if (rank >= 0) {
			static AsciiString s_rankLabel("APT:RankLabel");
			UnicodeString fetched = TheGameText->fetch(s_rankLabel, 0);
			rankText.format(fetched.str(), rank);
		}
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberRank", m_level08, team);
		g_bfmeAptWindowManager->bfmeSetText(key, rankText, false);
		m_rank4C = rank;
	}
	if (!(m_flags58 & 2)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetMemberRankState", "_show");
		m_flags58 |= 2;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowCommandPoints(int val)
{
	if (val != m_cmdPts54) {
		UnicodeString commandPointsText;
		if (val >= 0) {
			static AsciiString s_label("STRATEGICHUD:CommandPointsLabel");
			UnicodeString fetched = TheGameText->fetch(s_label, 0);
			commandPointsText.format(fetched.str(), val);
		}
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_CommandPoints", m_level08, team);
		g_bfmeAptWindowManager->bfmeSetText(key, commandPointsText, false);
		m_cmdPts54 = val;
	}
	if (!(m_flags58 & 8)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level08, team, "SetCommandPointsState", "_show");
		m_flags58 |= 8;
	}
}

// ArmyDetailsMovieClip vtable 0x00C7936C slots 1 and 2: the base class's
// notify hooks are empty; both entries are the shared RET at 0x000B3FD0.
void StrategicHUD::ArmyDetailsMovieClip::notifyBackButtonClicked() {}
void StrategicHUD::ArmyDetailsMovieClip::notifyIconListBackgroundClicked() {}

// The four small callbacks the Impl ctor 0x005F39D6 binds as
// "<_level%u.><name>_OnBackButtonClicked / _OnBackButtonRollOver /
// _OnBackButtonRollOut / _OnIconListBackgroundClicked" (retail strings).
void StrategicHUD::ArmyDetailsMovieClip::Impl::OnBackButtonClicked(const char *path)
{
	if (((AptWindowManager *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyBackButtonClicked();
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::OnBackButtonRollOver(const char *path)
{
	m_flags58 |= 0x10;
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::OnBackButtonRollOut(const char *path)
{
	m_flags58 &= ~0x10;
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::OnIconListBackgroundClicked(const char *path)
{
	if (((AptWindowManager *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->notifyIconListBackgroundClicked();
}

// The owner's ctor 0x005F3E93 (ret 0x10): vtable 0x0087936C and its Impl
// (new 0x5C; WorldBuilder-named ctor 0x005F39D6, pinned: it stores owner,
// level and the name, lays out "_hero" when the layout is 1 and sets
// SetBackButtonVisibility from the flag) built with this and the arguments.
StrategicHUD::ArmyDetailsMovieClip::ArmyDetailsMovieClip(int level, const AsciiString &name, int layout, bool backButtonVisible)
	: m_impl(new Impl(this, level, name, layout, backButtonVisible))
{
}

// Native 5F3E93 installs C7936C: slot 0 is scalar 5F39BA, which calls
// complete destructor 5F38CA. Both bodies and the +4 owned Impl agree with
// the named constructor, independently establishing the class identity.
class Rva005F35D3 { public: void clear(); };
StrategicHUD::ArmyDetailsMovieClip::~ArmyDetailsMovieClip()
{
    reinterpret_cast<Rva005F35D3 *>(&m_impl)->clear();
}
