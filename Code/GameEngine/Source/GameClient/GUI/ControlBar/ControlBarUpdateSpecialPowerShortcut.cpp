// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE2 /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// BFME1 ba7ddda7 ControlBar_updateSpecialPowerShortcut.cpp guides behavior.
// Native 0x0031B210..0x0031B4A8 establishes BFME2 layout, state cases,
// disallowed flag calls, five-button array and SSE percentage conversion.
typedef bool Bool;
#include "subsystem_interface.h"
class Object;
class GameWindow
{
public:
    bool winIsHidden();
    int winHide(bool);
    int winEnable(bool);
    unsigned int winSetStatus(unsigned int);
    unsigned int winClearStatus(unsigned int);
};
class CommandButton;
struct ShortcutCommandButtonView
{
    char unknown00[0x1C];
    unsigned int options;
};
class Player { public: Object *findNaturalCommandCenter(); };
class BfmeMemberRV { public: bool bfmeAskRV(); };
class PlayerList;
extern PlayerList *ThePlayerList;
struct ShortcutPlayerListView
{
    char unknown00[0x10];
    Player *localPlayer;
    Player *getLocalPlayer() { return localPlayer; }
};
struct ShortcutAnimateManagerView
{
    char unknown00[0x14];
    bool finished;
    bool isFinished() const { return finished; }
};
class AnimateWindowManager;
class Rva0031AF54
{
public:
	void rva0031AF54(bool flag);
	char m_pad00[0x14];
	AnimateWindowManager *m_manager; // +0x14
	char m_pad18[0x90];
	GameWindow *m_list[10]; // +0xA8
	int m_count; // +0xD0
	char m_padD4[0x4];
	GameWindow *m_window; // +0xD8
};
void *GadgetButtonGetData(GameWindow *);
void GadgetButtonSetDisallowed(GameWindow *,int);
void Rva003284B9(GameWindow *,int,int);
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};

class ControlBar : public SubsystemInterface
{
public:
    void showSpecialPowerShortcut();
    void hideSpecialPowerShortcut();
    void rva0031B210();
    // The target call and callee's ret 0x14 prove this five-argument ABI.
    // Const qualification follows the donor; the address name does not claim
    // the original return enum, access level or complete target declaration.
    CommandAvailability getCommandAvailability(const CommandButton *,GameWindow *,Object *,float *,bool) const;
private:
    char m_pad0C[0x14 - 0x0C];
    ShortcutAnimateManagerView *m_animateWindowManagerForGenShortcuts;
    char unknown18[0x30];
    GameWindow *contextParent[9]; // [0] is the master window
    char unknown6C[0x3C];
    GameWindow *shortcutButtons[5];
    GameWindow *shortcutButtonParents[5];
    int shortcutButtonCount;
    char unknownD4[4];
    GameWindow *shortcutParent;
    char unknownDC[0x12C];
    unsigned int buildUpClockColor;
};
void ControlBar::rva0031B210()
{
    if (!shortcutParent || !shortcutButtons || !ThePlayerList
        || !((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer())
        return;
    if (((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter()
        && shortcutParent->winIsHidden()
        && contextParent[0] && !contextParent[0]->winIsHidden())
    {
        showSpecialPowerShortcut();
        ((Rva0031AF54 *)this)->rva0031AF54(true);
    }
    else if (!((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter()
        && !shortcutParent->winIsHidden() && !m_animateWindowManagerForGenShortcuts->isFinished())
        ((Rva0031AF54 *)this)->rva0031AF54(false);
    if (shortcutParent->winIsHidden()) return;
    if (!((BfmeMemberRV *)((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer())->bfmeAskRV())
    {
        hideSpecialPowerShortcut();
        return;
    }
    if (contextParent[0] && !contextParent[0]->winIsHidden() && shortcutParent->winIsHidden())
        showSpecialPowerShortcut();
    for (int i=0; i<shortcutButtonCount; ++i)
    {
        GameWindow *win=shortcutButtons[i];
        if (win->winIsHidden()==true) continue;
        const CommandButton *command=(const CommandButton *)GadgetButtonGetData(win);
        if (!command) continue;
        win->winClearStatus(0x00400000);
        win->winClearStatus(0x01000000);
        win->winClearStatus(0x40000000);
        win->winClearStatus(0x80000000);
        GadgetButtonSetDisallowed(win,false);
        int availability=0;
        float percent=0.0f;
        if (((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter())
            availability=getCommandAvailability(command,win,
                ((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter(),
                &percent,false);
        if (availability==0 || availability==7 || availability==4)
            if (((const ShortcutCommandButtonView *)command)->options & 0x00400000) availability=3;
        int color=0;
        switch (availability)
        {
        case 3:
            win->winHide(true);
            break;
        case 0:
        case 4:
        case 8:
            win->winEnable(false);
            win->winSetStatus(0x80000000);
            if (availability==4) GadgetButtonSetDisallowed(win,true);
            if (availability==8) win->winSetStatus(0x01000000);
            break;
        case 5:
            color=buildUpClockColor;
            win->winEnable(false);
            win->winSetStatus(0x00400000);
            break;
        case 6:
        case 7:
            win->winEnable(false);
            win->winSetStatus(0x01000000);
            break;
        case 1:
        case 2:
        default:
            win->winEnable(true);
            break;
        }
        if (percent<1.0f) Rva003284B9(win,(int)(percent*100.0f),color);
    }
}
