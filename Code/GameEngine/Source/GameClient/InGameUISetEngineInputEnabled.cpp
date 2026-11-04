// cl: /O1 /DNDEBUG /MD
//
// InGameUI::setEngineInputEnabled, retail 0x0029AB22, 19 bytes.
// Dedicated TU so GameEngineClientSubsystems.cpp cannot see this body.
// Forwards the flag to virtual slot 0x148 with this+0x15 as the extra arg.

#include "../../Include/GameClient/InGameUI.h"

void InGameUI::setEngineInputEnabled(bool enabled)
{
	setInputEnabled(enabled, &field015);
}

// InGameUI::setInputEnabled, retail 0x0029AB35 (19 bytes), directly after the
// method above; the same forward with this+0x16. ZH's
// ScriptActions::doEnableInput pairs it with Mouse::setVisibility, and
// ScriptEngine::reset makes that same pair of calls with TRUE.
void InGameUI::setInputEnabled(bool enabled)
{
	setInputEnabled(enabled, &field016);
}

// BFME1 semantic guide ba7ddda7: W3DInGameUIDraw.cpp, native6FBFF0.
// Target8F0CA..8F179 adds a fourth per-view call and changes the measured
// slots/fields. Original receiver and new slot names remain unproved.
class View;
#define DRAW_SLOT(N) virtual void unused##N() = 0;
#include "../../Include/GameClient/Display.h"
class GameWindowManager
{
public:
    DRAW_SLOT(0)
    DRAW_SLOT(1)
    DRAW_SLOT(2)
    DRAW_SLOT(3)
    DRAW_SLOT(4)
    DRAW_SLOT(5)
    DRAW_SLOT(6)
    DRAW_SLOT(7)
    DRAW_SLOT(8)
    DRAW_SLOT(9)
    DRAW_SLOT(10)
    DRAW_SLOT(11)
    DRAW_SLOT(12)
    DRAW_SLOT(13)
    DRAW_SLOT(14)
    DRAW_SLOT(15)
    DRAW_SLOT(16)
    DRAW_SLOT(17)
    DRAW_SLOT(18)
    DRAW_SLOT(19)
    DRAW_SLOT(20)
    DRAW_SLOT(21)
    DRAW_SLOT(22)
    DRAW_SLOT(23)
    DRAW_SLOT(24)
    DRAW_SLOT(25)
    DRAW_SLOT(26)
    DRAW_SLOT(27)
    DRAW_SLOT(28)
    DRAW_SLOT(29)
    DRAW_SLOT(30)
    DRAW_SLOT(31)
    DRAW_SLOT(32)
    DRAW_SLOT(33)
    DRAW_SLOT(34)
    DRAW_SLOT(35)
    DRAW_SLOT(36)
    DRAW_SLOT(37)
    DRAW_SLOT(38)
    DRAW_SLOT(39)
    DRAW_SLOT(40)
    virtual void winRepaintWindows(); // native +0xA4
private:
    char unknown04[0x38];
public:
    int drawState; // native +0x3C
};
extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;
// Reuse the existing partial UI slot prefix as an ABI view. The donor
// supplies an inheritance lead; slot arithmetic alone proves no class name.
class Rva0008F0CA : public InGameUI
{
public:
    virtual void slot1E0();
    virtual void slot1E4(View *);
    virtual void slot1E8(View *);
    virtual void slot1EC(View *);
    virtual void slot1F0(View *);
    void rva0008F0CA();
};
#undef DRAW_SLOT
void Rva0008F0CA::rva0008F0CA()
{
    int state=TheWindowManager->drawState;
    switch (state) {
    case -1:
    case 1: break;
    case 0: TheWindowManager->winRepaintWindows(); return;
    default: return;
    }
    preDraw();
    if (field028) slot1E0();
    if (TheDisplay) {
        for (View *view=TheDisplay->getFirstView(); view; view=TheDisplay->getNextView(view)) {
            slot1E4(view);
            slot1E8(view);
            slot1EC(view);
            slot1F0(view);
        }
    }
    postDraw();
    TheWindowManager->winRepaintWindows();
}
