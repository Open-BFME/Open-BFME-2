// cl: /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob0
// stlport
// ?rva005FF4D5@Rva005FF4D5@@QAEX_N@Z at 0x005FF4D5 (8B). Forwarder via this+4 to rowed Impl::SetMouseOver 0x005FF38D. Evidence: callers 0x005FA8DA 0x005FA8EE; prev 0x005FF4BD same +4 forwarder precedent; callee rowed.
#include "ascii_string.h"
#include "unicode_string.h"
#include "BattlePromptArmyPanelClipImplView.h"

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

// Complete20B leaves5FA8CD..5FA8E1 and5FA8E1..5FA8F5: first call
// rowed5FED59 on unchanged receiver, then pass true/false to the rowed
// mouse-over bridge5FF4D5 with receiver+8. Its independently matched
// Impl::SetMouseOver callee establishes the flag's role. Original wrapper
// owner/name and allocation extent remain unknown; only borrowed prefixes.
class Rva005FED59 {
public:
    void rva005FED59() const;
};
struct Rva005FA8CDHoverPrefix {
    unsigned char prefix[8];
    Rva005FF4D5 panel;
    void activateHover();
    void clearHover();
};
void Rva005FA8CDHoverPrefix::activateHover() {
    ((const Rva005FED59 *)this)->rva005FED59();
    panel.rva005FF4D5(true);
}
void Rva005FA8CDHoverPrefix::clearHover() {
    ((const Rva005FED59 *)this)->rva005FED59();
    panel.rva005FF4D5(false);
}
