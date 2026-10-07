// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ?rva005FFEE5@Rva005FFEE5@@QAEHABUTreeHintRef00217D4C@@@Z at 0x005FFEE5 (8B). Forwarder via this+4 to rowed Impl::AddHeroArmyPanel 0x005FFCCB. Evidence: callers 0x005FB0CD 0x005FB39F 0x005FB574; prev 0x005FFED5 same +4 forwarder precedent; callee rowed.
struct TreeHintRef00217D4C
{
	void *m_ptr;
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
};

class Rva005FFEE5
{
public:
	int rva005FFEE5(const TreeHintRef00217D4C &arg);
private:
	char m_pad0[4];
	StrategicHUD::BattlePromptPlayerPageMovieClip::Impl *m_obj;
};

int Rva005FFEE5::rva005FFEE5(const TreeHintRef00217D4C &arg)
{
	return m_obj->AddHeroArmyPanel(arg);
}
