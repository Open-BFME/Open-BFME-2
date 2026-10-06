// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// GUI factories adapted from the readable Zero Hour GameWindowManager.cpp
// retained at Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69.
// Target facts: Ghidra boundaries; native style masks; the instance pointer
// at record+0x30; allocation/copy sizes; rowed helper calls; manager slots
// +0x88/+0x78/+0x12c; direct device wrappers selecting draw callbacks before
// these bodies. Shared views preserve the observed ABI without asserting
// the target's original record/type names or factory vtable positions.
// Field-purpose labels follow donor semantics where target accesses agree.
// Owner operation intentionally calls the existing target-address provider
// at 0x003140CF; no additional pin or duplicate range is introduced.
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"
class GameFont;
class GameWindow
{
public:
    void winSetUserData(void *);
};
class Rva003140CF { public: int rva003140CF(int); };
#include "GameWindowManagerRecordView.h"
struct FactoryInstanceView { unsigned char unknown[12]; unsigned int style; };
void GadgetTabControlComputeTabRegion(GameWindow *);
void GadgetTabControlCreateSubPanes(GameWindow *);
void GadgetTabControlShowSubPane(GameWindow *, int);
void GadgetButtonSetText(GameWindow *, UnicodeString);
void GadgetCheckBoxSetText(GameWindow *, UnicodeString);
void GadgetRadioSetText(GameWindow *, UnicodeString);
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
class DisplayStringFactoryView
{
public:
#define V(n) virtual void unused##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
    virtual DisplayString *newDisplayString();
};
class DisplayStringRecordView
{
public:
#define V(n) virtual void unused##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
    virtual void setWordWrapCentered(bool);
};
void GadgetStaticTextSetText(GameWindow *, UnicodeString);
GameWindow *TabWindowManagerView::gogoGadgetTabControl(GadgetCreateView *view,
    TabControlDataView *data, GameFont *font, bool visual)
{
    if (!(((FactoryInstanceView *)view->instance)->style & 0x2000)) return 0;
    GameWindow *window = ((TabWindowManagerView *)TheWindowManager)->createFromView(view);
    if (!window) return 0;
    TabControlDataView *copy = new TabControlDataView;
    memcpy(copy, data, sizeof(TabControlDataView));
    window->winSetUserData(copy);
    GadgetTabControlComputeTabRegion(window);
    GadgetTabControlCreateSubPanes(window);
    GadgetTabControlShowSubPane(window, 0);
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);
    assignDefaultGadgetLook(window, font, visual);
    return window;
}

GameWindow *TabWindowManagerView::gogoGadgetProgressBar(GadgetCreateView *view,
    GameFont *font, bool visual)
{
    if (!(((FactoryInstanceView *)view->instance)->style & 0x100)) return 0;
    GameWindow *window = ((TabWindowManagerView *)TheWindowManager)->createFromView(view);
    if (!window) return 0;
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);
    assignDefaultGadgetLook(window, font, visual);
    return window;
}

GameWindow *TabWindowManagerView::gogoGadgetPushButton(GadgetCreateView *view,
    GameFont *font, bool visual)
{
    if (!(((FactoryInstanceView *)view->instance)->style & 1)) return 0;
    GameWindow *window = ((TabWindowManagerView *)TheWindowManager)->createFromView(view);
    if (!window) return 0;
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);
    window->winSetUserData(0);
    assignDefaultGadgetLook(window, font, visual);
    UnicodeString text = winTextLabelToText(*(AsciiString *)((char *)view->instance + 0x188));
    if (text.getLength()) GadgetButtonSetText(window, text);
    return window;
}

GameWindow *TabWindowManagerView::gogoGadgetCheckBox(GadgetCreateView *view,
    GameFont *font, bool visual)
{
    if (!(((FactoryInstanceView *)view->instance)->style & 4)) return 0;
    GameWindow *window = ((TabWindowManagerView *)TheWindowManager)->createFromView(view);
    if (!window) return 0;
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);
    assignDefaultGadgetLook(window, font, visual);
    UnicodeString text = winTextLabelToText(*(AsciiString *)((char *)view->instance + 0x188));
    if (text.getLength()) GadgetCheckBoxSetText(window, text);
    return window;
}

GameWindow *TabWindowManagerView::gogoGadgetRadioButton(GadgetCreateView *view,
    RadioButtonDataView *data, GameFont *font, bool visual)
{
    if (!(((FactoryInstanceView *)view->instance)->style & 2)) return 0;
    GameWindow *window = ((TabWindowManagerView *)TheWindowManager)->createFromView(view);
    if (!window) return 0;
    RadioButtonDataView *copy = new RadioButtonDataView;
    memcpy(copy, data, sizeof(RadioButtonDataView));
    window->winSetUserData(copy);
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);
    assignDefaultGadgetLook(window, font, visual);
    UnicodeString text = winTextLabelToText(*(AsciiString *)((char *)view->instance + 0x188));
    if (text.getLength()) GadgetRadioSetText(window, text);
    return window;
}

GameWindow *TabWindowManagerView::gogoGadgetStaticText(GadgetCreateView *view,
    StaticTextDataView *data, GameFont *font, bool visual)
{
    ((FactoryInstanceView *)view->instance)->style &= ~0x1000;
    GameWindow *window;
    if (((FactoryInstanceView *)view->instance)->style & 0x80)
        window = createFromView(view);
    else return 0;
    if (window)
    {
        ((Rva003140CF *)window)->rva003140CF((int)view->parent);
        StaticTextDataView *copy = new StaticTextDataView;
        memcpy(copy, data, sizeof(StaticTextDataView));
        copy->text = ((DisplayStringFactoryView *)TheDisplayStringManager)->newDisplayString();
        ((DisplayStringRecordView *)copy->text)->setWordWrapCentered(
            (*(unsigned int *)((char *)view->instance + 0x10) & 0x40000) != 0);
        window->winSetUserData(copy);
        assignDefaultGadgetLook(window, font, visual);
        UnicodeString text = winTextLabelToText(*(AsciiString *)((char *)view->instance + 0x188));
        if (text.getLength()) GadgetStaticTextSetText(window, text);
    }
    return window;
}
