// cl: /ICode/GameEngine/Source/GameClient/GUI /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Slider gadget factory, retail 0x002C1485 (344 B, Ghidra boundary), called
// only by the W3D window manager override in vtable 0x00BC7C90 slot 25
// (0x0008FE14, call at 0x0008FE76) after it picks the thumb draw factory.
// Reference semantics: Zero Hour GameWindowManager::gogoGadgetSlider (BFME1
// 2791daf553 inputs). Target facts: create slot 34 (+0x88) with status bit
// 0x100 (tab stop), owner set through 0x003140CF, a 0x1A8-byte
// WinInstanceData local (ctor/init/dtor rowed) for the thumb with style 1
// (push button) plus 0x400 when the slider's own style has it, thumb created
// through slot 19 (+0x4C) at 13x16 for a horizontal slider (style 0x10) or
// width x width+1 otherwise, the 16-byte slider data copied after numTicks is
// computed, then assignDefaultGadgetLook (slot 30, +0x78). Like its rowed
// siblings in GameWindowManager_RecordFactories.cpp it is a member of the
// shared record view, not an assertion of the original class name.
#include <string.h>
#include "GameWindowManagerRecordView.h"

class GameWindow { public: void winSetUserData(void *); };
class Rva003140CF { public: int rva003140CF(int); };
struct FactoryInstanceView { unsigned char unknown[12]; unsigned int style; };
class WinInstanceData
{
    unsigned char opaque[420];
public:
    WinInstanceData();
    virtual ~WinInstanceData();
    void init();
};

GameWindow *TabWindowManagerView::gogoGadgetSlider(GadgetCreateView *view,
    SliderDataView *data, GameFont *font, bool visual)
{
    view->status |= 0x100;
    GameWindow *window = createFromView(view);
    if (!window) return 0;
    ((Rva003140CF *)window)->rva003140CF((int)view->parent);

    // thumb button: active and enabled, no border
    WinInstanceData instance;
    GadgetCreateView buttonView;
    buttonView.parent = window;
    buttonView.status = view->status | 0xC;
    buttonView.instance = &instance;
    instance.init();
    buttonView.status &= ~0x10;
    *(GameWindow **)((char *)&instance + 0x14) = window;
    ((FactoryInstanceView *)&instance)->style = 1;
    // if the slider is in image mode, so is the thumb
    if (((FactoryInstanceView *)view->instance)->style & 0x400)
        ((FactoryInstanceView *)&instance)->style |= 0x400;

    const unsigned int sliderStyle = ((FactoryInstanceView *)view->instance)->style;
    if (sliderStyle & 0x10)
    {
        buttonView.y = 0;
        buttonView.width = 13;
        buttonView.height = 16;
        createPushButtonFromView(&buttonView, 0, true);
    }
    else
    {
        buttonView.y = 0;
        buttonView.width = view->width;
        buttonView.height = view->width + 1;
        createPushButtonFromView(&buttonView, 0, true);
    }

    // need to have a range of at least 1
    if (data->maxVal == data->minVal) data->maxVal = data->minVal + 1;
    if (((FactoryInstanceView *)view->instance)->style & 0x10)
        data->numTicks = (float)(view->width - 13) / (float)(data->maxVal - data->minVal);
    else
        data->numTicks = (float)(view->height - 16) / (float)(data->maxVal - data->minVal);

    SliderDataView *copy = new SliderDataView;
    memcpy(copy, data, sizeof(SliderDataView));
    window->winSetUserData(copy);
    assignDefaultGadgetLook(window, font, visual);
    return window;
}
