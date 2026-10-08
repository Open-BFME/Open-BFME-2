// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FFA4E@Rva005FFA4E@@QAEXH@Z @ 0x005FFA4E 8B
// Forwarder: this+4 holds StrategicHUD::BattlePromptArmyPanelMovieClip::Impl object; tail-jmps to its 0x005FF9D8 SetUnitIconCount.
// Evidence: chain via 0x005FF9D8 row; caller 0x005FF061 push int mov ecx ebx esi+8; layout +4 ptr.
#include "ascii_string.h"
#include "unicode_string.h"
#include "BattlePromptArmyPanelClipImplView.h"

class Rva005FFA4E
{
public:
	void rva005FFA4E(int count);
private:
	char m_pad0[4];
	StrategicHUD::BattlePromptArmyPanelMovieClip::Impl *m_obj;
};

void Rva005FFA4E::rva005FFA4E(int count)
{
	m_obj->SetUnitIconCount(count);
}
