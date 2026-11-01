// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005F7670@Rva005F7670@@QAEXABVUnicodeString@@@Z retail 0x005F7670 190B
// Evidence: format APT:_level%u.%s_UnitName via rowed 0x00038150; pinned bfmeSetText 0x00225301; rowed releaseBuffer 0x00036410; rowed compare 0x00006A7A and set 0x00037150; AptCall row 0x005FB5E6 with SetUnitNameState _show; globals 0x009FE4CC 0x007BAC1C; caller forwarder 0x005F772E; precedent Rva005FB770 cached compare plus Rva005FB6E2 once flag
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

class Rva00222A8BTarget
{
};

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005F7670Team
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005F6F0C
{
	void Update();
};

namespace StrategicHUD {
class BuildQueueDetailsMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BuildQueueDetailsMovieClip::Impl
{
public:
	void ShowUnitName(const UnicodeString &text);
	void HideUnitName();
	void HideCommandPoints();
	void HideBuildTime();
	void ShowCommandPoints(int val);
	void ShowBuildTime(int val);
	void rva005F744E();
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F7670Team *m_team08;
	char m_pad0C[0x38 - 0x0C];
	Rva005F6F0C *m_tip38;
	Rva005F6F0C *m_tips3C[7];
	UnicodeString m_cached58;
	int m_buildTime5C;
	int m_cmdPts60;
	bool m_shown64;
	bool m_shown65;
	bool m_shown66;
};

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::ShowUnitName(const UnicodeString &text)
{
	if (text.compare(m_cached58) != 0) {
		AsciiString key;
		const char *team = m_team08 ? m_team08->m_name : "";
		key.format("APT:_level%u.%s_UnitName", m_level04, team);
		g_bfmeAptWindowManager->bfmeSetText(key, text, false);
		m_cached58.set(text);
	}
	if (!m_shown64) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetUnitNameState", "_show");
		m_shown64 = true;
	}
}

class Rva005F772E
{
public:
	void rva005F772E(const UnicodeString &text);
	void rva005F7470();
private:
	char m_pad00[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member04;
};

void Rva005F772E::rva005F772E(const UnicodeString &text)
{
	m_member04->ShowUnitName(text);
}

void Rva005F772E::rva005F7470()
{
	m_member04->HideUnitName();
}

void StrategicHUD::BuildQueueDetailsMovieClip::Impl::HideUnitName()
{
	if (m_shown64) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetUnitNameState", "_hide");
		m_shown64 = false;
	}
}
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::HideCommandPoints()
{
	if (m_shown66) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetCommandPointsState", "_hide");
		m_shown66 = false;
	}
}
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::HideBuildTime()
{
	if (m_shown65) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetBuildTimeState", "_hide");
		m_shown65 = false;
	}
}
// ?rva005F7304@Rva005F7670@@QAEXH@Z retail 0x005F7304 270B
// Evidence: cached int at +0x60 vs edi; TheGameText fetch slot 0x3C STRATEGICHUD:CommandPointsLabel with +8-or-NullChr via str(); Unicode format row 0x006CB5D0; Ascii format APT:_level%u.%s_CommandPoints row 0x00038150; bfmeSetText pin 0x00225301; AptCall row 0x005FB5E6 SetCommandPointsState _show; globals 0x009FE4CC 0x007BAC1C 0x007BB5C4; precedent Rva005F2FEF::rva005F2D41
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::ShowCommandPoints(int val)
{
	if (val != m_cmdPts60) {
		UnicodeString label;
		if (val >= 0) {
			UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:CommandPointsLabel", 0);
			label.format(fetched.str(), val);
		}
		AsciiString key;
		const char *team = m_team08 ? m_team08->m_name : "";
		key.format("APT:_level%u.%s_CommandPoints", m_level04, team);
		g_bfmeAptWindowManager->bfmeSetText(key, label, false);
		m_cmdPts60 = val;
	}
	if (!m_shown66) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetCommandPointsState", "_show");
		m_shown66 = true;
	}
}
// ?rva005F719D@Rva005F7670@@QAEXH@Z retail 0x005F719D 299B
// Evidence: cached int at +0x5C; singular vs plural BuildTime labels via fetch slot 0x3C; set row 0x00037150 vs format row 0x006CB5D0 with +8-or-NullChr; Ascii APT:_level%u.%s_BuildTime row 0x00038150; bfmeSetText pin 0x00225301; AptCall 0x005FB5E6 SetBuildTimeState _show flag +0x65; precedent rva005F7304 CommandPoints
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::ShowBuildTime(int val)
{
	if (val != m_buildTime5C) {
		UnicodeString label;
		if (val >= 0) {
			if (val == 1) {
				label.set(TheGameText->fetch("STRATEGICHUD:BuildTimeSingularLabel", 0));
			} else {
				UnicodeString fetched = TheGameText->fetch("STRATEGICHUD:BuildTimePluralLabel", 0);
				label.format(fetched.str(), val);
			}
		}
		AsciiString key;
		const char *team = m_team08 ? m_team08->m_name : "";
		key.format("APT:_level%u.%s_BuildTime", m_level04, team);
		g_bfmeAptWindowManager->bfmeSetText(key, label, false);
		m_buildTime5C = val;
	}
	if (!m_shown65) {
		const char *team = m_team08 ? m_team08->m_name : "";
		Rva005FB5E6AptCall(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level04, team, "SetBuildTimeState", "_show");
		m_shown65 = true;
	}
}
// ?rva005F744E@Rva005F7670@@QAEXXZ retail 0x005F744E 34B
// Evidence: 1 plus 7 loop over Rva005F6F0C pointers at +0x38 and +0x3C via rowed 0x005F6F0C; caller forwarder 0x005F749B; gap between rva005F7412 and rva005F7470
void StrategicHUD::BuildQueueDetailsMovieClip::Impl::rva005F744E()
{
	m_tip38->Update();
	for (int i = 0; i < 7; i++)
		m_tips3C[i]->Update();
}

// ?rva005F7478@Rva005F7478@@QAEXH@Z @0x005F7478 8B member forwarder to rowed
// ?rva005F719D@Rva005F7670@@QAEXH@Z (int arg passes through the shared stack
// slot). No callers. Honest address name.
class Rva005F7478
{
public:
	void rva005F7478(int val);
private:
	char m_pad[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member;
};
void Rva005F7478::rva005F7478(int val)
{
	return m_member->ShowBuildTime(val);
}

// ?rva005F7480@Rva005F7480@@QAEXXZ @0x005F7480 8B member forwarder to rowed
// ?rva005F72C8@Rva005F7670@@QAEXXZ. No callers. Honest address name.
class Rva005F7480
{
public:
	void rva005F7480();
private:
	char m_pad[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member;
};
void Rva005F7480::rva005F7480()
{
	return m_member->HideBuildTime();
}

// ?rva005F7488@Rva005F7488@@QAEXH@Z @0x005F7488 8B member forwarder to rowed
// ?rva005F7304@Rva005F7670@@QAEXH@Z (int arg passes through the shared stack
// slot). No callers. Honest address name.
class Rva005F7488
{
public:
	void rva005F7488(int val);
private:
	char m_pad[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member;
};
void Rva005F7488::rva005F7488(int val)
{
	return m_member->ShowCommandPoints(val);
}

// ?rva005F7490@Rva005F7490@@QAEXXZ @0x005F7490 8B member forwarder to rowed
// ?rva005F7412@Rva005F7670@@QAEXXZ. No callers. Honest address name.
class Rva005F7490
{
public:
	void rva005F7490();
private:
	char m_pad[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member;
};
void Rva005F7490::rva005F7490()
{
	return m_member->HideCommandPoints();
}

// ?rva005F7498@Rva005F7498@@QAEXXZ @0x005F7498 8B member forwarder to rowed
// ?rva005F744E@Rva005F7670@@QAEXXZ. No callers. Honest address name.
class Rva005F7498
{
public:
	void rva005F7498();
private:
	char m_pad[4];
	StrategicHUD::BuildQueueDetailsMovieClip::Impl *m_member;
};
void Rva005F7498::rva005F7498()
{
	return m_member->rva005F744E();
}
