// cl: /O1 /MD
// WB names SelectGameWindowHotKeyAction::doInvoke in its own source file.
// Retail53DA75..53DAD0 proves window+8, instance-owner+14 and dispatch+E8.
// The table at869310 puts this method at slot3. The other three slots and
// the prefix word remain opaque; this declaration-only view is not instantiated.
class WinInstanceData;
class GameWindow {
public:
    WinInstanceData *winGetInstanceData();
    int winGetWindowId();
};
struct HotKeyWindowInstanceView {
    unsigned char unknown0[0x14];
    GameWindow *owner;
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class HotKeyWindowManagerDispatchView {
public:
#define V(n) virtual void unknownSlot##n();
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
    V(20) V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29)
    V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
    V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
    V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57)
#undef V
    virtual int sendSystemMessage(GameWindow *, int, GameWindow *, int);
};
class SelectGameWindowHotKeyAction {
public:
    virtual void unknownSlot0();
    virtual void unknownSlot1();
    virtual void unknownSlot2();
    virtual bool doInvoke(bool flag);
private:
    unsigned char unknown4[4];
    GameWindow *window;
};
bool SelectGameWindowHotKeyAction::doInvoke(bool flag) {
    WinInstanceData *instance = window->winGetInstanceData();
    if (!instance) return false;
    GameWindow *owner = ((HotKeyWindowInstanceView *)instance)->owner;
    if (((HotKeyWindowManagerDispatchView *)TheWindowManager)->sendSystemMessage(
            owner, flag ? 0x400B : 0x4008, window, window->winGetWindowId())
            || !flag)
        return true;
    return false;
}
