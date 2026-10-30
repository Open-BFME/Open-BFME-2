// Target Ghidra5966DD+125 and named owner from virtual destructor59675A.
// Primary clean donor BF1 9cbfb551fe20 BfmeCreditedCtorWA.cpp (Gen_00471EC0).
// Target verifies same layout: anim1C/scale20/name24/color28/delay2C/fontSize30,
// three-word phase arrays34 and40. Concrete semantic class name is unproven.
// Target-specific delay comes from canonical BfmeClientFramesPerSecond /4 +1; donor used8.
// Canonical AsciiString calls the rowed StringBase C-string constructor.
// Virtual base destructor is the same empty view as the existing matched dtor TU.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <string.h>
extern int BfmeClientFramesPerSecond;
class __declspec(novtable) Rva0059675ABase
{
public:
    virtual ~Rva0059675ABase();
};
class Anim2D;
class GameFont;
struct FadeInTextRender : Rva0059675ABase
{
    FadeInTextRender();
    virtual ~FadeInTextRender();
    virtual void LoadAssets();
    void bfmeExtend(int left, int top, int right, int bottom);

    GameFont* font;
    int m_bfmeLeft;
    int m_bfmeTop;
    int m_bfmeRight;
    int m_bfmeBottom;
    unsigned effectColor;
    Anim2D* anim;
    float scale;
    AsciiString fontName;
    unsigned color;
    int delay;
    unsigned fontSize;
    unsigned starts[3], ends[3];
    int width, height;
};
FadeInTextRender::FadeInTextRender():anim(0),scale(0.0f),fontName("SachaWynter"),color((220 << 16) | (240 << 8) | 250),delay(BfmeClientFramesPerSecond/4+1),fontSize(14) {
 memset(starts,0,sizeof(starts));memset(ends,0,sizeof(ends));
}
