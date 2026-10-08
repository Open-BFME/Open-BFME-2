// cl: /O1 /DNDEBUG /MD /EHsc
// Clean BFME1 ControlBar.cpp showSpecialPowerShortcut at ba7ddda7 supplies
// the workflow. Native 0x0031DAF8..0x0031DB83 proves the complete 139B body,
// timer +0x1A104, local player +0x10, five windows +0xA8, count +0xD0,
// and parent +0xD8. WB 0x00C31690 has the same calls but no original name.
class ScriptEngine;
class PlayerList;
class Object;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
struct ShortcutTimerView
{
    char unknown00[0x1A104];
    int endGameTimer;
    bool isGameEnding() const { return endGameTimer >= 0; }
};
class Player
{
public:
    Object *findNaturalCommandCenter();
};
struct ShortcutPlayerListView
{
    char unknown00[0x10];
    Player *localPlayer;
    Player *getLocalPlayer() { return localPlayer; }
};
class GameWindow
{
public:
    void *winGetUserData();
    int winHide(bool);
};
class ControlBar
{
public:
    void rva0031DAF8();
protected:
    void populateSpecialPowerShortcut(Player *);
private:
    char unknown00[0xA8];
    GameWindow *shortcutButtons[5];
    GameWindow *shortcutButtonParents[5];
    int shortcutButtonCount;
    char unknownD4[4];
    GameWindow *shortcutParent;
};
void ControlBar::rva0031DAF8()
{
    if (((const ShortcutTimerView *)TheScriptEngine)->isGameEnding()
        || !shortcutParent || !shortcutButtons || !ThePlayerList
        || !((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer())
        return;
    bool dontAnimate=true;
    for (int i=0; i<shortcutButtonCount; ++i)
    {
        if (shortcutButtons[i]->winGetUserData())
        {
            dontAnimate=false;
            break;
        }
    }
    if (dontAnimate
        || !((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer()->findNaturalCommandCenter())
        return;
    shortcutParent->winHide(false);
    populateSpecialPowerShortcut(((ShortcutPlayerListView *)ThePlayerList)->getLocalPlayer());
}
