// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Clean BFME1 ba7ddda7 ControlBarUpdateVirtual.cpp supplies the workflow.
// Named WB 0x00C2B8A0 and full native 0x0031E25E..0x0031E4BA supply
// the BFME2 offsets, 32-button loops, radar cleanup and actual call routes.
#include "ascii_string.h"
class GameWindow { public: bool winIsHidden(); int winHide(bool); };
class Player;
class Drawable;
class CommandButton;
class GameClient;
class GameWindowManager;
class PlayerList;
class RadarWindowOverrideSource { public: void rva002D370A(); };
// GameClient.cpp defines this singleton as GameClient*. Access its frame
// slot through the explicitly measured dispatch view below.
extern GameClient *TheGameClient;
extern GameWindowManager *TheWindowManager;
extern PlayerList *ThePlayerList;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString &); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva0031AEFF { public: void rva0031AEFF(); };
class Rva0031FA8E { public: void rva0031FA8E(); };
class Rva002D36D8 { public: int rva002D36D8(); };
class Rva000AD6F4 { public: void clear(); private: void *held; };
class Rva000B3FD0Nop { public: void noop(); };
class BfmeMemberRV;
class BfmeThingRV { public: BfmeMemberRV *bfmePickRV(); };
void *GadgetButtonGetData(GameWindow *);
int Rva00328700(GameWindow *);
struct ControlBarDrawableView { char unknown00[0xFC]; void *object; };
struct ControlBarFlashButtonView { char unknown00[0xF8]; int flashCount; };
#define SLOT(n) virtual void unknown##n()=0;
class ControlBarManagerUpdateView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04)
    SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
    virtual void update()=0;
};
class ControlBarAnimateUpdateView : public ControlBarManagerUpdateView
{
public:
    char unknown04[0x10];
    bool needsUpdate;
    bool reverse;
};
class ControlBarWindowManagerView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
    SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
    SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
    SLOT(56) SLOT(57) SLOT(58) SLOT(59)
    virtual GameWindow *lookupWindow(GameWindow *,NameKeyType)=0;
};
class ControlBarGameClientView
{
public:
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
    virtual unsigned int getFrame()=0;
};
#undef SLOT
class ControlBar
{
public:
    virtual void update();
    int rva0031AA86();
    void rva0031B210();
    void rva0031D230();
protected:
    void populateSpecialPowerShortcut(Player *);
public:
    void switchToContext(int,void *);
    void rva0053DF0A();
    void rva0053E6E1();
    void rva0053EAEC();
    void rva0053CF65();
    void rva0053E4B1();
    void updateContextContestedStructureInventory();
protected:
    void updateContextOCLTimer();
private:
    char unknown04[8];
    ControlBarManagerUpdateView *videoManager;
    ControlBarAnimateUpdateView *animateManager;
    ControlBarAnimateUpdateView *shortcutAnimateManager;
    char unknown18[0x10];
    bool uiDirty;
    char unknown29[0x1B];
    Rva0031FA8E *schemeManager;
    char unknown48[0x24];
    Drawable *selectedDrawable;
    int context;
    char unknown74[0x64];
    GameWindow *shortcutParent;
    GameWindow *commandWindows[32];
    char unknown15C[0xB8];
    bool radarTouched;
    char unknown215[0x8B];
    ControlBarManagerUpdateView *finalManager;
    Rva000AD6F4 radarHolder;
};
void ControlBar::update()
{
    rva0031AA86();
    ((Rva0031AEFF *)this)->rva0031AEFF();
    if (schemeManager) schemeManager->rva0031FA8E();
    if (videoManager) videoManager->update();
    if (animateManager) animateManager->update();
    if (animateManager && !animateManager->needsUpdate && animateManager->reverse)
    {
        NameKeyType id;
        {
            AsciiString name("ControlBar.wnd:ControlBarParent");
            id=TheNameKeyGenerator->nameToKey(name);
        }
        GameWindow *window=((ControlBarWindowManagerView *)TheWindowManager)->lookupWindow(0,id);
        if (window && !window->winIsHidden()) window->winHide(true);
    }
    if (shortcutAnimateManager) shortcutAnimateManager->update();
    if (shortcutAnimateManager && shortcutParent && !shortcutAnimateManager->needsUpdate
        && shortcutAnimateManager->reverse && !shortcutParent->winIsHidden())
        shortcutParent->winHide(true);
    if (!radarTouched)
    {
        if (theRadarWindowOverrideSource
            && (unsigned char)((Rva002D36D8 *)theRadarWindowOverrideSource)->rva002D36D8())
            theRadarWindowOverrideSource->rva002D370A();
        radarHolder.clear();
    }
    radarTouched=false;
    rva0031B210();
    for (int i=0; i!=32; ++i)
    {
        GameWindow *button=commandWindows[i];
        if (button)
        {
            ControlBarFlashButtonView *command=(ControlBarFlashButtonView *)GadgetButtonGetData(button);
            if (command && command->flashCount>0
                && ((ControlBarGameClientView *)TheGameClient)->getFrame()%10==0)
                --command->flashCount;
        }
    }
    if (uiDirty)
    {
        rva0031D230();
        populateSpecialPowerShortcut((Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV());
    }
    if (context==7)
    {
        rva0053DF0A();
        return;
    }
    if (!selectedDrawable || !((ControlBarDrawableView *)selectedDrawable)->object)
        if (context || selectedDrawable) switchToContext(0,0);
    switch (context)
    {
    case 1: rva0053CF65(); break;
    case 2: rva0053EAEC(); break;
    case 3: updateContextContestedStructureInventory(); break;
    case 4: rva0053E6E1(); break;
    case 5: ((Rva000B3FD0Nop *)this)->noop(); break;
    case 6: rva0053E4B1(); break;
    case 10: updateContextOCLTimer(); break;
    }
    for (int i=0; i!=32; ++i)
        if (commandWindows[i]) Rva00328700(commandWindows[i]);
    finalManager->update();
}
