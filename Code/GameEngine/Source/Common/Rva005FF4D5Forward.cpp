// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005FF4D5@Rva005FF4D5@@QAEX_N@Z at 0x005FF4D5 (8B). Forwarder via this+4 to rowed Impl::SetMouseOver 0x005FF38D. Evidence: callers 0x005FA8DA 0x005FA8EE; prev 0x005FF4BD same +4 forwarder precedent; callee rowed.
namespace StrategicHUD {
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
};

class Rva005FF4D5
{
public:
	void rva005FF4D5(bool flag);
private:
	char m_pad0[4];
	StrategicHUD::BattlePromptArmyPanelMovieClip::Impl *m_obj;
};

void Rva005FF4D5::rva005FF4D5(bool flag)
{
	m_obj->SetMouseOver(flag);
}
