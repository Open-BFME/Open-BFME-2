// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?AddHeroArmyPanel@Impl@BattlePromptPlayerPageMovieClip@StrategicHUD@@QAEHABUTreeHintRef00217D4C@@@Z @0x005FFCCB 172B: append TreeHint plus CreateArmyPanel Apt via rowed AptCall 0x0050E9FE with hero format. Evidence: callers jmp 0x005FFEE8 plus TheRva00222A8BTarget plus g_Rva0107301CEmptyString plus strings hero CreateArmyPanel plus TreeHint assign 0x002174A4 plus format 0x00038150.
#include "ascii_string.h"

struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva0050E9FEAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char **a0ptr);

struct Rva005FFCCBInner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005FFCCBElem
{
	TreeHintRef00217D4C m_hint;
	int m_4;
	int m_8;
};

namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::BattlePromptPlayerPageMovieClip::Impl
{
public:
	int AddHeroArmyPanel(const TreeHintRef00217D4C &arg);
private:
	char m_pad0[4];
	void *m_4;
	Rva005FFCCBInner *m_8;
	char m_padC[0x24 - 0xC];
	Rva005FFCCBElem m_elems[3];
	int m_48;
};

int StrategicHUD::BattlePromptPlayerPageMovieClip::Impl::AddHeroArmyPanel(const TreeHintRef00217D4C &arg)
{
	int idx = m_48;
	m_48 = idx + 1;
	Rva005FFCCBElem *e = (Rva005FFCCBElem *)((char *)this + (idx + 3) * 12);
	e->m_hint = arg;
	e->m_8 = idx;
	AsciiString tmp;
	tmp.format("%s%d", "hero", idx);
	const char *raw = *(const char *const *)&tmp;
	const char *state;
	if (raw)
		state = raw + 8;
	else
		state = g_Rva0107301CEmptyString;
	const char *prefix = m_8 ? m_8->m_name : g_Rva0107301CEmptyString;
	Rva0050E9FEAptCall(TheRva00222A8BTarget, m_4, prefix, "CreateArmyPanel", &state);
	return idx;
}
