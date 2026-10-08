// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva005F2FEF@Rva005F2FEF@@QAEXABVUnicodeString@@@Z retail 0x005F2FEF 191B
// Evidence: SetMemberNameState _show plus APT:_level%u.%s_MemberName via rowed format 0x00038150 and pinned bfmeSetText 0x00225301; rowed compare 0x00006A7A set 0x00037150 release 0x00036410 AptCall 0x005FB5E6; globals 0x009FE4CC 0x007BAC1C; caller forwarder 0x005F3272; precedent Rva005F7670 UnitName show plus cached
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005F2FEFTeam
{
	char m_pad[8];
	char m_name[1];
};

// The Apt window manager's +0x318 mode (0: idle).
struct Rva005F2537AptMode
{
	unsigned char m_pad000[0x318];
	int m_mode; // +0x318
};

namespace StrategicHUD {
class ArmyDetailsMovieClip
{
public:
	class Impl;

	// The owner's slots the back-button and icon-list callbacks fire
	// (vtable +4 / +8; names follow the bound callbacks, inference).
	ArmyDetailsMovieClip(int level, const AsciiString &name, int layout, bool backButtonVisible);
	virtual void v0();
	virtual void notifyBackButtonClicked();
	virtual void notifyIconListBackgroundClicked();

private:
	Impl *m_impl; // +0x04
};
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

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnicodeString fetch(const AsciiString &label, int x);
};

extern GameTextInterface *TheGameText;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberName(const UnicodeString &text)
{
	if (!(m_flags58 & 1)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberNameState", "_show");
		m_flags58 |= 1;
	}
	if (text.compare(m_cached48) != 0) {
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberName", m_level08, team);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, false);
		m_cached48.set(text);
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::rva005F2897()
{
	if (m_flags58 & 1) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberNameState", "_hide");
		m_flags58 &= ~1;
	}
	if (!m_cached48.isEmpty()) {
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberName", m_level08, team);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, UnicodeString::TheEmptyString, false);
		m_cached48.set(UnicodeString::TheEmptyString);
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideMemberRank()
{
	if (m_flags58 & 2) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberRankState", "_hide");
		m_flags58 &= ~2;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideMemberRankProgress()
{
	if (m_flags58 & 4) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberRankProgressBarState", "_hide");
		m_flags58 &= ~4;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::HideCommandPoints()
{
	if (m_flags58 & 8) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetCommandPointsState", "_hide");
		m_flags58 &= ~8;
	}
}

class Rva005F2A32
{
public:
	void rva005F2A32();
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

void Rva005F2A32::rva005F2A32()
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

__forceinline const char *GetStr005F2A52(const AsciiString &s)
{
	char *t = *(char **)(void *)&s;
	return t ? t + 8 : "";
}

int __cdecl Rva005F2A52AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, float *pF1, float *pF2)
{
	return target->rva00222B19(level, prefix, function, 3, GetStr005F2A52(Rva00222834Get(*pInt)), (void *)GetStr005F2A52(Rva002228E8Get(*pF1)), (void *)GetStr005F2A52(Rva002228E8Get(*pF2)), 0, 0);
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowMemberRank(int rank)
{
	if (rank != m_rank4C) {
		UnicodeString tmp;
		if (rank >= 0) {
			static AsciiString s_rankLabel("APT:RankLabel");
			UnicodeString fetched = TheGameText->fetch(s_rankLabel, 0);
			tmp.format(fetched.str(), rank);
		}
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_MemberRank", m_level08, team);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, tmp, false);
		m_rank4C = rank;
	}
	if (!(m_flags58 & 2)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetMemberRankState", "_show");
		m_flags58 |= 2;
	}
}

void StrategicHUD::ArmyDetailsMovieClip::Impl::ShowCommandPoints(int val)
{
	if (val != m_cmdPts54) {
		UnicodeString tmp;
		if (val >= 0) {
			static AsciiString s_label("STRATEGICHUD:CommandPointsLabel");
			UnicodeString fetched = TheGameText->fetch(s_label, 0);
			tmp.format(fetched.str(), val);
		}
		AsciiString key;
		const char *team = m_team0C ? m_team0C->m_name : "";
		key.format("APT:_level%u.%s_CommandPoints", m_level08, team);
		((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, tmp, false);
		m_cmdPts54 = val;
	}
	if (!(m_flags58 & 8)) {
		const char *team = m_team0C ? m_team0C->m_name : "";
		Rva005FB5E6AptCall(TheRva00222A8BTarget, m_level08, team, "SetCommandPointsState", "_show");
		m_flags58 |= 8;
	}
}

// The four small callbacks the Impl ctor 0x005F39D6 binds as
// "<_level%u.><name>_OnBackButtonClicked / _OnBackButtonRollOver /
// _OnBackButtonRollOut / _OnIconListBackgroundClicked" (retail strings).
void StrategicHUD::ArmyDetailsMovieClip::Impl::OnBackButtonClicked(const char *path)
{
	if (((Rva005F2537AptMode *)TheRva00222A8BTarget)->m_mode == 0)
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
	if (((Rva005F2537AptMode *)TheRva00222A8BTarget)->m_mode == 0)
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
