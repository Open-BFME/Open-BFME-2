// cl: /Ireference/shims/bfme2_ascii /MD
// ?GetButtonForLevel@CreateAHeroHero@@QAEPBVCommandButton@@H@Z @0x00406ED7 38B
// Unlock lane: bounds-checked (unsigned idx < 15) lookup of AsciiString at
// this+0x80 stride 12 via ControlBar::findCommandButton row 0x0031BE3C on
// g_bfmeWorldRV; callers 0x005B041D 0x005B2D23 0x005B4818 0x005B5B75.
// this+0x80 is CreateAHeroHero's m_buttons[15]; WB 107F3B0 names the method.
#include "ascii_string.h"

class CommandButton;
#include "../../Include/GameClient/ControlBar.h"
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

struct Rva00406ED7Item
{
    AsciiString name;
    int a;
    int b;
};

#include "../../Include/Common/CreateAHeroHero.h"
const CommandButton *CreateAHeroHero::GetButtonForLevel(int idx)
{
    if ((unsigned int)idx >= 15)
        return 0;
    return ((ControlBar *)(void *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(*(const AsciiString *)((char *)this + 0x80 + idx * 12));
}
