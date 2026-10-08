// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// BFME1 ba7ddda7 ControlBar.cpp supplies the context-selection workflow.
// WB 0x00C2DCC0 names switchToContext. Native 0x0031BF64..0x0031C3E2
// supplies the complete 1150B instruction body, context values and offsets.
// The row also covers its immediately following 44B eleven-case jump table.
// Four new address-derived ControlBar callees have named WB counterparts:
// command 0x01117000, multiselect 0x01124EB0, construction 0x01123660,
// observer 0x0111D290. Beacon 0x01123A30 is unnamed. Native boundaries and
// argument cleanup establish each ABI, without recovering these bodies.
// Rally-point 0x00C2F300 names the Coord3D-pointer workflow, with retail
// 0x0031B892..0x0031B99A supplying its complete one-argument boundary.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
class Drawable;
class Object;
class GameWindow { public: int winHide(bool); unsigned int winClearStatus(unsigned int); };
class GameWindowManager;
class InGameUI;
class Rva00E01E28Owner;
extern GameWindowManager *TheWindowManager;
extern InGameUI *TheInGameUI;
extern Rva00E01E28Owner *g_00E01E28;
extern int g_Va00E04478;
extern Drawable *g_00E01D14; // Native previous-selection pointer; original name unknown.
extern GameLogic *TheGameLogic;
int Rva0043C969Get();
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D368E { public: void rva002D368E(); };
// This existing folded setter copies Object+0x74 to receiver+0x58. Using its
// owned binding does not identify the context overlay as PhysicsBehavior.
class PhysicsBehavior { public: void setIgnoreCollisionsWith(const Object *); };
struct BfmePod8 { int a[2]; };
namespace _STL {
template <> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *, BfmePod8 *);
}
class ContextResetView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void reset()=0;
};
class ContextRadiusView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void slot09()=0;
    virtual void slot10()=0;
    virtual void slot11()=0;
    virtual void slot12()=0;
    virtual void slot13()=0;
    virtual void slot14()=0;
    virtual void slot15()=0;
    virtual void slot16()=0;
    virtual void slot17()=0;
    virtual void slot18()=0;
    virtual void slot19()=0;
    virtual void slot20()=0;
    virtual void slot21()=0;
    virtual void slot22()=0;
    virtual void slot23()=0;
    virtual void slot24()=0;
    virtual void slot25()=0;
    virtual void slot26()=0;
    virtual void slot27()=0;
    virtual void slot28()=0;
    virtual void slot29()=0;
    virtual void slot30()=0;
    virtual void slot31()=0;
    virtual void slot32()=0;
    virtual void slot33()=0;
    virtual void slot34()=0;
    virtual void slot35()=0;
    virtual void slot36()=0;
    virtual void slot37()=0;
    virtual void slot38()=0;
    virtual void slot39()=0;
    virtual void slot40()=0;
    virtual void slot41()=0;
    virtual void slot42()=0;
    virtual void slot43()=0;
    virtual void slot44()=0;
    virtual void slot45()=0;
    virtual void slot46()=0;
    virtual void slot47()=0;
    virtual void slot48()=0;
    virtual void slot49()=0;
    virtual void slot50()=0;
    virtual void slot51()=0;
    virtual void slot52()=0;
    virtual void slot53()=0;
    virtual void slot54()=0;
    virtual void slot55()=0;
    virtual void slot56()=0;
    virtual void slot57()=0;
    virtual void slot58()=0;
    virtual void slot59()=0;
    virtual void slot60()=0;
    virtual void slot61()=0;
    virtual void slot62()=0;
    virtual void slot63()=0;
    virtual void slot64()=0;
    virtual void slot65()=0;
    virtual void slot66()=0;
    virtual void slot67()=0;
    virtual void slot68()=0;
    virtual void slot69()=0;
    virtual void slot70()=0;
    virtual void slot71()=0;
    virtual void slot72()=0;
    virtual void slot73()=0;
    virtual void slot74()=0;
    virtual void slot75()=0;
    virtual void slot76()=0;
    virtual void slot77()=0;
    virtual void slot78()=0;
    virtual void slot79()=0;
    virtual void slot80()=0;
    virtual void clearRadius()=0;
};
class ContextFocusView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void slot03()=0;
    virtual void slot04()=0;
    virtual void slot05()=0;
    virtual void slot06()=0;
    virtual void slot07()=0;
    virtual void slot08()=0;
    virtual void slot09()=0;
    virtual void slot10()=0;
    virtual void slot11()=0;
    virtual void slot12()=0;
    virtual void slot13()=0;
    virtual void slot14()=0;
    virtual void slot15()=0;
    virtual void slot16()=0;
    virtual void slot17()=0;
    virtual void slot18()=0;
    virtual void slot19()=0;
    virtual void slot20()=0;
    virtual void slot21()=0;
    virtual void slot22()=0;
    virtual void slot23()=0;
    virtual void slot24()=0;
    virtual void slot25()=0;
    virtual void slot26()=0;
    virtual void slot27()=0;
    virtual void slot28()=0;
    virtual void slot29()=0;
    virtual void slot30()=0;
    virtual void slot31()=0;
    virtual void slot32()=0;
    virtual void slot33()=0;
    virtual void slot34()=0;
    virtual void slot35()=0;
    virtual void slot36()=0;
    virtual void slot37()=0;
    virtual void slot38()=0;
    virtual void slot39()=0;
    virtual void slot40()=0;
    virtual void slot41()=0;
    virtual void slot42()=0;
    virtual void slot43()=0;
    virtual void slot44()=0;
    virtual void slot45()=0;
    virtual void slot46()=0;
    virtual void slot47()=0;
    virtual void slot48()=0;
    virtual int setFocus(GameWindow *)=0;
};
class ContextRebuildView {
public:
    virtual void slot00()=0;
    virtual void slot01()=0;
    virtual void slot02()=0;
    virtual void selected()=0;
};
class RebuildHoleBehaviorInterface;
class RebuildHoleBehavior { public: static RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterfaceFromObject(Object *); };
struct ContextDrawableView { char unknown00[0xFC]; Object *object; Object *getObject() { return object; } };
struct ContextTemplateView { char unknown00[0x10C]; unsigned char flags; };
struct ContextObjectView { char unknown00[4]; ContextTemplateView *objectTemplate; bool hasRebuildFlag() const { return (objectTemplate->flags&0x40)!=0; } };
struct ContextControlBarView {
    char unknown00[0x44];
    GameWindow *parent[10];
    Drawable *selected;
    int context;
    char unknown74[0x68];
    GameWindow *commandWindows[32];
    char unknown15C[0x144];
    ContextResetView *overlay;
    void *unknown2A4;
    _STL::vector<BfmePod8> selections;
};
struct Coord3D;
class ControlBar {
public:
    void switchToContext(int,void *);
    void showRallyPoint(const Coord3D *);
    void rva0053D355(Object *,bool);
    void rva0053E783(void *,int);
    void rva0050DBE6(Object *);
    void rva0053E4F1(Object *);
    void rva0053E34A(int);
    void rva0053DD53();
    void rva0050E08E();
};
// Each arm follows the independently read native call order.
#define HIDE_PARENTS(a,b,c,d,e,f,g,h) \
    self->parent[2]->winHide(a); self->parent[9]->winHide(b); \
    self->parent[3]->winHide(c); self->parent[4]->winHide(d); \
    self->parent[5]->winHide(e); self->parent[8]->winHide(f); \
    self->parent[6]->winHide(g); self->parent[7]->winHide(h)
void ControlBar::switchToContext(int context,void *draw)
{
    ContextControlBarView *self=(ContextControlBarView *)this;
    Drawable *incomingDraw=(Drawable *)draw;
    bool changed=context!=self->context || incomingDraw!=self->selected;
    if (changed) {
        self->selections.clear();
        if (theRadarWindowOverrideSource)
            ((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E();
    }
    Object *drawObject=incomingDraw ? ((ContextDrawableView *)incomingDraw)->getObject() : 0;
    if (g_00E01E28) ((ContextResetView *)g_00E01E28)->reset();
    ((ContextRadiusView *)TheInGameUI)->clearRadius();
    if (incomingDraw!=g_00E01D14 && incomingDraw!=self->selected)
        self->overlay->reset();
    Drawable *oldSelected=self->selected;
    self->selected=incomingDraw;
    g_00E01D14=oldSelected;
    if (!g_Va00E04478 && !Rva0043C969Get() && TheGameLogic && TheGameLogic->rva0042219())
        ((ContextFocusView *)TheWindowManager)->setFocus(0);
    ((PhysicsBehavior *)self->overlay)->setIgnoreCollisionsWith(drawObject);
    showRallyPoint(0);
    switch (context) {
    case 0:
    case 4:
        HIDE_PARENTS(true,true,true,true,true,true,true,true);
        {
            GameWindow **window=self->commandWindows;
            int count=32;
            do { if (*window) (*window)->winClearStatus(0x800000); ++window; --count; } while (count!=0);
        }
        if (incomingDraw && ((ContextDrawableView *)incomingDraw)->getObject()
            && ((ContextObjectView *)((ContextDrawableView *)incomingDraw)->getObject())->hasRebuildFlag()) {
            RebuildHoleBehaviorInterface *rebuild=RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject(((ContextDrawableView *)incomingDraw)->getObject());
            if (rebuild) ((ContextRebuildView *)rebuild)->selected();
        }
        break;
    case 1:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        rva0053D355(((ContextDrawableView *)incomingDraw)->getObject(),changed);
        break;
    case 2:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        rva0053E783(((ContextDrawableView *)incomingDraw)->getObject(),0);
        break;
    case 3:
        if (theRadarWindowOverrideSource) ((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E();
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        rva0053E783(((ContextDrawableView *)incomingDraw)->getObject(),1);
        break;
    case 5:
        HIDE_PARENTS(true,true,true,false,true,true,true,true);
        rva0050DBE6(((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 6:
        HIDE_PARENTS(true,false,true,true,true,true,true,true);
        rva0053E4F1(((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 10:
        HIDE_PARENTS(true,true,true,true,true,false,true,true);
        rva0053E34A((int)((ContextDrawableView *)incomingDraw)->getObject());
        break;
    case 7:
        HIDE_PARENTS(false,false,true,true,true,true,true,true);
        rva0053DD53();
        break;
    case 9:
        HIDE_PARENTS(true,true,true,true,true,true,true,false);
        rva0050E08E();
        break;
    }
    self->context=context;
}
#undef HIDE_PARENTS
