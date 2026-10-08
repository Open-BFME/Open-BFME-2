// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00406ED7@Rva00406ED7@@QAEPBVCommandButton@@H@Z @0x00406ED7 38B
// Unlock lane: bounds-checked (unsigned idx < 15) lookup of AsciiString at
// this+0x80 stride 12 via ControlBar::findCommandButton row 0x0031BE3C on
// g_bfmeWorldRV; callers 0x005B041D 0x005B2D23 0x005B4818 0x005B5B75.
// Honest-address method; LINK BONUS none.
#include "ascii_string.h"

class CommandButton;
class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};
struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

struct Rva00406ED7Item
{
    AsciiString name;
    int a;
    int b;
};

class Rva00406ED7
{
    char m_pad[0x80];
public:
    const CommandButton *rva00406ED7(int idx);
};
const CommandButton *Rva00406ED7::rva00406ED7(int idx)
{
    if ((unsigned int)idx >= 15)
        return 0;
    return ((ControlBar *)(void *)(*(BfmeWorldRV **)&TheControlBar))->findCommandButton(*(const AsciiString *)((char *)this + 0x80 + idx * 12));
}
