// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005ED708@StrategicHUD::RegionAwardMovieClip::Impl@@QAEXHH@Z, retail 0x005ED708, 98 bytes.
// NumRegions cached setter via Rva005ED310Get and SetPlayerString; imul needs /G7.
// Evidence: calls 0x005ED310 0x005ED516 0x00036E70; string APT NumRegions via callee; base +0x44 slot size 0x14 field +0xC; caller 0x005ED849.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "unicode_string.h"


UnicodeString Rva005ED310Get(int val);

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva0057A9B7Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);

struct Rva005ED445Holder
{
	char m_pad[8];
	char m_name[1];
};

struct Rva005ED445Slot
{
	UnicodeString m_name;
	char m_pad[0x0C - 0x04];
	int m_numRegions;
	int m_numUnits;
};

namespace StrategicHUD {
class RegionAwardMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionAwardMovieClip::Impl
{
public:
	void SetPlayerString(int suffixIndex, const char *suffix, const UnicodeString &text);
	void rva005ED708(int index, int num);
	void rva005ED76A(int index, int num);
	void SetPlayerName(int index, const UnicodeString &text);
	void SelectPlayer(int newRow);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005ED445Holder *m_holder08;
	char m_pad0C[0x44 - 0x0C];
	Rva005ED445Slot *m_slots;
	char m_pad48[0x50 - 0x48];
	int m_row50;
};

void StrategicHUD::RegionAwardMovieClip::Impl::rva005ED708(int index, int num)
{
	Rva005ED445Slot *base = m_slots;
	Rva005ED445Slot *slot = base + index;
	if (num != slot->m_numRegions) {
		SetPlayerString(index, "NumRegions", Rva005ED310Get(num));
		slot->m_numRegions = num;
	}
}

void StrategicHUD::RegionAwardMovieClip::Impl::rva005ED76A(int index, int num)
{
	Rva005ED445Slot *base = m_slots;
	Rva005ED445Slot *slot = base + index;
	if (num != slot->m_numUnits) {
		SetPlayerString(index, "NumUnits", Rva005ED310Get(num));
		slot->m_numUnits = num;
	}
}

void StrategicHUD::RegionAwardMovieClip::Impl::SetPlayerName(int index, const UnicodeString &text)
{
	Rva005ED445Slot *base = m_slots;
	Rva005ED445Slot *slot = base + index;
	if (((const StringBase<unsigned short> *)(const void *)&text)->compare(*(const StringBase<unsigned short> *)(const void *)&slot->m_name) != 0) {
		SetPlayerString(index, "PlayerName", text);
		((StringBase<unsigned short> *)(void *)&slot->m_name)->set(*(const StringBase<unsigned short> *)(const void *)&text);
	}
}

void StrategicHUD::RegionAwardMovieClip::Impl::SelectPlayer(int newRow)
{
	if (newRow == m_row50)
		return;
	if (m_row50 >= 0) {
		const char *oldTeam = m_holder08 ? (const char *)m_holder08 + 8 : "";
		Rva0057A9B7Fire(TheRva00222A8BTarget, m_level04, oldTeam, "SetPlayerRowState", &m_row50, (void *)"_deselect");
	}
	m_row50 = newRow;
	if (newRow < 0)
		return;
	const char *newTeam = m_holder08 ? (const char *)m_holder08 + 8 : "";
	Rva0057A9B7Fire(TheRva00222A8BTarget, m_level04, newTeam, "SetPlayerRowState", &m_row50, (void *)"_selected");
}
